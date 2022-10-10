#include<stdexcept>
#include<iostream>
#include<iomanip>
#include<string>

struct MatrixException : public std::runtime_error{   
    MatrixException(std::string s): std::runtime_error( s ){} 
};

template<typename T>
int get_Longest_Row(std::initializer_list<std::initializer_list<T>> list){//OK
    int longest = 0;
    for(auto a : list){
        if(a.size()>longest) longest = a.size();
    }
    return longest;
}


template<typename T, int N, int M>
class Matrix;

template<typename T, int N, int M>
std::ostream& operator<<( std::ostream&, Matrix<T,N,M>& ); 

template<typename T, int N, int M>
Matrix<T,N,M> operator+(const Matrix<T,N,M>& m1, const Matrix<T,N,M>& );

template< typename T, int N, int M> 
class Matrix{
    private:   
        T matrix[N*M];
        int n;
        int m;
    public:
        Matrix();
        Matrix(bool);
        Matrix(const Matrix<T,N,M>& );
        Matrix(std::initializer_list<std::initializer_list<T>>);
        Matrix operator-();
        T& operator()(int n, int m);
        int numberOfRows()const{return n;}
        int numberOfColumns()const{return m;}
        template<typename TT, int U, int V, int X> 
        friend Matrix<TT,U,X> operator* (const Matrix<TT,U,V>& m1, const Matrix<TT,V,X>& m2);
        friend Matrix operator+<T,N,M> (const Matrix<T,N,M>& m1, const Matrix<T,N,M>& m2);
        friend std::ostream& operator<<<T,N,M>( std::ostream&, Matrix<T,N,M>& ); 
};

template<typename T, int N, int M>
Matrix<T,N,M>::Matrix(){
    std::cout<<" constructor of static "<<N<<"x"<<M<<" matrix\n";
    for(int i = 0 ; i < N*M ; i++) matrix[i]= T();
}
template<typename T, int N, int M>
Matrix<T,N,M>::Matrix(bool){
    std::cout<<" constructor of static "<<N<<"x"<<M<<" matrix without initialization\n";
}
template<typename T, int N, int M>
Matrix<T,N,M>::Matrix(const Matrix<T,N,M>& copied){
    std::cout<<"copy constructor of static "<<N<<"x"<<M<<" matrix\n";
    for(int i = 0 ; i < N*M ; i++) matrix[i]= copied.matrix[i];
}

template<typename T, int N, int M>
Matrix<T,N,M>::Matrix(std::initializer_list<std::initializer_list<T>> list){//OK
    std::cout<<" constructor of static "<<N<<"x"<<M<<" matrix from initializer list\n";
    int num_Of_Columns = get_Longest_Row(list);
    int num_Of_Rows = list.size();
    if(num_Of_Rows==N && num_Of_Columns == M){
        int row = 0;
        for(auto a : list){
            auto v = a.begin();
            int col = 0;
            for(col ; col < num_Of_Columns; col++){
                if(v!=a.end()){
                    matrix[row*num_Of_Columns+col]=*v;
                    v++;
                }
                else{
                    matrix[row*num_Of_Columns+col]=0.0;
                }
            }
            row++;
        } 
    }
    else{
        throw MatrixException();
    }
    
}

template<typename T, int N, int M>
T& Matrix<T,N,M>::operator()(int i, int j){
    return matrix[(i-1)*M+(j-1)];
}

template<typename TT, int U, int V, int X, int Y> 
Matrix<TT,U,X> operator* (const Matrix<TT,U,V>& m1,const  Matrix<TT,X,Y>& m2){
    if(V==X){
        Matrix<TT, U, X> newMatrix;
        for(int i = 0 ; i < U ; i++){
            for(int j = 0 ; j < X ; j++){
                for(int k = 0 ; k < V;k++){
                    newMatrix(i+1,j+1)+=(m1(i+1,k+1)*m2(k+1,j+1));
                }
            }
        }
        return newMatrix;
    }
    else{
        throw MatrixException();
    }
    
}   

