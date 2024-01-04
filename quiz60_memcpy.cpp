
#include <iostream>
#include <cstring>

using std::cout;
using std::endl;

void *MemCpy(void *dest, const void *src, size_t size);

int main()
{
    char a[] = "ah yakar";
    char b[10] = "ahi";
    
    cout << "before copy: " << b << endl;
    MemCpy(b, a, strlen(a));
    cout << "after copy: " << b << endl;
    (0 == strcmp(a, b)) ? cout << "SUCCESS ✅️\n" : cout << "FAIL ❌️\n";
    
    return 0;
}

void *MemCpy(void *dest, const void *src, size_t size)
{
    unsigned char *d = reinterpret_cast<unsigned char *>(dest);
    const unsigned char *s = reinterpret_cast<const unsigned char *>(src);
    
    while (size--)
    {
        *d++ = *s++;
    }
    
    return dest;
}

