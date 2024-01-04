
#include <iostream>
#include <unordered_map>
#include <list>
#include <iterator>

template <class T>
class LRUCache
{
public:
    explicit LRUCache(std::size_t capacity);

    void Put(int key, const T& value);
    const T& Get(int key) const;
    void Print() const;

private:
    typedef typename std::list<std::pair<int, T> >::iterator iterator;
    std::size_t m_capacity;
    std::list<std::pair<int, T> > m_queue;
    std::unordered_map<int, iterator> m_cache;
};

int main(void)
{
    LRUCache<int> cache(3);

    cache.Put(1, 1);
    cache.Put(2, 2);
    cache.Put(3, 3);

    for (std::size_t i = 1; i <= 3; ++i)
    {
        std::cout << cache.Get(i) << std::endl;
    }
    cache.Print();
    
    cache.Put(4, 4);
    cache.Put(3, 5);
    cache.Put(1, 7);

    cache.Print();

    return 0;
}

template <class T>
LRUCache<T>::LRUCache(std::size_t capacity) : m_capacity(capacity)
{}

template <class T>
void LRUCache<T>::Put(int key, const T& value)
{
    if (m_cache.find(key) == m_cache.end())
    {
        if (m_queue.size() >= m_capacity)
        {
            std::pair<int, T> last = m_queue.back();
            m_queue.pop_back();
            m_cache.erase(last.first);
        }
    }
    else
    {
        m_queue.erase(m_cache[key]);
    }

    m_queue.push_front(std::make_pair(key, value));
    m_cache[key] = m_queue.begin();
}

template <class T>
const T& LRUCache<T>::Get(int key) const
{
    auto it = m_cache.find(key);
    if (it == m_cache.end())
    {
        throw std::runtime_error("key not found");
    }

    return (it->second->second);
}

template <class T>
void LRUCache<T>::Print() const
{
    for (const auto& item : m_queue)
    {
        std::cout << "key: " << item.first << " value: " << item.second << '\n';
    }
    std::cout << std::endl;
}