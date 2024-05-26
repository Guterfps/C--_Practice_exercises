
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>

bool WordPattern(std::string& pattern, std::string& s);

int main() {
    std::string pattern1 = "abba";
    std::string test1 = "dog cat cat dog";
    std::string pattern2 = "abcb";
    std::string test2 = "dog cat dog cat";
    std::string pattern3 = "abcb";
    std::string test3 = "dog cat hat cat";
    std::string pattern4 = "aaa";
    std::string test4 = "aa aa aa aa";
    std::string pattern5 = "aaaaa";
    std::string test5 = "aa aa aa aa";

    std::cout << (WordPattern(pattern1, test1) ? "true" : "false") << '\n';
    std::cout << (WordPattern(pattern2, test2) ? "true" : "false") << '\n';
    std::cout << (WordPattern(pattern3, test3) ? "true" : "false") << '\n';
    std::cout << (WordPattern(pattern4, test4) ? "true" : "false") << '\n';
    std::cout << (WordPattern(pattern5, test5) ? "true" : "false") << '\n';

}

bool WordPattern(std::string& pattern, std::string& s) {
    if ((std::count(s.begin(), s.end(), ' ') + 1) != 
        static_cast<std::ptrdiff_t>(pattern.size())) {
            return false;
    }

    std::unordered_map<char, std::string> map;
    std::unordered_set<std::string> words;
    size_t s_indx = 0;

    for (char c : pattern) {
        size_t e_indx = s.find(" ", s_indx);
        std::string word = s.substr(s_indx, e_indx - s_indx);
        s_indx = e_indx + 1;

        if (map.find(c) == map.end()) {
            if (words.find(word) != words.end()) {
                return false;
            }
            map[c] = word;
            words.insert(word);
        }
        else if (map.at(c) != word) {
            return false;
        }
    }

    return true;
}