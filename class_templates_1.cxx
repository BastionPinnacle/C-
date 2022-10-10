#include<stdexcept>
#include <iostream>
#include <iomanip>


template<typename T, int N, int M>
class Matrix;

template<typename T, int N, int M>
Matrix<T,N,M> operator+ (const Matrix<T,N,M>& m1, const Matrix<T,N,M>& m2);    


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
        T& operator()(int n, int m);
        T operator()(int n, int m)const;
        int numberOfRows()const{return N;}
        int numberOfColumns()const{return M;}
        template<typename TT, int U, int V, int X> 
        friend Matrix<TT,U,X> operator* (const Matrix<TT,U,V>& m1, const Matrix<TT,V,X>& m2);
        friend Matrix operator+<T,N,M> (const Matrix<T,N,M>& m1, const Matrix<T,N,M>& m2);    
};

template<typename T, int N, int M>
Matrix<T,N,M>::Matrix(){
    for(int i = 0 ; i < N*M ; i++) matrix[i]= T();
    std::cout<<"constructor of static " << N <<"x" <<M<<" matrix\n";
}
template<typename T, int N, int M>
Matrix<T,N,M>::Matrix(bool){
    std::cout<<"constructor of static " << N <<"x" <<M<<" matrix without initialization\n";
}


template<typename T, int N, int M>
Matrix<T,N,M>::Matrix(const Matrix<T,N,M>& copied){
    for(int i = 0 ; i < N*M ; i++) matrix[i]= copied.matrix[i];
    std::cout<<"copy constructor of static matrix\n";
}

template<typename U>
int get_Longest_Row(std::initializer_list<std::initializer_list<U>> list){//OK
    int longest = 0;
    for(auto a : list){
        if(a.size()>longest) longest = a.size();
    }
    return longest;
}

template<typename T, int N, int M>
Matrix<T,N,M>::Matrix(std::initializer_list<std::initializer_list<T>> list){//OK
    int num_Of_Columns = get_Longest_Row(list);
    int num_Of_Rows = list.size();
    
    if(num_Of_Rows==N && num_Of_Columns == M){
        std::cout<<"constructor of static "<< N<<"x"<<M<< " matrix from initializer_list\n";
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
        throw 10;
    }
    
}

template<typename T, int N, int M>
T& Matrix<T,N,M>::operator()(int i, int j){
    return matrix[(i-1)*M+(j-1)];
}
template<typename T, int N, int M>
T Matrix<T,N,M>::operator()(int i, int j)const{
    return matrix[(i-1)*M+(j-1)];
}

template<typename TT, int U, int V, int X> 
Matrix<TT,U,X> operator* ( Matrix<TT,U,V>& m1,  Matrix<TT,V,X>& m2){
    Matrix<TT, U, X> newMatrix = {0};
    for(int i = 0 ; i < U ; i++){
        for(int j = 0 ; j < X ; j++){
            for(int k = 0 ; k < V;k++){
                newMatrix(i+1,j+1)+=(m1(i+1,k+1)*m2(k+1,j+1));
            }
        }
    }
    return newMatrix;
}   

template<typename T, int N, int M> 
Matrix<T,N,M> operator+ (const Matrix<T,N,M>& m1, const Matrix<T,N,M>& m2){
    Matrix<T,N,M> newMatrix = {0};
    for(int i = 1 ; i <= N; i++){
        for(int j = 1 ; j<= M ;j++){
            newMatrix(i,j) = m1(i,j) + m2(i,j);
        }
    }
    return newMatrix;
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
	using DMatrix = Matrix<double, 3, 4>;

	DMatrix m0{}; // Matrix filled with zeroes
	printMatrix(m0);

	DMatrix m1({{1,  2,  3,  4},  // constructor from
		       { 5,  6,  7,  8},  // initialization_list 
		       { 9, 10, 11, 12}});
	printMatrix(m1); 
	DMatrix m2 = m1;              // copy constructor  
	m2(2,1) = -5;  m2(3,2) = -20; // mutable access  
	DMatrix m3 = m1 + m2;         // matrix sum (with equal sizes)  
	//auto mm = m1 * m2; // compilation ERROR
	printMatrix(m3);
	
	Matrix<double, 4, 2> m4({
		{1.2, 1},
		{21, 2},
		{34, 2},
		{2, 32}});
	Matrix<double,3,2> m5 = m1 * m4;    // matrix multiplication 
	//auto mm = m1 + m4;   // compilation ERROR
	printMatrix(m5);

	return 0;
}

/*
 * Expected output (or similar)
 constructor of static 3x4 matrix
      0.00       0.00       0.00       0.00
      0.00       0.00       0.00       0.00
      0.00       0.00       0.00       0.00
 constructor of static 3x4 matrix from initializer_list
      1.00       2.00       3.00       4.00
      5.00       6.00       7.00       8.00
      9.00      10.00      11.00      12.00
 copy constructor of static matrix
 constructor of static uninitialized matrix
      2.00       4.00       6.00       8.00
      0.00      12.00      14.00      16.00
     18.00     -10.00      22.00      24.00
 constructor of static 4x2 matrix from initializer_list
 constructor of static uninitialized matrix
    153.20     139.00
    386.00     287.00
    618.80     435.00
*/