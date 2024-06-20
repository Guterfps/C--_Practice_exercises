
#include <iostream>
#include <string>
#include <algorithm>

void ReverseAndRemoveSpacesV1(char *str);
void ReverseAndRemoveSpacesV2(std::string& str);

void ReverseStr(char *str);
void Swap(char *a, char *b);
void RemoveSpaces(char *str);


int main(void) {
    char str[] = " ah  yakar ";

    std::cout << "before: ";
    std::cout << str << '\n';

    ReverseAndRemoveSpacesV1(str);

    std::cout << "after: ";
    std::cout << str << '\n';

    std::string str2 = "   ma  ha    matzav ?   ";

    std::cout << "before: ";
    std::cout << str2 << '\n';

    ReverseAndRemoveSpacesV2(str2);

    std::cout << "after: ";
    std::cout << str2 << '\n';


    return 0;
}

void ReverseAndRemoveSpacesV1(char *str) {
    ReverseStr(str);
    RemoveSpaces(str);
}

void ReverseStr(char *str) {
    size_t len = std::strlen(str);
    char *start = str;
    char *end = start + len - 1;

    while (start < end) {
        Swap(start++, end--);
    }
}

void Swap(char *a, char *b) {
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

void RemoveSpaces(char *str) {
    if (str == nullptr) {
        return;
    }
    
    size_t count = 0;

    for (size_t i = 0; str[i] != '\0'; ++i) {
        if (str[i] != ' ') {
            str[count++] = str[i];
        }
    }

    str[count] = '\0';
}

void ReverseAndRemoveSpacesV2(std::string& str) {
    std::reverse(str.begin(), str.end());
    auto end = std::remove(str.begin(), str.end(), ' ');
    str.resize(end - str.begin());
}