template<typename T, int N, int M>
Matrix<T,N,M> Matrix<T,N,M>::operator-(){
    Matrix<T,N,M> newMatrix;
    for(int i = 1 ; i <= N ; i++){
        for(int j = 1; j <= M ; j++){
            newMatrix(i,j) =-(this->operator()(i,j));
        }
    }
    return newMatrix;
}

template<typename T, int N, int M>
std::ostream& operator<<( std::ostream& out, Matrix<T,N,M>& matrix){
    for(int i = 1 ; i < N ; i++ ){
        out<<"{";
        for(int j = 1 ; j < M ; j++ ){
            out<<matrix(i,j)<<", ";
        }
        out<<matrix(i,M)<<"}\n";
    }
    int i =  N;
    out<<"{";
    for(int j = 1 ; j < M ; j++ ){
        out<<matrix(i,j)<<", ";
    }
    out<<matrix(i,M)<<"}\n";
    return out;
}

template<typename T, int N, int M>
Matrix<T,N,M> operator+ (const Matrix<T,N,M>& m1, const Matrix<T,N,M>& m2){
    Matrix<T,N,M> newMatrix;
    for(int i = 1 ; i <= N; i++){
        for(int j = 1 ; j<= M ;j++){
            newMatrix(i,j) = m1(i,j) + m2(i,j);
        }
    }
    return newMatrix;
}

//specialization Matrix<T,0,0>
template<typename T> 
class Matrix<T,0,0>;

template<typename U>
Matrix<U,0,0> operator+(Matrix<U,0,0>& m1, Matrix<U,0,0>& m2);

template<typename T> 
class Matrix<T,0,0>{
    private:
        T* data;
        int num_Of_Columns;
        int num_Of_Rows;
        
