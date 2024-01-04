
#include <iostream>
#include <cstring>
#include <cassert>

class String
{
public:
    String(const char* str = "");
    String(const String& str);
    ~String();

    String& operator=(const String& str);
    char *c_str() const;

private:
    char* m_str;
    static char *DupStr(const char *str);

};

std::ostream& operator<<(std::ostream& os, const String& str);
std::istream& operator>>(std::istream& is, String& str);

template <typename T>
class Point
{
public:
    explicit Point(const T& x = 0, const T& y = 0);
    
    const Point operator+(const Point& p) const;
    const Point operator-(const Point& p) const;
    Point& operator+=(const T& value);
    Point& operator/=(const T& value);
    bool operator==(const Point& other) const;

    const T& GetX() const;
    const T& GetY() const;

private:
    T m_x;
    T m_y;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Point<T>& p);

void TestString(void);
void TestPoint(void);

int main(void)
{
    TestString();
    TestPoint();

    return 0;
}

void TestString(void)
{
    String str1 = "Hello world";
    String str2(str1);
    str1 = str1;
    str2 = str1;
    std::cout << str2 << std::endl;
    std::cin >> str1;
    std::cout << str1 << std::endl;
}

String::String(const char* str) : m_str(DupStr(str))
{}

String::String(const String& str) : m_str(DupStr(str.m_str))
{}

String::~String()
{
    delete[] m_str;
    m_str = 0;
}

String& String::operator=(const String& str)
{
    char *tmp = m_str;
    m_str = DupStr(str.m_str);
    delete[] tmp;
    tmp = 0;

    return *this;
}

char *String::c_str() const
{
    return m_str;
}

char *String::DupStr(const char *str)
{
    std::size_t len = strlen(str) + 1;
    char *newStr = new char[len];
    std::memcpy(newStr, str, len);

    return newStr;
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
    return (os << str.c_str());
}

std::istream& operator>>(std::istream& is, String& str)
{
    return (is >> str.c_str());
}


void TestPoint(void)
{
    Point<int> p1(5, 6);
    Point<int> p2(12, 18);
    Point<int> p3;
    p3 = p1 + p2;
    Point<int> p4 = p3 - p1;
    Point<int> p5(0, 0);
    std::cout << "point tests:\n";
    assert(p4 == p2);
    (p4 == p2) ? std::cout << "SUCCESS ✅\n" :  std::cout << "FAIL  ❌\n";
    Point<int> p6(p1);
    p6 += 1;
    assert(p6 == Point<int>(6, 7));
    (p6 == Point<int>(6, 7)) ? 
    std::cout << "SUCCESS ✅\n" :  std::cout << "FAIL  ❌\n";
    p2 /= 2;
    assert(p2 == Point<int>(6, 9));
    (p2 == Point<int>(6, 9)) ? 
    std::cout << "SUCCESS ✅\n" :  std::cout << "FAIL  ❌\n";

    std::cout << "points: " << p1 << ", " << p2 << ", " << p3 << ", " << p4 <<
                ", " << p5 << ", " << p6 << std::endl;
}

template  <typename T>
Point<T>::Point(const T& x, const T& y) : m_x(x), m_y(y)
{}

template <typename T>
const Point<T> Point<T>::operator+(const Point<T>& p) const
{
    return Point<T>(m_x + p.m_x, m_y + p.m_y);
}

template <typename T>
const Point<T> Point<T>::operator-(const Point<T>& p) const
{
    return Point<T>(m_x - p.m_x, m_y - p.m_y);
}

template  <typename T>
Point<T>& Point<T>::operator+=(const T& value)
{
    return (*this = *this + Point<T>(value, value));
}

template <typename T>
Point<T>& Point<T>::operator/=(const T& value)
{
    m_x /= value;
    m_y /= value;

    return *this;
}

template <typename T>
bool Point<T>::operator==(const Point<T>& other) const
{
    return ((m_x == other.m_x) && (m_y == other.m_y));
}

template <typename T>
const T& Point<T>::GetX() const
{
    return m_x;
}

template <typename T>
const T& Point<T>::GetY() const
{
    return m_y;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Point<T>& p)
{
    return (os << "(" << p.GetX() << ", " << p.GetY() << ")");
}