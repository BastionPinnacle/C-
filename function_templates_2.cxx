#include<string>
#include<iostream>
#include<vector>
#include<list>
#include<cmath>


template<typename T>
int compare(T a, T b){
    if(a<b){
        return 1;
    }
    else if(a>b){
        return -1;
    }
    else{
        return 0;
    }
}
template<typename T>
int compare(T* a, T* b){
    if(*a<*b){
        return 1;
    }
    else if(*a>*b){
        return -1;
    }
    else{
        return 0;
    }
}
template <>
int compare<const char>(const char* a,const char* b){
    int aLength = 0;
    while(a[aLength]!='\0'){
        aLength++;
    }
    int bLength = 0;
    while(b[bLength]!='\0'){
        bLength++;
    }
    int i = 0 ;
    while(true){
        if(i<aLength && i<bLength){
            if(a[i]<b[i])return 1;
            else if(a[i]>b[i])return -1;
            else i++;
        }
        else{
            if(i>=aLength){
                if(i>=bLength){
                    return 0;
                }
                else{
                    return 1;
                }
            }
            return -1;
        }
    }
}




using namespace std;
int main(){
    int a = 1, b=-6;
    float  y= 1.0 + 1e20 - 1e20, x = 1.0;
    cout << compare(a,b) << " " << compare(b,a) << " " << compare(a,a) << endl;
    cout << compare(x,y) << " " << compare(y,x) << " " << compare(x,x) << endl;
    cout << compare(&a,&b) << " " << compare(&b,&a) << " " << compare(&a,&a) <<endl;
    cout << compare(&x,&y) << " " << compare(&y,&x) << " " << compare(&x,&x) <<endl;
    cout << compare("Alpha", "Alfa") <<endl;
}