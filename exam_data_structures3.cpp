
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <set>
#include <vector>
#include <stack>
#include <list>
#include <iterator>

typedef std::pair<int, size_t> element_t;

struct int_array_t
{
    std::size_t size;
    std::size_t gen;
    int val;
    element_t arr[1];
};


int_array_t *CreateArr(std::size_t size);
void DestroyArr(int_array_t *arr);
void SetVal(int_array_t *arr, int indx, int val);
int GetVal(int_array_t *arr, int indx);
void SetAll(int_array_t *arr, int val);

bool FindSumOfTwo(unsigned int *arr, std::size_t size,  unsigned int sum);

bool FindChar(char *arr, std::size_t size, char c);

void ShiftNBytesInPlace(char *arr, std::size_t size, std::size_t n);
void ReverseChars(char *start, char *end);

std::size_t CountIslands(std::vector<std::vector<bool> > map);
void MarkIsland(std::vector<std::vector<bool> >& map, 
                std::size_t i, std::size_t j, 
                std::size_t Rows, std::size_t Cols);

template<class type>
class MinStack
{
public:
    void Push(type val);
    void Pop();
    type Top();
    type Min();

private:
    std::stack<type> m_data;
    std::stack<type> m_min;
};

bool CheckParantheses(char *str);
bool CheckStack(char *str, std::stack<char>& stack);

int RecMulty(int a, int b);
int RecInc(int num);

void PivotSort(std::list<int>& list, int pivot);

enum children
{
	LEFT = 0,
	RIGHT,
	NUM_OF_CHILDREN
};

struct tree_node
{
	tree_node(int data) : data(data) {}
    int data;
	tree_node *child[NUM_OF_CHILDREN];
};

int IterInsert(tree_node *root, int data);
tree_node *RecInsert(tree_node *root, int data);

void TestIntArr(void);
void TestFindSumOfTwo(void);
void TestFindChar(void);
void TestShiftNBytesInPlace(void);
void TestCountIslands(void);
void TestMinStack(void);
void TestCheckParantheses(void);
void TestRecMulty(void);
void TestRecInc(void);
void TestPivotSort(void);

int main(void)
{
    TestIntArr();
    TestFindSumOfTwo();
    TestFindChar();
    TestShiftNBytesInPlace();
    TestCountIslands();
    TestMinStack();
    TestCheckParantheses();
    TestRecMulty();
    TestRecInc();
    TestPivotSort();


    return 0;
}

void TestIntArr(void)
{
    const std::size_t SIZE = 10;
    int_array_t *arr = CreateArr(SIZE);
    int status = 1;

    for (std::size_t i = 0; i < SIZE; ++i)
    {
        SetVal(arr, i, i);
    }
    
    for (std::size_t i = 0; (i < SIZE) && status; ++i)
    {
        status = (GetVal(arr, i) == static_cast<int>(i));
    }
    
    std::cout << "Test setval:  ";
    status ? std::cout << "SUCCESS ✅" << '\n' : std::cout << "FAIL ❌" << '\n';

    SetAll(arr, 25);

    for (std::size_t i = 0; (i < SIZE) && status; ++i)
    {
        status = (GetVal(arr, i) == 25);
    }

    std::cout << "Test setall:  ";
    status ? std::cout << "SUCCESS ✅" << '\n' : std::cout << "FAIL ❌" << '\n';

    SetVal(arr, 3, 100);
    SetVal(arr, 7, -100);

    std::cout << "Test setval and getval after set all: " << '\n';
    (GetVal(arr, 3) == 100) ? 
    std::cout << "SUCCESS ✅" << '\n' : std::cout << "FAIL ❌" << '\n';
    (GetVal(arr, 7) == -100) ? 
    std::cout << "SUCCESS ✅" << '\n' : std::cout << "FAIL ❌" << '\n';
    (GetVal(arr, 0) == 25) ? 
    std::cout << "SUCCESS ✅" << '\n' : std::cout << "FAIL ❌" << '\n';

    SetAll(arr, -42);

    for (std::size_t i = 0; (i < SIZE) && status; ++i)
    {
        status = (GetVal(arr, i) == -42);
    }

    std::cout << "Test setall:  ";
    status ? std::cout << "SUCCESS ✅" << '\n' : std::cout << "FAIL ❌" << '\n';
    std::cout << "Test setval and getval after set all: " << '\n';
    (GetVal(arr, 3) == -42) ? 
    std::cout << "SUCCESS ✅" << '\n' : std::cout << "FAIL ❌" << '\n';

    DestroyArr(arr);
}