    public:
        Matrix();
        Matrix(int,int,bool);
        Matrix(int,int);
        Matrix(std::initializer_list<std::initializer_list<T>>);
        Matrix(const Matrix& );
        Matrix(Matrix&& );
        ~Matrix();
        int numberOfRows()const{return num_Of_Rows;}
        int numberOfColumns()const{return num_Of_Columns;}
        Matrix& operator=(const Matrix& matrix);
        Matrix& operator=(Matrix&& matrix);
        T operator()(int,int)const;
        T& operator()(int,int);
        Matrix<T,0,0> operator-();
        friend std::ostream& operator<<<T,0,0>( std::ostream&, Matrix<T,0,0>& );
        friend Matrix<T,0,0> operator+<T,0,0>(const Matrix<T,0,0>& m1, const Matrix<T,0,0>& m2);
        friend Matrix<T,0,0> operator*<T,0,0>(const Matrix<T,0,0>& m1, const Matrix<T,0,0>& m2);

};
template<typename T>
Matrix<T,0,0>::Matrix(std::initializer_list<std::initializer_list<T>> list){
    num_Of_Columns = get_Longest_Row(list);
    num_Of_Rows = list.size();
    std::cout<<" constructor of dynamic "<<num_Of_Rows<<"x"<<num_Of_Columns<<" matrix from initializer_list\n";
    data = new T[num_Of_Columns*num_Of_Rows];
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
template<typename T>
Matrix<T,0,0>::Matrix():data(nullptr),num_Of_Columns(0),num_Of_Rows(0){
        std::cout<<" default constructor of dynamic matrix\n";
}
template<typename T>
Matrix<T,0,0>::Matrix(int n, int m) : num_Of_Columns(m), num_Of_Rows(n){ //OK
    std::cout<<" constructor of dynamic "<<num_Of_Rows<<"x"<<num_Of_Columns<<" matrix\n";
    data = new T[n*m];
    for(int i = 0 ; i < num_Of_Rows ; i++){
        for(int j = 0 ; j < num_Of_Columns ; j++){
            data[i*num_Of_Columns+j]=0.0;
        }
    }
}

template<typename T>
Matrix<T,0,0>::Matrix(int n, int m, bool f) : num_Of_Columns(m), num_Of_Rows(n){ //OK
    std::cout<<" constructor of dynamic "<<num_Of_Rows<<"x"<<num_Of_Columns<<" uninitialized matrix\n";
    data = new T[n*m];
    for(int i = 0 ; i < num_Of_Rows ; i++){
        for(int j = 0 ; j < num_Of_Columns ; j++){
            data[i*num_Of_Columns+j]=0.0;
        }
    }
}

template<typename T>
Matrix<T,0,0>::Matrix(const Matrix& matrix):num_Of_Columns(matrix.num_Of_Columns),num_Of_Rows(matrix.num_Of_Rows){//OK 
    std::cout<<"copy constructor of dynamic "<<num_Of_Rows<<"x"<<num_Of_Columns<<" matrix\n";

    data = new T[num_Of_Columns*num_Of_Rows];
    for(int i = 0 ; i < num_Of_Rows ; i++ ){
        for(int j = 0 ; j < num_Of_Columns ; j++ ){
            data[i*num_Of_Columns+j]=matrix.data[i*num_Of_Columns+j];
        }
    }
}
template<typename T>
Matrix<T,0,0>::Matrix(Matrix&& matrix){
    std::cout<<" move constructor of dynamic matrix\n";
    num_Of_Columns = matrix.num_Of_Columns;
    num_Of_Rows = matrix.num_Of_Rows;
    data = matrix.data;
    matrix.data = nullptr;
}
template<typename T>
Matrix<T,0,0>::~Matrix(){//OK
    if(data) delete data;
    data = nullptr;
}
template<typename T>
T Matrix<T,0,0>::operator()(int n, int m)const{//OK
    return data[(n-1)*num_Of_Columns+(m-1)];
}
template<typename T>
T& Matrix<T,0,0>::operator()(int n, int m){//OK
    return data[(n-1)*num_Of_Columns+(m-1)];
}
template<typename T>
Matrix<T,0,0>& Matrix<T,0,0>::operator=(const Matrix<T,0,0>& matrix){//OK
    std::cout<<" copy assignment operator\n";   
    if(!(data)) delete [] data;
    data = new T[num_Of_Columns*num_Of_Rows];
    num_Of_Columns  =    matrix.num_Of_Columns;
    num_Of_Rows     =    matrix.num_Of_Rows;
    for(int i = 0 ; i < num_Of_Rows ; i++ ){
        for(int j = 0 ; j < num_Of_Columns ; j++ ){
            data[i*num_Of_Columns+j]=matrix.data[i*num_Of_Columns+j];
        }
    }
    return *this;
}
template<typename T>
Matrix<T,0,0>& Matrix<T,0,0>::operator=(Matrix<T,0,0>&& matrix){
    std::cout<<" move assignment operator\n";
    num_Of_Columns = matrix.num_Of_Columns;
    num_Of_Rows = matrix.num_Of_Rows;
    data = matrix.data;
    matrix.data = nullptr;
    return *this;
}
template<typename T>
Matrix<T,0,0> Matrix<T,0,0>::operator-(){
    Matrix newMatrix;
    newMatrix.num_Of_Rows = this->num_Of_Rows;
    newMatrix.num_Of_Columns = this->num_Of_Columns;
    newMatrix.data = new T[newMatrix.num_Of_Columns*newMatrix.num_Of_Rows];
    for(int i = 0 ; i < newMatrix.num_Of_Rows ; i++){
        for(int j = 0 ; j < newMatrix.num_Of_Columns ; j++){
            newMatrix.data[i*newMatrix.num_Of_Columns+j]=-(this->data[i*newMatrix.num_Of_Columns+j]);
        }
    }
    return newMatrix;
}
template<typename U>
std::ostream& operator<<( std::ostream& out, Matrix<U,0,0>& matrix){
    for(int i = 0 ; i < matrix.numberOfRows()-1 ; i++ ){
        out<<"{";
        for(int j = 0 ; j < matrix.numberOfColumns()-1 ; j++ ){
            out<<matrix.data[i*matrix.numberOfColumns()+j]<<", ";
        }
        out<<matrix.data[i*matrix.numberOfColumns()+matrix.numberOfColumns()-1]<<"}\n";
    }
    int i =  matrix.numberOfRows()-1;
    out<<"{";
    for(int j = 0 ; j < matrix.numberOfColumns()-1 ; j++ ){
        out<<matrix.data[i*matrix.numberOfColumns()+j]<<", ";
    }
    out<<matrix.data[i*matrix.numberOfColumns()+matrix.numberOfColumns()-1]<<"}\n";
    return out;
}
template<typename U>
Matrix<U,0,0> operator+(Matrix<U,0,0>& m1, Matrix<U,0,0>& m2){
    if(m1.numberOfColumns() == m2.numberOfColumns() && m1.numberOfRows() == m2.numberOfRows()){
        int n = m1.numberOfRows();
        int m = m1.numberOfColumns();
        Matrix<U,0,0> newMatrix(n, m);
        for(int i = 1 ; i <= n ; i++ ){
            for(int j = 1 ; j <= m ; j++){
                newMatrix(i,j) = m1(i,j) + m2(i,j);
            }
        }
        return newMatrix;
    }
    else{
        throw MatrixException("Incompatible sizes operation +");
    }
}

template<typename U>
Matrix<U,0,0> operator*(Matrix<U,0,0>& m1, Matrix<U,0,0>& m2){
    if(m1.numberOfColumns() == m2.numberOfRows()){
        int n = m1.numberOfRows();
        int m = m2.numberOfColumns();
        int p = m1.numberOfColumns();
        Matrix<U,0,0> newMatrix(n, m, 0) ;
        for(int i = 1 ; i <= n ; i++ ){
            for(int j = 1 ; j <= m ; j++){  
                for(int k = 1 ; k<= p ; k++){
                    newMatrix(i,j) += (m1(i,k)*m2(k,j));
                }
                
            }
        }
        return newMatrix;
    }
    else{
        throw MatrixException("Incompatible sizes operation *");
    }
}

using namespace std;




template <typename M>
void printMatrix(const M & m, int width = 10){
	for(int i = 1; i <= m.numberOfRows(); ++i){
		for(int j = 1; j <= m.numberOfColumns(); ++j){
			if(j != 1) 
				cout << " ";
			cout << setw(width) <<  m(i,j) ;
		}
		cout << endl;
	}
}

int main(){
    cout <<fixed << setprecision(2);

	using DMatrix = Matrix<double, 0, 0>;
	DMatrix m0(2,3);
	printMatrix(m0);

	DMatrix m1({{1,  2,  3,  4},  // constructor from 
		       { 5,  6,  7,  8},  // initialization_list 
		       { 9, 10, 11, 12}});  
	printMatrix(m1);

	DMatrix m2 = m1;              // copy constructor
	m2(2,1) = -5;  m2(3,2) = -20; // mutable access
	printMatrix(m2);

	DMatrix m3 = m1 + m2;         // matrix sum (with equal sizes)  
    printMatrix(m3);

    try {
        auto mm = m1 * m2; // ERROR: exception
    } catch(MatrixException & e){
	    cout << " Exception : " << e.what() << endl;
	}

	DMatrix m4({
		{1.2, 1},
		{21, 2},
		{34, 2},
		{2, 32}});
	DMatrix m5 = m1 * m4;    // matrix multiplication 
    printMatrix(m5);

    try {
        auto mm = m1 + m4;   // ERROR: exception
    } catch(MatrixException & e){
        cout << " Exception : " << e.what() << endl;
    }

	return 0;
}

/*
 * Expected output (or similar)
 constructor of dynamic 2x3 matrix
      0.00       0.00       0.00
      0.00       0.00       0.00
 constructor of dynamic 3x4 matrix from initializer_list
      1.00       2.00       3.00       4.00
      5.00       6.00       7.00       8.00
      9.00      10.00      11.00      12.00
 copy constructor of dynamic matrix
      1.00       2.00       3.00       4.00
     -5.00       6.00       7.00       8.00
      9.00     -20.00      11.00      12.00
 constructor of dynamic 3x4 matrix
 move constructor of dynamic matrix
      2.00       4.00       6.00       8.00
      0.00      12.00      14.00      16.00
     18.00     -10.00      22.00      24.00
 Exception : Incompatible dimensions in operator *
 constructor of dynamic 4x2 matrix from initializer_list
 constructor of uninitialized dynamic 3x2 matrix
    153.20     139.00
    386.00     287.00
    618.80     435.00
 Exception : Incompatible dimensions in operator +

*/