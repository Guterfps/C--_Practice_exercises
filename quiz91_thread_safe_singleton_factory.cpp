
#include <iostream>
#include <functional>
#include <unordered_map>
#include <mutex>
#include <atomic>
#include <future>
#include <string>
#include <vector>

class Base
{
public:
    Base(int data) : m_data(data) {}
    virtual ~Base() = default;

    static Base *Create(const int& data)
    {
        return new Base(data);
    }
    virtual long GetData() const { return m_data; }
    
private:
    int m_data;
};

template <class T, class K, class D>
class Factory
{
public:
    Factory(const Factory&) = delete;
    Factory& operator=(const Factory&) = delete;

    static Factory& getInstance();
    void Add(const K& key, std::function<T*(const D&)> creator);
    T *Create(const K& key, const D& data);


private:
    Factory() = default;
    ~Factory() = default;

    std::unordered_map<K, std::function<T*(const D&)>> m_creators;
    std::mutex m_mutex;
    std::atomic<std::size_t> m_count{0};

};

class Derived1 : public Base
{
public:
    Derived1(int data, long moreData) : Base(data), m_moreData(moreData) {}

    static Derived1 *Create(const int& data)
    {
        return new Derived1(data, data * data);
    }
    long GetData() const {return (m_moreData * Base::GetData());}

private:
    long m_moreData;
};

class Derived2 : public Base
{
public:
    Derived2(int data, long moreData) : Base(data), m_moreData(moreData) {}

    static Derived2 *Create(const int& data)
    {
        return new Derived2(data, data + data);
    }
    long GetData() const {return (m_moreData / Base::GetData());}

private:
    long m_moreData;
};

int main()
{
    std::vector<std::future<Base*>> futures;
    std::atomic<std::size_t> count(0);
    std::string keys[3] = {"Base", "Derived1", "Derived2"};
    std::function<Base*(const int&)> creators[3] = 
    {&Base::Create, &Derived1::Create, &Derived2::Create};

    for (std::size_t i = 0; i < 100; ++i)
    {
        futures.emplace_back(std::async(std::launch::async,
        [i, &count, &keys, &creators]
        {
            auto& factory = Factory<Base, std::string, int>::getInstance();
            factory.Add(keys[i % 3], creators[i % 3]);
            Base *object = nullptr;
            try
            {
                object = factory.Create(keys[(i - 1) % 3], i + 1);
            } 
            catch (std::exception& e)
            {
                return object;
            }

            count.fetch_add(object->GetData(), std::memory_order_relaxed);
            
            return object;
        }));
    }

    for (auto& f : futures)
    {
        delete f.get();
    }

    std::cout << "count: ";
    std::cout << count.load() << std::endl;

    return 0;
}

template <class T, class K, class D>
Factory<T, K, D>& Factory<T, K, D>::getInstance()
{
    static Factory<T, K, D> instance;

    return instance;
}

template <class T, class K, class D>
void Factory<T, K, D>::Add(const K& key, std::function<T*(const D&)> creator)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    while (m_count.load(std::memory_order_relaxed) > 0);
    m_creators[key] = creator;
}

template <class T, class K, class D>
T *Factory<T, K, D>::Create(const K& key, const D& data)
{
    m_mutex.lock();
    m_count.fetch_add(1, std::memory_order_acquire);
    m_mutex.unlock();

    std::function<T*(const D&)> creator;
    try
    {
        creator = m_creators.at(key);
    } 
    catch (std::exception& e) 
    {
        m_count.fetch_sub(1, std::memory_order_release);
        throw std::runtime_error("Unknown key");
    }
    m_count.fetch_sub(1, std::memory_order_release);

    return creator(data);
}