#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;
class Printer{
	public:
        Printer(ostream &os, string a, string b):str(os),left(a),right(b){}
        void operator()(string s){
            str << left << s <<right;
        }
        void operator()(int s){
            str << left << s <<right;
        }
        void operator()(double s){
            str << left << s <<right;
        }
        ~Printer(){}
    private:
        ostream& str;
        string left;
        string right;  
};

int main(){
  Printer print(std::cout,  "[ ", " ] " );   // creates unary functor 
                                          //that takes argument x of any type
                                          // and prints [ x ]
  print("hello");    // [ hello ]  
  std::vector<int> v = {1, 2, 3, 4};
  std::for_each(v.begin(), v.end(), print);  // [ 1 ] [ 2 ] [ 3 ] [ 4 ]  

  std::ofstream file("myFile.txt");
  Printer filePrinter(file, "- ", "\n");
  filePrinter(5);
  filePrinter("My text");	
	return 0;
}
