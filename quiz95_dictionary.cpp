
#include <iostream>
#include <string>
#include <unordered_map>
#include <set>

class Dictionary
{
public:

    void Insert(const std::string& key, int value);
    int Search(const std::string& key);
    void Delete(const std::string& key);
    int Size() const;
    int Min() const;
    int Max() const;

private:
    std::unordered_map<std::string, std::multiset<int>::iterator> m_dict;
    std::multiset<int> m_values;

};

int main()
{
    Dictionary dict;
    bool status = true;

    for (std::size_t i = 0; (i < 10000) && status; ++i)
    {
        dict.Insert("key" + std::to_string(i), i);
        status = (dict.Search("key" + std::to_string(i)) == static_cast<int>(i));
    }

    for (std::size_t i = 2000; (i < 5000) && status; ++i)
    {
        dict.Insert(std::to_string(i), i);
        status = (dict.Search(std::to_string(i)) == static_cast<int>(i));
    }

    std::cout << "insert test:  ";
    std::cout << ((dict.Size() == 13000) ? "SUCCESS ✅" : "FAIL ❌") << ", ";
    std::cout << ((dict.Min() == 0) ? "SUCCESS ✅" : "FAIL ❌") << ", ";
    std::cout << ((dict.Max() == 9999) ? "SUCCESS ✅" : "FAIL ❌") << ", ";
    std::cout << (status ? "SUCCESS ✅" : "FAIL ❌") << std::endl;
    
    for (std::size_t i = 0; (i < 1000); ++i)
    {
        dict.Delete("key" + std::to_string(i));
        dict.Delete("key" + std::to_string(9999 - i));
    }

    for (std::size_t i = 2000; (i < 5000); ++i)
    {
        dict.Delete(std::to_string(i));
    }

    for (std::size_t i = 1000; (i < 8999) && status; ++i)
    {
        status = (dict.Search("key" + std::to_string(i)) == static_cast<int>(i));
    }

    std::cout << "delete test:  ";
    std::cout << ((dict.Size() == 8000) ? "SUCCESS ✅" : "FAIL ❌") << ", ";
    std::cout << ((dict.Min() == 1000) ? "SUCCESS ✅" : "FAIL ❌") << ", ";
    std::cout << ((dict.Max() == 8999) ? "SUCCESS ✅" : "FAIL ❌") << ", ";
    std::cout << (status ? "SUCCESS ✅" : "FAIL ❌") << std::endl;

    return 0;
}

void Dictionary::Insert(const std::string& key, int value)
{
    if (m_dict.find(key) != m_dict.end())
    {
        m_values.erase(m_dict[key]);
    }

    m_dict[key] = m_values.insert(value);

}

int Dictionary::Search(const std::string& key)
{
    if (m_dict.find(key) == m_dict.end())
    {
        throw std::runtime_error("Key not found");
    }

    return (*(m_dict.at(key)));
}

void Dictionary::Delete(const std::string& key)
{
    if (m_dict.find(key) == m_dict.end())
    {
        throw std::runtime_error("Key not found");
    }

    m_values.erase(m_dict[key]);
    m_dict.erase(key);
}

int Dictionary::Size() const
{
    return (m_dict.size());
}

int Dictionary::Min() const
{
    if (m_values.empty())
    {
        throw std::runtime_error("Empty dictionary");
    }

    return (*(m_values.begin()));
}

int Dictionary::Max() const
{
    if (m_values.empty())
    {
        throw std::runtime_error("Empty dictionary");
    }

    return (*(m_values.rbegin()));
}
