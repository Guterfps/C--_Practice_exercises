
#include <iostream>

template <class T>
class make_adder
{
public:
    make_adder(T add);

    const T operator()(const T& add_to) const;

private:
    T m_add;
};

int main(void)
{
    make_adder<int> add_4 = make_adder<int>(4);

    std::cout << "make_adder tests:\n";
    (9 == add_4(5)) ? std::cout << "Success ✅\n" : std::cout << "Fail ❌\n";
    (12 == add_4(8)) ? std::cout << "Success ✅\n" : std::cout << "Fail ❌\n";

    return 0;
}

template <class T>
make_adder<T>::make_adder(T add) : m_add(add)
{}

template <class T>
const T make_adder<T>::operator()(const T& add_to) const
{
    return (add_to + m_add);
}