
#include <iostream>
#include <cstdlib>
#include <ctime>

class Node;

class List
{
public:
    List();
    ~List();
    void InsertFirst(Node *node);
    void InsertLast(Node *node);
    const Node *GetFirst() const;
    const Node *GetLast() const;
    size_t GetNumOfElements() const;
    void Remove(const Node *node);

private:
    size_t m_size;
    Node *m_dummy;
};

class Node
{
public:
    Node();
    void Tie(Node *prev);
    void UnTie();

private:
    Node *m_next;
    Node *m_prev;

    friend class List;
};

void TestList();

int main(void)
{
    TestList();

    return 0;
}

void TestList()
{
    Node nodes[10];
    List list;

    srand(time(0));

    for (size_t i = 0; i < 10; ++i)
    {
        if (rand() % 2)
        {
            list.InsertFirst(&nodes[i]);
        }
        else
        {
            list.InsertLast(&nodes[i]);
        }
    }

    (10 == list.GetNumOfElements()) ? 
    std::cout << "SUCCESS ✅\n" : std::cout << "FAIL ❌\n";

    const Node *first = list.GetFirst();
    const Node *last = list.GetLast();

    for (size_t i = 0; i < 10; ++i)
    {
        if (first != &nodes[i] &&
            last != &nodes[i])
        {
            list.Remove(&nodes[i]);
        }
    }

    std::cout << "size: " << list.GetNumOfElements() << "\n";

}

Node::Node() : m_next(0), m_prev(0)
{}

void Node::Tie(Node *prev)
{
    m_prev = prev;
    prev->m_next = this;
}

void Node::UnTie()
{
    m_next->Tie(m_prev);
}

List::List() : m_size(0), m_dummy(new Node)
{
    m_dummy->Tie(m_dummy);
}

List::~List()
{
    delete m_dummy;
}

void List::InsertFirst(Node *node)
{
    m_dummy->m_next->Tie(node);
    node->Tie(m_dummy);
    ++m_size;
}

void List::InsertLast(Node *node)
{
    node->Tie(m_dummy->m_prev);
    m_dummy->Tie(node);
    ++m_size;
}

void List::Remove(const Node *node)
{
    const_cast<Node *>(node)->UnTie();
    --m_size;
}

const Node *List::GetFirst() const
{
    return (m_dummy->m_next);
}

const Node *List::GetLast() const
{
    return (m_dummy->m_prev);
}

size_t List::GetNumOfElements() const
{
    return m_size;
}

