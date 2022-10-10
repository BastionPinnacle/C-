#include<iostream>
#include<cmath>
#include<vector>
#include<list>
#include <memory> // for std::allocator
template    <template <typename, typename> class OutContainer, 
            template <typename, typename> class InContainer, 
            typename T,
            typename Alloc,typename Predicate =  bool (*)(T) >
OutContainer<T,Alloc> selectIf(const InContainer<T, Alloc> & c, Predicate p){
    OutContainer<T,Alloc> out;
    for(auto x : c){
        if(p(x)) out.insert(out.end(),x);
    }
    return out;
}

template<typename Container>
void print(const Container & v){
    for(auto a : v){
        std::cout<<a<<" ";
    }
    std::cout<<std::endl;
}

bool biggerThan5(int x){ return x>5; }

int main(){
    
    std::vector<int> v={1, 2, 13, 4, 5, 54};
    std::list<int> result = selectIf<std::list>(v, biggerThan5);// result should contain 13 and 54
    print(result);
}