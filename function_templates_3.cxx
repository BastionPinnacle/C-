#include<iostream>
#include<cmath>

template<typename T, T (*F)(T), int N>
void process(T array[]){
    for(int i = 0 ; i < N ; i++){
        auto x = F(array[i]);
        array[i] = x;
    }
}
using namespace std;

int main(){
    double a[] = {1, 2, 3, 4};
    process<double, sin, 4> (a);
    for( auto x: a) cout << x << " ";
     // 0.841471 0.909297 0.14112 -0.756802
}