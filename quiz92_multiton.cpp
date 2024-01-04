
#include <iostream>
#include <vector>

template <class T>
class Multiton
{
public:
    Multiton(int num_instances);

    Multiton(const Multiton &) = delete;
    Multiton &operator=(const Multiton &) = delete;

    T *GetInstance(int index);

private:
    static std::vector<T *> m_instances;
    static bool m_atExit;
    static void CleanInstances(std::size_t numElementsToClean);
};

template <class T>
std::vector<T *> Multiton<T>::m_instances;
template <class T>
bool Multiton<T>::m_atExit = false;

int main()
{
    Multiton<double> multi(10);
    bool status = true;

    for (std::size_t i = 0; (i < 10) && status; ++i)
    {
        status = (multi.GetInstance(i) != nullptr && 
                  multi.GetInstance(i) == multi.GetInstance(i));
    }

    std::cout << "test1:    ";
    status ? std::cout << "SUCCESS ✅\n" : std::cout << "FAIL ❌\n";

    Multiton<double> multi2(20);

    for (std::size_t i = 0; (i < 20) && status; ++i)
    {
        status = (multi2.GetInstance(i) != nullptr && 
                  multi2.GetInstance(i) == multi.GetInstance(i));
    }

    std::cout << "test2:    ";
    status ? std::cout << "SUCCESS ✅\n" : std::cout << "FAIL ❌\n";
    
    Multiton<double> multi3(5);

    for (std::size_t i = 0; (i < 5) && status; ++i)
    {
        status = (multi3.GetInstance(i) != nullptr && 
                  multi3.GetInstance(i) == multi2.GetInstance(i) && 
                  multi3.GetInstance(i) == multi.GetInstance(i));
    }

    std::cout << "test3:    ";
    status ? std::cout << "SUCCESS ✅\n" : std::cout << "FAIL ❌\n";

    Multiton<double> multi4(25);

    for (std::size_t i = 0; (i < 25) && status; ++i)
    {
        status = (multi4.GetInstance(i) != nullptr && 
                  multi4.GetInstance(i) == multi3.GetInstance(i) && 
                  multi3.GetInstance(i) == multi2.GetInstance(i) &&
                  multi2.GetInstance(i) == multi.GetInstance(i));
    }

    std::cout << "test4:    ";
    status ? std::cout << "SUCCESS ✅\n" : std::cout << "FAIL ❌\n";

    return 0;
}

template <class T>
Multiton<T>::Multiton(int num_instances)
{
    if (1 > num_instances)
    {
        throw std::invalid_argument("num_instances must be greater than 0");
    }

    if (m_instances.size() > static_cast<std::size_t>(num_instances))
    {
        CleanInstances(m_instances.size() - num_instances);
    }
    m_instances.resize(num_instances, nullptr);

    if (!m_atExit)
    {
        std::atexit([]{CleanInstances(m_instances.size());});
        m_atExit = true;
    }
}

template <class T>
T *Multiton<T>::GetInstance(int index)
{
    if (0 > index || static_cast<std::size_t>(index) >= m_instances.size())
    {
        throw std::invalid_argument("invalid index");
    }

    if (nullptr == m_instances[index])
    {
        m_instances[index] = new T();
    }

    return m_instances[index];
}

template <class T>
void Multiton<T>::CleanInstances(std::size_t numElementsToClean)
{
    std::size_t endIndx = m_instances.size() - 1;

    for (std::size_t i = 0; i < numElementsToClean; ++i)
    {
        delete m_instances[endIndx - i];
    }
}