int_array_t *CreateArr(std::size_t size)
{
    int_array_t *newArr = reinterpret_cast<int_array_t *>
                (malloc(offsetof(int_array_t, arr) + sizeof(element_t) * size));
    if (0  == newArr)
    {
        return 0;
    }
    newArr->size = size;
    newArr->gen = 0;
    newArr->val = 0;

    return newArr;
}

void DestroyArr(int_array_t *arr)
{
    free(arr);
    arr = 0;
}

void SetVal(int_array_t *arr, int indx, int val)
{
    if (arr->size <= static_cast<std::size_t>(indx)) 
    {
        throw std::out_of_range("Index out of range");
    }

    arr->arr[indx] = std::make_pair(val, arr->gen);
}

int GetVal(int_array_t *arr, int indx)
{
    if (arr->size <= static_cast<std::size_t>(indx)) 
    {
        throw std::out_of_range("Index out of range");
    }
    
    const element_t& elem = arr->arr[indx];

    return ((elem.second == arr->gen) ? elem.first : (arr->val));
}

void SetAll(int_array_t *arr, int val)
{
    ++arr->gen;
    arr->val = val;
}

void TestFindSumOfTwo(void)
{
    unsigned int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::size_t size = sizeof(arr) / sizeof(arr[0]);
    
    std::cout << "Test find sum of two: ";
    FindSumOfTwo(arr, size, 13) ? 
    std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌, ";
    !FindSumOfTwo(arr, size, 2) ? 
    std::cout << "SUCCESS ✅" << '\n' : std::cout << "FAIL ❌" << '\n';

}

bool FindSumOfTwo(unsigned int *arr, std::size_t size,  unsigned int sum)
{
    std::set<unsigned int> set;

    for (std::size_t i = 0; i < size; ++i)
    {
        unsigned int diff = sum - arr[i];
        if (set.find(diff) != set.end())
        {
            return true;
        }
        else
        {
            set.insert(arr[i]);
        }
    }

    return false;
}

void TestFindChar(void)
{
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    std::size_t size = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Test find char: ";
    FindChar(arr, size, 'e') ?
    std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌, ";
    !FindChar(arr, size, 'z') ?
    std::cout << "SUCCESS ✅" << '\n' : std::cout << "FAIL ❌" << '\n';
}


bool FindChar(char *arr, std::size_t size, char c)
{
    char status = 1;

    for (std::size_t i = 0; i < size; ++i)
    {
        status *= arr[i] ^ c;
    }

    return !status;
}

void TestShiftNBytesInPlace(void)
{
    char arr[] = "ah yakar";
    std::size_t size = std::strlen(arr);

    std::cout << "Test shift n bytes in place: " << '\n';
    std::cout << "Before: " << arr << '\n';
    ShiftNBytesInPlace(arr, size, 3);
    std::cout << "After: " << arr << '\n';
    std::cout << "Before: " << arr << '\n';
    ShiftNBytesInPlace(arr, size, 10);
    std::cout << "After: " << arr << '\n';
    std::cout << "Before: " << arr << '\n';
    ShiftNBytesInPlace(arr, size, 3);
    std::cout << "After: " << arr << '\n';
}

void ShiftNBytesInPlace(char *arr, std::size_t size, std::size_t n)
{
    char *start = arr;
    char *end = arr + size - 1;
    n %= size;
    char *pivot = start + n - 1;

    ReverseChars(start, pivot);
    ReverseChars(pivot + 1, end);
    ReverseChars(start, end);
}

