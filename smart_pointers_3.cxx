#include"Matrix.hxx"

class MatrixPair{
    public:
        MatrixPair(Matrix first, Matrix second):left(first),right(second){}
        //MatrixPair(MatrixPair& mp) = default;
        MatrixPair(MatrixPair&& mp): left(std::move(mp.left)), right(std::move(mp.right)){}
        MatrixPair& operator=(MatrixPair&& mp) = default;
        Matrix left;
        Matrix right;   
};

int main(){
    Matrix m1({{1,2},{4,4}}), m2(4,5);
    MatrixPair p1(m1,std::move(m2));
    MatrixPair p2 = p1;
    MatrixPair p3 = std::move(p1);
    Matrix a = p3.left;
    Matrix b = p3.right;
    MatrixPair p4(a,b);
    //p1=p4;
    p1=std::move(p4);
}