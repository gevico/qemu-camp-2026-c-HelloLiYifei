#include <stdio.h>

int main() {
    char source[] = "Hello, World! This is a test string for my_strcpy function.\n";
    char destination[101];
    
	// TODO: 在这里添加你的代码
    for (int i = 0; i < 101; i++) {
        destination[i] = source[i];
    }
    printf("拷贝后的字符串: %s", destination);
    
    return 0;
}