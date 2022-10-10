#include<iostream>
#include <initializer_list>
#include<memory>

class Matrix{
    private:
        std::unique_ptr<double []> data;
        int num_Of_Columns;
        int num_Of_Rows;
        
    public:
        Matrix();
        Matrix(int,int);
        Matrix(std::initializer_list<std::initializer_list<double>>);
        Matrix(const Matrix& );
        Matrix(Matrix&& );
        ~Matrix();
        Matrix& operator=(const Matrix& matrix);
        Matrix& operator=(Matrix&& matrix);
        double operator()(int,int);
        Matrix operator-();
        friend std::ostream& operator<<( std::ostream&,Matrix& ); 
};
int get_Longest_Row(std::initializer_list<std::initializer_list<double>> list){//OK
    int longest = 0;
    for(auto a : list){
        if(a.size()>longest) longest = a.size();
    }
    return longest;
}
Matrix::Matrix(std::initializer_list<std::initializer_list<double>> list){//OK
    num_Of_Columns = get_Longest_Row(list);
    num_Of_Rows = list.size();
    std::cout<<" constructor of "<<num_Of_Rows<<"x"<<num_Of_Columns<<" matrix from initializer_list\n";
    data = std::make_unique<double []> (num_Of_Columns*num_Of_Rows);
    int row = 0;
    for(auto a : list){
        auto v = a.begin();
        int col = 0;
        for(col ; col < num_Of_Columns; col++){
            if(v!=a.end()){
                data[row*num_Of_Columns+col]=*v;
                v++;
            }
            else{
                data[row*num_Of_Columns+col]=0.0;
            }
        }
        row++;
    }
}
Matrix::Matrix():num_Of_Columns(0),num_Of_Rows(0){
    data = nullptr;
    std::cout<<"default constructor\n";
} //OK
Matrix::Matrix(int n, int m) : num_Of_Columns(m), num_Of_Rows(n){ //OK
std::cout<<" constructor of "<<num_Of_Rows<<"x"<<num_Of_Columns<<" matrix\n";
    data = std::make_unique<double []> (num_Of_Columns*num_Of_Rows);
    for(int i = 0 ; i < num_Of_Rows ; i++){
        for(int j = 0 ; j < num_Of_Columns ; j++){
            data[i*num_Of_Columns+j]=0.0;
        }
    }
}
Matrix::Matrix(const Matrix& matrix):num_Of_Columns(matrix.num_Of_Columns),num_Of_Rows(matrix.num_Of_Rows){//OK
    std::cout<<" copy constructor\n";    
    data = std::make_unique<double []> (num_Of_Columns*num_Of_Rows);
    for(int i = 0 ; i < num_Of_Rows ; i++ ){
        for(int j = 0 ; j < num_Of_Columns ; j++ ){
            data[i*num_Of_Columns+j]=matrix.data[i*num_Of_Columns+j];
        }
    }
}

Matrix::Matrix(Matrix&& matrix){
    std::cout<<" move constructor\n";
    num_Of_Columns = matrix.num_Of_Columns;
    num_Of_Rows = matrix.num_Of_Rows;
    data = std::move(matrix.data);
}
Matrix::~Matrix(){}//OK
double Matrix::operator()(int n, int m){//OK
    return data[(n-1)*num_Of_Columns+(m-1)];
}
Matrix& Matrix::operator=(const Matrix& matrix){//OK
    std::cout<<" copy assignment operator\n";   
    num_Of_Columns  =    matrix.num_Of_Columns;
    num_Of_Rows     =    matrix.num_Of_Rows;
    data = std::make_unique<double []> (num_Of_Columns*num_Of_Rows);
    for(int i = 0 ; i < num_Of_Rows ; i++ ){
        for(int j = 0 ; j < num_Of_Columns ; j++ ){
            data[i*num_Of_Columns+j]=matrix.data[i*num_Of_Columns+j];
        }
    }
    return *this;
}
Matrix& Matrix::operator=(Matrix&& matrix){
    std::cout<<" move assignment operator\n";
    num_Of_Columns = matrix.num_Of_Columns;
    num_Of_Rows = matrix.num_Of_Rows;
    data = std::move(matrix.data);
    return *this;
}
Matrix Matrix::operator-(){
    Matrix newMatrix;
    newMatrix.num_Of_Rows = this->num_Of_Rows;
    newMatrix.num_Of_Columns = this->num_Of_Columns;
    newMatrix.data = std::make_unique<double []> (num_Of_Columns*num_Of_Rows);
    for(int i = 0 ; i < newMatrix.num_Of_Rows ; i++){
        for(int j = 0 ; j < newMatrix.num_Of_Columns ; j++){
            newMatrix.data[i*newMatrix.num_Of_Columns+j]=-(this->data[i*newMatrix.num_Of_Columns+j]);
        }
    }
    return newMatrix;
}
std::ostream& operator<<( std::ostream& out, Matrix& matrix){//OK
    for(int i = 0 ; i < matrix.num_Of_Rows-1 ; i++ ){
        out<<"{";
        for(int j = 0 ; j < matrix.num_Of_Columns-1 ; j++ ){
            out<<matrix.data[i*matrix.num_Of_Columns+j]<<", ";
        }
        out<<matrix.data[i*matrix.num_Of_Columns+matrix.num_Of_Columns-1]<<"}\n";
    }
    int i =  matrix.num_Of_Rows-1;
    out<<"{";
    for(int j = 0 ; j < matrix.num_Of_Columns-1 ; j++ ){
        out<<matrix.data[i*matrix.num_Of_Columns+j]<<", ";
    }
    out<<matrix.data[i*matrix.num_Of_Columns+matrix.num_Of_Columns-1]<<"}\n";
    return out;
}

using namespace std;

int main(){
	
	Matrix m1;
	Matrix m2(3,4); 
	Matrix m3({{1,2,3},{32, 23, 22},{3,234,23,44}});
	cout << m2(1,1) << endl;  // 0
	cout << m3(2,2) << endl;  // 23
	cout << m3; 
	
	cout << "Copy semantics \n";
	Matrix m4 = m2;
	m4 = m3;
	
	cout << "Move semantics \n";
	Matrix m7 = std::move(m2);
	m4 = -m3;
	
	cout << "Copy elision \n";
	Matrix m6 = -m4;           
	Matrix * pm = new Matrix(-m4);           
	cout << m6(2,1) << endl; // 32
	
	return 0;
}