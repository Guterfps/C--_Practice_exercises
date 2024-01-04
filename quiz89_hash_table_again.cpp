
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

template <class Key, class Value, class Hash = std::hash<Key>>
class HashTable
{
public:
    void Insert(const Key& key, const Value& value);
    void Remove(const Key& key);
    Value& Find(const Key& key);
    std::size_t Size() const;

private:
    std::vector<std::list<std::pair<Key, Value>>> m_table;
    Hash m_hash;
    std::size_t m_size{0};

    typename std::list<std::pair<Key, Value>>::iterator 
    FindIter(const Key& key, std::size_t bucket);
};

int main()
{
    HashTable<int, std::size_t, std::hash<int>> table;

    table.Insert(1000, 123);

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
    (101 == table.Size()) ? 
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
    
    (123 == table.Find(1000)) ? 
    std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌， ";

    status ? std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌， ";
    (67 == table.Size()) ?
    std::cout << "SUCCESS ✅\n" : std::cout << "FAIL ❌\n";


    return 0;
}

template <class Key, class Value, class Hash>
void HashTable<Key, Value, Hash>::Insert(const Key& key, const Value& value)
{
    std::size_t bucket = m_hash(key);

    if (bucket >= m_table.size())
    {
        m_table.resize(bucket + 1);
    }
    m_table[bucket].push_back(std::make_pair(key, value));
    ++m_size;
}

template <class Key, class Value, class Hash>
void HashTable<Key, Value, Hash>::Remove(const Key& key)
{
    std::size_t bucket = m_hash(key);
    auto it = FindIter(key, bucket);
    m_table[bucket].erase(it);
    --m_size;
}

template <class Key, class Value, class Hash>
Value& HashTable<Key, Value, Hash>::Find(const Key& key)
{
    std::size_t bucket = m_hash(key);
    auto it = FindIter(key, bucket);
    
    return it->second;
}

template <class Key, class Value, class Hash>
std::size_t HashTable<Key, Value, Hash>::Size() const
{
    return m_size;
}

template <class Key, class Value, class Hash>
typename std::list<std::pair<Key, Value>>::iterator 
HashTable<Key, Value, Hash>::FindIter(const Key& key, std::size_t bucket)
{
    if (bucket >= m_table.size())
    {
        throw std::runtime_error("Key not found");
    }

    auto it = std::find_if(m_table[bucket].begin(), m_table[bucket].end(), 
    [&key](const std::pair<Key, Value>& pair) 
    { 
        return (key == pair.first); 
    });
    if (it == m_table[bucket].end())
    {
        throw std::runtime_error("Key not found");
    }

    return it;
}