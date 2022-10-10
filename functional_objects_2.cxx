#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <cassert>
#include <numeric>
#include <cmath>
#include <type_traits>
using namespace std;

void print(const std::vector<int> & v){
	for( auto x  : v) cout << x << " ";
	cout << endl;
}

int main(){
    std::vector<int> v = {256, 64, 16*3, 16*9, 16, 8*7, 9, 3, 1, 6, 2, 5};
    print(v);
    
    int center = 50;
	std::sort(v.begin(), v.end(), [] (int x, int y ){return abs(x-50)<abs(y-50);}
	);            
    print(v);
	
    auto sharkovsky =  [](int x, int y){int xCoeff=1;int yCoeff=1;
                                        int xPower=0; int yPower=0;
                                        while(x%2==0){ xPower++; x/=2;} 
                                        xCoeff=x;
                                        while(y%2==0){ yPower++; y/=2;} 
                                        yCoeff=y;
                                        if(xCoeff==1){
                                            if(yCoeff==1){
                                                return xPower < yPower;
                                            }
                                            else{
                                                return true;
                                            }
                                        }
                                        else{
                                            if(yCoeff==1){
                                                return false;
                                            }
                                            else{
                                                if(xPower==yPower){
                                                    return xCoeff > yCoeff;
                                                }
                                                else{
                                                    return xPower > yPower;
                                                }
                                            }
                                        }
                                        } ;                  // ( 2 )
    
    assert(sharkovsky(1,2));	
    assert(sharkovsky(2,4));    
    assert(sharkovsky(64,256)); 
    assert(sharkovsky(256,256*3));  
    assert(sharkovsky(256*9,256*5));    
    assert(sharkovsky(256*3,64*9));    
    assert(!sharkovsky(1,1));	
    assert(!sharkovsky(4,2));
    assert(!sharkovsky(256,64));
    assert(!sharkovsky(256*3,256));
    assert(!sharkovsky(256*5,256*9));
    assert(!sharkovsky(64*9,256*3));

    std::sort(v.begin(), v.end(), sharkovsky);            
    print(v);
    
	srand(2019);
    int a = 0, b = 40;    
    auto generator = [&a,&b](){return (rand()%(b-a+1))+a;};                         // ( 3 )
    std::generate(v.begin(), v.end(), generator);          
    print(v);
    a = 100, b = 200;
    std::generate(v.begin(), v.end(), generator);  
    print(v); 
    a = -10; b=10;
    auto evenGenerator =  [a,b](){return (rand()%(b-a+1))+a;};     ;                   // ( 4 )
    std::generate(v.begin(), v.end(), evenGenerator);
    print(v);
    
    v.resize(20);
    a = 0; b=100;
    std::generate(v.begin(), v.end(), evenGenerator);
    print(v);
    
    
    auto l1_norm = [] (auto v){return std::accumulate(v.begin(),v.end(),0.0,[&](double a, double b){return a + abs(b);});} ;                      // ( 5 )    
    cout << l1_norm(v) << endl;

    vector<double> m = { 1.4, 2.4, -2.4, -4.2, -43.3 };
    cout << l1_norm(m) << endl;
    
    list<double> l(m.begin(), m.end());
    cout << l1_norm(l) << endl;
    
    auto wielomian = [](double* a, int n) { return [a,n](int x)    {  double sum=0.0;  double y = 1; for(int i = 0 ; i <= n ; i++){
                                                                                sum+=(a[i]*y);
                                                                                y*=x;
                                                                        }
                                                                        return sum; 
                                                                        }; };
    
    double c[] = {1, 2, 3, 4, 5};
    auto w1  = wielomian(c, 4);
    cout << w1(1.0) << " " << w1(0.0) << " " << w1(2.0) << endl;
   
    auto w2  = wielomian(c, 2);
    cout << w2(1.0) << " " << w2(0.0) << " " << w2(2.0) << endl;
    
    return 0;
}


/**
Expected output (or similar): 
256 64 48 144 16 56 9 3 1 6 2 5 
48 56 64 16 9 6 5 3 2 1 144 256 
1 2 16 64 256 144 48 56 6 9 5 3 
11 33 7 4 40 20 36 27 4 38 31 18 
142 135 106 164 160 189 152 196 156 102 198 114 
0 -2 -6 -8 -2 -10 -2 -4 -4 0 -8 0 
-6 -2 -4 -8 8 -6 0 -4 8 -2 6 8 -8 -8 2 10 10 -6 6 2 
114
53.7
53.7
15 1 129
6 1 17
*/
