
#include <cstddef>
#include <cstring>
#include <iostream>

class String
{
public:
    String(const char *str = "");
    String(const String& str);
    ~String();
    
    String& operator=(const String& str);
    char& operator[](std::size_t indx);
    friend std::ostream& operator<<(std::ostream& os, const String& str);

private:
    static char *AllocNewStr(const char *str);
    
    char *string;
};


int main(void)
{
    String s1("aaa");
    String s2 = "bbb";
    String s3(s2);
    String s4;
    
    s4 = s2;
    s3[2] = 'k';
    s2 = s2;
    
    std::cout << "s1: " << s1 << '\n';
    std::cout << "s2: " << s2 << '\n';
    std::cout << "s3: " << s3 << '\n';
    std::cout << "s4: " << s4 << '\n';
    
    return 0;
}

String::String(const char *str) : string(AllocNewStr(str))
{
}

String::String(const String& str) : string(AllocNewStr(str.string))
{
}

String::~String()
{
    delete[] string;
}

String& String::operator=(const String& str)
{
    char *temp = AllocNewStr(str.string);
    delete[] string;
    string = temp;

    return *this;
}

char& String::operator[](std::size_t indx)
{
    return string[indx];
}

char *String::AllocNewStr(const char *str)
{
    std::size_t len = std::strlen(str) + 1;
    char *newStr = new char[len];
    std::memcpy(newStr, str, len);
    
    return newStr;
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
    return (os << str.string);
}

