#include<string>
#include<iostream>
#include<vector>
#include<list>
#include<cmath>

//A
template<typename T>
T sqr(T x){
    return x*x;
}
template <> std::string sqr<std::string>(std::string x){
    std::string y = x;
    y+=x;
    return y;
}
//B
template<int N>
int mod (int x){
    return x%N;
}
template <> int mod<0>(int x){
    return -x;
}
//C
template    <template <typename, typename> class Container, 
            typename T,
            typename Alloc>
void print(const Container<T,Alloc> & v){
    for(auto a : v){
        std::cout<<a<<" ";
    }
    std::cout<<std::endl;
}
//D
template    <template <typename, typename> class C, 
            typename T,
            typename Alloc, typename F =  bool (*)(T) >
C<T,Alloc> apply(const C<T,Alloc>& c, F f){
    C<T,Alloc> newC;
    for(auto x : c){
        auto y = f(x);
        newC.insert( newC.end(), y);
    }
    return newC;
}


int main(){
    //A
    std::cout << sqr(4) << std::endl;
    std::cout << sqr(14.5) << std::endl;
    std::cout << sqr(std::string("hey")) << std::endl;  
    //B
    std::cout<< mod<5>(131) <<std::endl;        //1
    std::cout<< mod<7>(131) <<std::endl;        //5
    std::cout<< mod<0>(131) <<std::endl;        //-131
    //C
    std::vector<int> v = {1,21,34,4,15};
    print(v);                                   // 1 21 34 4 15
    std::list<double> l = {1, 2.1, 3.2,6.3};
    print(l);                                   // 1 2.1 3.2 6.3
    //D
    auto w = apply(v, sqr<int>);
    auto w2 = apply(w, mod<5> );
    print(w2);                                  // 1 1 1 1 0 
    auto l2 = apply(l, sqr<double>);
    auto l3 = apply(l2, mod<5>);
    print(l3);                                  // 1 4 0 4 

    auto l4 = apply(l3, static_cast<double(*)(double)>(std::sin));
    print(l4); // 0.841471 -0.756802 0 -0.756802
}