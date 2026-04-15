#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    if (cmd[0] != 's' || cmd[1] != '/') {
        return -1;
    }

    int i = 2;
    int old_start = 2;
    while (cmd[i] != '\0' && cmd[i] != '/') {
        i++;
    }
    if (cmd[i] != '/') {
        return -1;
    }
    int old_len = i - old_start;
    
    i++;
    int new_start = i;
    while (cmd[i] != '\0' && cmd[i] != '/') {
        i++;
    }
    if (cmd[i] != '/') {
        return -1;
    }
    int new_len = i - new_start;
    
    *old_str = (char*)malloc(old_len + 1);
    *new_str = (char*)malloc(new_len + 1);
    
    if (*old_str == NULL || *new_str == NULL) {
        free(*old_str);
        free(*new_str);
        return -1;
    }
    
    strncpy(*old_str, cmd + old_start, old_len);
    (*old_str)[old_len] = '\0';
    
    strncpy(*new_str, cmd + new_start, new_len);
    (*new_str)[new_len] = '\0';
    
    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new) {
    char* pos = strstr(str, old);

    
    int old_len = strlen(old);
    int new_len = strlen(new);
    int str_len = strlen(str);
    
    if (new_len > old_len) {
        int offset = new_len - old_len;
        for (int i = str_len; i >= (pos - str) + old_len; i--) {
            str[i + offset] = str[i];
        }
    } else if (new_len < old_len) {
        int offset = old_len - new_len;
        for (int i = (pos - str) + new_len; i <= str_len; i++) {
            str[i] = str[i + offset];
        }
    }
    
    strncpy(pos, new, new_len);
}

int main(int argc, char* argv[]) {
    const char* replcae_rules = "s/unix/linux/";

    char line[MAX_LINE_LENGTH] = {"unix is opensource. unix is free os."};

    char* old_str = NULL;
    char* new_str = NULL;
    
    if (parse_replace_command(replcae_rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    
    replace_first_occurrence(line, old_str, new_str);
    fputs(line, stdout);

    free(old_str);
    free(new_str);
    return 0;
}
