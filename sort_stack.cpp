
#include <stack>
#include <iostream>
#include <random>
#include <functional>

void IterativeSortStack(std::stack<int> *st);
void RecSortStack(std::stack<int> *st);
void RecSortInsert(std::stack<int> *st, int num);
bool IsStackSorted(std::stack<int> st);
void TestSortStack(std::function<void(std::stack<int> *st)> sort_func);


int main(void)
{
    std::cout << "Iterative sort:\n";
    TestSortStack(&IterativeSortStack); 

    std::cout << "Recursive sort:\n";
    TestSortStack(&RecSortStack);
}

void IterativeSortStack(std::stack<int> *st)
{
    std::stack<int> tmp_st;

    while (!st->empty())
    {
        int tmp = st->top();
        st->pop();

        while (!tmp_st.empty() && tmp_st.top() > tmp)
        {
            st->push(tmp_st.top());
            tmp_st.pop();
        }

        tmp_st.push(tmp);
    }

    while (!tmp_st.empty())
    {
        st->push(tmp_st.top());
        tmp_st.pop();       
    }
}

void RecSortStack(std::stack<int> *st)
{
    if (!st->empty())
    {
        int tmp = st->top();
        st->pop();

        RecSortStack(st);

        RecSortInsert(st, tmp);
    }
}

void RecSortInsert(std::stack<int> *st, int num)
{
    if (st->empty() || (num < st->top()))
    {
        st->push(num);
    }
    else
    {
        int tmp = st->top();
        st->pop();
        RecSortInsert(st, num);
        st->push(tmp);
    }
}

bool IsStackSorted(std::stack<int> st)
{
    int prev = st.top();
    bool status = true;
    
    while (!st.empty() && status)
    {
        status = st.top() >= prev;
        prev = st.top();
        st.pop();
    }

    return status;
}

void TestSortStack(std::function<void(std::stack<int> *st)> sort_func)
{
    std::stack<int> st;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(-10,10);

    st.push(dist(rng));
    st.push(dist(rng));
    st.push(dist(rng));
    st.push(dist(rng));
    st.push(dist(rng));
    st.push(dist(rng));

    std::cout << "is stack sorted before: " << 
    (IsStackSorted(st) ? "yes" : "no") << '\n'; 

    sort_func(&st);

    std::cout << "is stack sorted after: " << 
    (IsStackSorted(st) ? "yes✅" : "no❌") << '\n'; 
}