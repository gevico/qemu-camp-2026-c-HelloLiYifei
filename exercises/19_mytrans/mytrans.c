// mytrans.c
#include "myhash.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim(char *str) {
    if (!str || *str == '\0') return;
    
    // 去除前导空白
    char *start = str;
    while (*start && isspace((unsigned char)*start)) {
        start++;
    }
    
    // 去除尾部空白
    char *end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }
    
    // 移动字符串并添加终止符
    size_t len = end - start + 1;
    memmove(str, start, len);
    str[len] = '\0';
}

int load_dictionary(const char *filename, HashTable *table,
                    uint64_t *dict_count) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("无法打开词典文件");
    return -1;
  }

  char line[1024];
  char current_word[100] = {0};
  char current_translation[1024] = {0};
  int in_entry = 0;

  while (fgets(line, sizeof(line), file)) {
    // 去除换行符
    line[strcspn(line, "\n")] = '\0';
    trim(line);
    
    // 如果是空行，跳过
    if (strlen(line) == 0) {
      continue;
    }
    
    // 如果以 # 开头，表示新单词
    if (line[0] == '#') {
      // 如果之前有单词，先保存
      if (in_entry && strlen(current_word) > 0 && strlen(current_translation) > 0) {
        hash_table_insert(table, current_word, current_translation);
        (*dict_count)++;
      }
      
      // 开始新单词
      strncpy(current_word, line + 1, sizeof(current_word) - 1);
      current_word[sizeof(current_word) - 1] = '\0';
      current_translation[0] = '\0';
      in_entry = 1;
    }
    // 如果以 Trans: 开头，表示翻译
    else if (strncmp(line, "Trans:", 6) == 0) {
      strncpy(current_translation, line + 6, sizeof(current_translation) - 1);
      current_translation[sizeof(current_translation) - 1] = '\0';
    }
  }
  
  // 保存最后一个单词
  if (in_entry && strlen(current_word) > 0 && strlen(current_translation) > 0) {
    hash_table_insert(table, current_word, current_translation);
    (*dict_count)++;
  }

  fclose(file);
  return 0;
}
