
#include <iostream>
#include <cstring>

class String
{
public:
    String(const char* str = "ABC");
    String(const String& str);
    ~String();

    char& operator[](std::size_t index);
    void operator=(const String& str);
    void operator=(char ch);
    static std::size_t GetInstances();

    const char *Cstr() const;

private:
    char *m_str;
    static std::size_t m_instances;
    static char *DupStr(const char *str);

};


int main(void)
{
    String s0;
    std::cout << s0.Cstr() << std::endl;

    String s1("1234");
    String s2(s1);
    std::cout << s2.Cstr() << std::endl;

    s1[0] = 'r';
    s2[0] = s1[0];
    std::cout << s1.Cstr() << std::endl;
    std::cout << s2.Cstr() << std::endl;

    s1 = "abc";
    std::cout << s1.Cstr() << std::endl;
    s2 = s1;
    std::cout << s2.Cstr() << std::endl;
    s1 = 'A';
    std::cout << s1.Cstr() << std::endl;

    s2 = s2;
   // s0 = s1 = s2;

    std::cout << String::GetInstances() << std::endl;

    String S1("1234");
    S1 = '@';
    std::cout << S1.Cstr() << std::endl;
    String *S2 = new String;
    std::cout << S2->Cstr() << std::endl;
    std::cout << String::GetInstances() << std::endl;
    delete S2;
    std::cout << String::GetInstances() << std::endl;

    return 0;
}

std::size_t String::m_instances = 0;

String::String(const char *str) : m_str(DupStr(str))
{
    ++m_instances;
}

String::String(const String& str) : m_str(DupStr(str.m_str))
{
    ++m_instances;
}

String::~String()
{
    delete[] m_str;
    m_str = 0;
    --m_instances;
}

char& String::operator[](std::size_t index)
{
    return (m_str[index]);
}

void String::operator=(const String& str)
{
    char *temp = m_str;
    m_str = DupStr(str.m_str);
    delete[] temp;
    temp = 0;
}

void String::operator=(char ch)
{
    std::memset(m_str, ch, std::strlen(m_str));
}

std::size_t String::GetInstances()
{
    return m_instances;
}

const char *String::Cstr() const
{
    return m_str;
}

char *String::DupStr(const char *str)
{
    std::size_t len = std::strlen(str) + 1;
    char *newStr = new char[len];
    std::memcpy(newStr, str, len);

    return newStr;
}