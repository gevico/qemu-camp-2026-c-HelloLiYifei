#include <stdio.h>


int countWord(char* str) {
    int count = 0;
    int i = 0;
    while (str[i++] != '\0') {
        if (str[i] == ' ' || str[i] == '.') {count ++;}
    }
    return count;
}

int main() {
    char str[]="Don't ask what your country can do for you, but ask what you can do for your country.";
    int wordCount = 0;
    // TODO: 在这里添加你的代码

    wordCount =countWord(str);
    printf("单词数量: %d\n", wordCount);
    
    return 0;
}