
#include <iostream>
#include <cstring>
#include <cassert>

class String
{
public:
    String(const char *str = "");
    String(const String& str);
    ~String();

    String& operator=(const String& str);
    friend std::ostream& operator<<(std::ostream& os, const String& str);
    friend std::istream& operator>>(std::istream& is, String& str);

private:
    char *DupStr(const char *str);
    char *m_str;
};

template <typename T> class Point;
template <typename T> std::ostream& operator<<(std::ostream&, const Point<T>& );

template <typename T>
class Point
{
public:
    explicit Point(const T& x = 0, const T& y = 0);
    Point(const Point& p);
    ~Point();

    Point& operator=(const Point& p);
    const Point operator+(const Point& p) const;
    const Point operator-(const Point& p) const;
    bool operator==(const Point& p) const;
    Point& operator+=(const T& p);
    Point& operator/=(const T& p);
    friend std::ostream& operator<< <T>(std::ostream& os, const Point<T>& p);

private:
    T m_x;
    T m_y;
};

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

String::String(const char *str) : m_str(DupStr(str))
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

    return *this;
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
    os << str.m_str;
    
    return os;
}

std::istream& operator>>(std::istream& is, String& str)
{
    is >> str.m_str;
    
    return is;
}

char *String::DupStr(const char *str)
{
    std::size_t len = strlen(str) + 1;
    char *newStr = new char[len + 1];
    std::memcpy(newStr, str, len);

    return newStr;
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

template <typename T>
Point<T>::Point(const T& x, const T& y) : m_x(x), m_y(y)
{}

template <typename T>
Point<T>::Point(const Point &p) : m_x(p.m_x), m_y(p.m_y)
{}

template <typename T>
Point<T>::~Point()
{}

template <typename T>
Point<T>& Point<T>::operator=(const Point &p)
{
    m_x = p.m_x;
    m_y = p.m_y;

    return *this;
}

template <typename T>
const Point<T> Point<T>::operator+(const Point &p) const
{
    Point<T> tmp(m_x + p.m_x, m_y + p.m_y);

    return tmp;
}

template <typename T>
const Point<T> Point<T>::operator-(const Point &p) const
{
    Point<T> tmp(m_x - p.m_x, m_y - p.m_y);

    return tmp;
}

template <typename T>
bool Point<T>::operator==(const Point &p) const
{
    return ((m_x == p.m_x) && (m_y == p.m_y));
}

template <typename T>
Point<T>& Point<T>::operator+=(const T& p)
{
    m_x += p;
    m_y += p;

    return *this;
}

template <typename T>
Point<T>& Point<T>::operator/=(const T& p)
{
    m_x /= p;
    m_y /= p;

    return *this;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Point<T>& p)
{
    os << "(" << p.m_x << ", " << p.m_y << ")";

    return os;
}
