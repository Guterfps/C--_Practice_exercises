
#include <iostream>

class NonCopyable
{
protected:
    NonCopyable(void) {}
    ~NonCopyable() {}

private:
    NonCopyable(const  NonCopyable&);
    NonCopyable& operator=(const NonCopyable&);
};

template <typename T>
class Stack : private NonCopyable
{
public:
    Stack(void);
    ~Stack();

    void Push(const T& item);
    void Pop(void);
    T Peek(void) const;

private:
    template <typename Type>
    struct Node
    {
        Type data;
        Node<Type> *next;
    };

    Node<T> *top;
};

int main(void)
{
    Stack<int> s;
    int status = 1;

    std::cout << "Stack test:   ";
    int i = 0;
    for (; i < 10000; ++i)
    {
        s.Push(i);
    }

    for (i -= 1; (i > 0) && status; --i)
    {
        status = (s.Peek() == i);
        s.Pop();
    }
    
    std::cout << (status ? "SUCCESS ✅" : "FAIL ❌") << std::endl;

    return 0;
}

template <typename T>
Stack<T>::Stack(void) : NonCopyable(), top(0)
{}

template <typename T>
Stack<T>::~Stack(void)
{
    while(top)
    {
        Pop();
    }
}

template <typename T>
void Stack<T>::Push(const T& item)
{
    Node<T> *newNode = new Node<T>;
    newNode->data = item;
    newNode->next = top;
    top = newNode;
}

template <typename T>
void Stack<T>::Pop(void)
{
    Node<T> *temp = top;
    top = top->next;
    delete temp;
    temp = 0;
}

template <typename T>
T Stack<T>::Peek(void) const
{
    return (top->data);
}
