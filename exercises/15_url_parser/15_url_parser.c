#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * URL参数解析器
 * 输入：包含http/https超链接的字符串
 * 输出：解析出所有的key-value键值对，每行显示一个
 */

int parse_url(const char* url) {
    int err = 0;

    // TODO: 在这里添加你的代码
    int len = strlen(url);
    char key[50], value[50];
    int isvalue, iskey, j;
    isvalue = iskey = j = 0;
    for (int i = 0; i <= len; i ++) {
        if (url[i] == '?') {
            isvalue = 1;
            continue;
        }
        if (url[i] == '&' || url[i] == '\0') {
            iskey = 0;
            isvalue = 1;
            value[j] = '\0';
            j = 0;
            printf("value = %s\n", value);
            continue;
        }
        if (url[i] == '=') {
            isvalue = 0;
            iskey   = 1;
            key[j]  = '\0';
            j       = 0;
            printf("key = %s, ", key);
            continue;
        }
        if (isvalue) {
            key[j++] = url[i];
        }
        if (iskey) {
            value[j++] = url[i];
        }

    }
exit:
    return err;
}

int main() {
    const char* test_url = "https://cn.bing.com/search?name=John&age=30&city=New+York";

    printf("Parsing URL: %s\n", test_url);
    printf("Parameters:\n");

    parse_url(test_url);

    return 0;
}