void ReverseChars(char *start, char *end)
{
    while (start < end)
    {
        char temp = *start;
        *start++ = *end;
        *end-- = temp;
    }
}

void TestCountIslands(void)
{
    bool map[][5]  = {{1,1,0,0,0},
                      {0,1,0,0,1},
                      {1,0,0,1,1},
                      {0,0,1,0,0},
                      {1,0,0,0,1},
                      {0,0,1,0,0}};
    
    std::vector<std::vector<bool> > mapv;
    for (std::size_t i = 0; i < sizeof(map) / sizeof(map[0]); ++i)
    {
        std::vector<bool> row(map[i], map[i] + 5);
        mapv.push_back(row);
    }
    
    std::cout << "Test count islands:   ";
    (5 == CountIslands(mapv)) ? 
    std::cout << "SUCCESS ✅\n" : std::cout << "FAIL ❌\n";
}

std::size_t CountIslands(std::vector<std::vector<bool> > map)
{
    std::size_t count = 0;
    std::size_t numRows = map.size();
    std::size_t numCols = map[0].size();

    for (std::size_t i = 0; i < numRows; ++i)
    {
        for (std::size_t j = 0; j < numCols; ++j)
        {
            if (1 == map[i][j])
            {
                ++count;
                MarkIsland(map, i, j, numRows, numCols);
            }
        }
    }

    return count;
}

