#include<memory>
#include<iostream>
#include<string>

class String{
    public:
        String(size_t size);  // creates an empty string
        String(const char * ); // copy C-string
        String(const String& );  // no copy
        String operator=(const String &); // no copy // makes a copy of a string if it has more than one reference.
        char & operator[](int ); 
        // no copy
        char operator[](int ) const; 
        // concatenation creates a new string only if both strings are non empty
        friend String operator+(String , String ); // no copyfriend 
        friend std::ostream& operator<<(std::ostream & , String );
        inline int count()const{return ptr.use_count();} 
    private:
        std::shared_ptr<std::string> ptr;
};

String::String(size_t size = 0){
    ptr = std::make_shared<std::string>();
} 

String::String(const char* str){
    ptr = std::make_shared<std::string>(str);
}

String::String(const String& s){
    ptr = s.ptr;
}
String String::operator=(const String & s){
    ptr = s.ptr;
    return *this;
}

char& String::operator[](int i){
    if(ptr.use_count()>=1){
        std::shared_ptr<std::string> newPtr = std::make_shared<std::string>(*(ptr));
        this->ptr = newPtr;
        return (*newPtr)[i];
    }
    return (*ptr)[i];
}

char String::operator[](int i) const{
    return (*ptr)[i];
}

String operator+(String a, String b){
    if((a.ptr)->size()==0 && (b.ptr)->size()==0){
        String str;
        str.ptr = a.ptr;
        return str;
    }
    else{
        std::string s = *(a.ptr)+*(b.ptr);
        const char* c_str = s.c_str();
        String str(c_str);
        return str;  
    }
}

std::ostream& operator<<(std::ostream & out , String s){
    out << *(s.ptr);
    return out;
}


int main(){
    String a("hi");
    String b;
    const String c = a;
    std::cout<<a.count()<<std::endl;
    String d = a + b;
    a[0] = 'l';
    std::cout<<a.count()<<std::endl;
    a[1] = 'l';
    d = c + a ;
    std::cout << c << " " << d << std::endl;
    std::cout<< a[0] << std::endl;
    std::cout<< c.count() <<std::endl;
    return 0;
}