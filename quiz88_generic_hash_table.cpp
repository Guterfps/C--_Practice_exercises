
#include <iostream>
#include <list>
#include <functional>
#include <algorithm>

template <typename Key, typename Value, std::size_t NumOfBuckets>
class HashTable
{
public:
    HashTable(std::function<std::size_t(const Key&)> hashFunc);

    void Insert(const Key& key, const Value& value);
    void Remove(const Key& key);
    Value& Find(const Key& key);
    std::size_t Size() const
    {
        return m_size;
    }

private:
    std::list<std::pair<Key, Value>> m_buckets[NumOfBuckets];
    std::function<std::size_t(const Key&)> m_hashFunc;
    std::size_t m_size;
};

int main()
{
    HashTable<int, std::size_t, 10> table([](const int& key) { return (key % 10);});

    for (std::size_t i = 0; i < 100; ++i)
    {
        table.Insert(i, i * 10);
    }

    bool status = true;

    for (std::size_t i = 0; (i < 100) && status; ++i)
    {
        status = (table.Find(i) == (i * 10));
    }

    std::cout << "Hash table test: ";
    status ? std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌， ";
    (100 == table.Size()) ? 
    std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌, ";

    for (std::size_t i = 0; (i < 100) && status; ++i)
    {
        if (0 == (i % 3))
        {
            table.Remove(i);
            try
            {
                table.Find(i);
            }
            catch (const std::runtime_error& e)
            {
                continue;
            }
            status = false;
        }
    }

    status ? std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌， ";

    for (std::size_t i = 0; (i < 100) && status; ++i)
    {
        if (0 != (i % 3))
        {
            status = (table.Find(i) == (i * 10));
        }
    }

    status ? std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌， ";
    (66 == table.Size()) ?
    std::cout << "SUCCESS ✅\n" : std::cout << "FAIL ❌\n";

    return 0;
}

template <typename Key, typename Value, std::size_t NumOfBuckets>
HashTable<Key, Value, NumOfBuckets>::
HashTable(std::function<std::size_t(const Key&)> hashFunc) : 
m_hashFunc(hashFunc), m_size(0)
{}

template <typename Key, typename Value, std::size_t NumOfBuckets>
void HashTable<Key, Value, NumOfBuckets>::
Insert(const Key& key, const Value& value)
{
    std::size_t bucket = m_hashFunc(key) % NumOfBuckets;
    m_buckets[bucket].push_back(std::make_pair(key, value));
    ++m_size;
}

template <typename Key, typename Value, std::size_t NumOfBuckets>
void HashTable<Key, Value, NumOfBuckets>::Remove(const Key& key)
{
    std::size_t bucket = m_hashFunc(key) % NumOfBuckets;
    
    auto it = std::find_if(m_buckets[bucket].begin(), m_buckets[bucket].end(), 
    [&key](const std::pair<Key, Value>& pair)
    {
        return (key == pair.first);
    });

    if (it != m_buckets[bucket].end())
    {
        m_buckets[bucket].erase(it);
        --m_size;
    }
}

template <typename Key, typename Value, std::size_t NumOfBuckets>
Value& HashTable<Key, Value, NumOfBuckets>::Find(const Key& key)
{
    std::size_t bucket = m_hashFunc(key) % NumOfBuckets;
    auto it = std::find_if(m_buckets[bucket].begin(), m_buckets[bucket].end(), 
    [&key](const std::pair<Key, Value>& pair)
    {
        return (key == pair.first);
    });

    if (it == m_buckets[bucket].end())
    {
        throw std::runtime_error("Key not found");
    }

    return it->second;
}