void MarkIsland(std::vector<std::vector<bool> >& map, 
                std::size_t i, std::size_t j, 
                std::size_t Rows, std::size_t Cols)
{
    static int rowNbr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    static int colNbr[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    if ((i >= Rows) || (j >= Cols) || (0 == map[i][j]))
    {
        return;
    }

    const std::size_t numOfNbrs = 8;
    map[i][j] = 0;
    for (std::size_t k = 0; k < numOfNbrs; ++k)
    {
        MarkIsland(map, i + rowNbr[k], j + colNbr[k], Rows, Cols);
    }
}

void TestMinStack(void)
{
    MinStack<int> stack;
    stack.Push(10);
    stack.Push(2);
    stack.Push(3);
    stack.Push(2);
    stack.Push(1);
    stack.Push(4);
    stack.Push(5);

    std::cout << "Test min stack: ";
    (1 == stack.Min()) ? 
    std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌, ";
    (5 == stack.Top()) ?
    std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌, ";

    stack.Pop();
    stack.Pop();
    stack.Pop();
    (2 == stack.Min()) ? 
    std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌, ";

    stack.Pop();
    (2 == stack.Min()) ? 
    std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌, ";

    stack.Pop();
    stack.Pop();
    (10 == stack.Min()) ?
    std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌, ";
    std::cout << std::endl;
}

template<class type>
void MinStack<type>::Push(type val)
{
    if (m_min.empty() || m_min.top() >= val)
    {
        m_min.push(val);
    }
    m_data.push(val);
}

template<class type>
void MinStack<type>::Pop()
{
    if (m_data.top() == m_min.top())
    {
        m_min.pop();
    }
    m_data.pop();
}

template<class type>
type MinStack<type>::Top()
{
    return m_data.top();
}

template<class type>
type MinStack<type>::Min()
{
    return m_min.top();
}

void TestCheckParantheses(void)
{
    char str1[] = "(x + 3 * [4 + 6]) <>";
    char str2[] = "(8 ]* (6 + 2) + 1)";
    char str3[] = "[(8 ]* (6 + 2) + 1)";

    std::cout << "Test check parantheses: ";
    (true == CheckParantheses(str1)) ?
    std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌, ";
    (false == CheckParantheses(str2)) ?
    std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌, ";
    (false == CheckParantheses(str3)) ?
    std::cout << "SUCCESS ✅\n" : std::cout << "FAIL ❌\n";
}

bool CheckParantheses(char *str)
{
    std::stack<char> stack;

    while ('\0' != *str)
    {
        if ('(' == *str || '{' == *str || '[' == *str || '<' == *str)
        {
            stack.push(*str);
        }
        else if (false == CheckStack(str, stack))
        {
            return false;
        }
        ++str;
    }

    return stack.empty();
}

bool CheckStack(char *str, std::stack<char>& stack)
{
    bool status = true;

    switch (*str)
    {
        case ')': 
            if (stack.empty() || stack.top() != '(')
            {
                return false;
            }
            stack.pop();
            break;
        case '}': 
            if (stack.empty() || stack.top() != '{')
            {
                return false;
            }
            stack.pop();
            break;
        case ']':
            if (stack.empty() || stack.top() != '[')
            {
                return false;
            }
            stack.pop();
            break;
        case '>':
            if (stack.empty() || stack.top() != '<')
            {
                return false;
            }
            stack.pop();
            break;
        default:
            break;
    }
    
    return status;
}

void TestRecMulty(void)
{
    std::cout << "Test rec multy: ";
    (15 == RecMulty(3, 5)) ?
    std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌, ";
    (0 == RecMulty(0, 5)) ?
    std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌, ";
    (-15 == RecMulty(-3, 5)) ?
    std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌, ";
    (-15 == RecMulty(3, -5)) ?
    std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌, ";
    (15 == RecMulty(-3, -5)) ?
    std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌, ";
    std::cout << std::endl;
}

int RecMulty(int a, int b)
{
    if (0 == b)
    {
        return 0;
    }
    if (b > a)
    {
        return RecMulty(b, a);
    }
    if (b < 0)
    {
        return (-a + RecMulty(a, b + 1));
    }
    return (a + RecMulty(a, b - 1));
}

void TestRecInc(void)
{
    int num1 = 0;
    int num2 = 11;
    int num3 = -11;
    int num4 = 32;
    int num5 = 12;

    std::cout << "Test rec inc: ";
    (1 == RecInc(num1)) ?
    std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌, ";
    (12 == RecInc(num2)) ?
    std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌, ";
    (-10 == RecInc(num3)) ?
    std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌, ";
    (33 == RecInc(num4)) ?
    std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌, ";
    (13 == RecInc(num5)) ?
    std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌, ";
    std::cout << std::endl;
}

int RecInc(int num)
{
    if (0 == (1 & num))
    {
        return (num | 1);
    }

    return (RecInc(num >> 1) << 1);
}

void TestPivotSort(void)
{
    std::list<int> list;
    list.push_front(5);
    list.push_front(3);
    list.push_front(10);
    list.push_front(20);
    list.push_front(-2);

    std::cout << "Test pivot sort: \n";
    std::cout << "Before: ";
    for (std::list<int>::iterator iter = list.begin(); iter != list.end(); 
        ++iter)
    {
        std::cout << *iter << " ";
    }
    std::cout << "\n";
    PivotSort(list, 6);
    std::cout << "After: ";
    for (std::list<int>::iterator iter = list.begin(); iter != list.end(); 
        ++iter)
    {
        std::cout << *iter << " ";
    }
    std::cout << "\n";

}

void PivotSort(std::list<int>& list, int pivot)
{
    std::list<int>::iterator iter = list.begin();
    for (std::size_t i = 0; i < list.size(); ++i)
    {
        if (*iter >= pivot)
        {
            list.push_back(*iter);
            std::list<int>::iterator temp = iter;
            ++iter;
            list.erase(temp);
        }
        else
        {
            ++iter;
        }
    }
}

int IterInsert(tree_node *root, int data)
{
    tree_node *newNode = new tree_node(data);
    
    while (NULL != root)
    {
        int dir = (root->data > data) ? LEFT : RIGHT;
        if (NULL == root->child[dir])
        {
            root->child[dir] = newNode;
            return 0;
        }
        root = root->child[dir];
    }

    return -1;
}

tree_node *RecInsert(tree_node *root, int data)
{
    if (NULL == root)
    {
        return (new tree_node(data));
    }

    int dir = (root->data > data) ? LEFT : RIGHT;
    root->child[dir] = RecInsert(root->child[dir], data);

    return root;
}