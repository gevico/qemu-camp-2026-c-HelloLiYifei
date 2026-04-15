#include "mywc.h"

// 创建哈希表
WordCount **create_hash_table() {
  WordCount **hash_table = calloc(HASH_SIZE, sizeof(WordCount *));
  return hash_table;
}

// 简单的哈希函数
unsigned int hash(const char *word) {
  unsigned long hash = 5381;
  int c;
  while ((c = *word++))
    hash = ((hash << 5) + hash) + c; // hash * 33 + c
  return hash % HASH_SIZE;
}

// 检查字符是否构成单词的一部分
bool is_valid_word_char(char c) { return isalpha(c) || c == '\''; }

// 转换为小写
char to_lower(char c) { return tolower(c); }

// 添加单词到哈希表
void add_word(WordCount **hash_table, const char *word) {
    // TODO: 在这里添加你的代码
    int h = hash(word);
    if (hash_table[h] == NULL) {
        hash_table[h] = malloc(sizeof(WordCount));
        strncpy(hash_table[h]->word, word, MAX_WORD_LEN - 1);
        hash_table[h]->word[MAX_WORD_LEN - 1] = '\0';  // 确保字符串以null结尾
        hash_table[h]->count = 1;
        hash_table[h]->next = NULL;  // 初始化next指针
    } else if (strcmp(hash_table[h]->word, word) == 0) {
        hash_table[h]->count++;
    } else {
        WordCount *current = hash_table[h];
        WordCount *prev = NULL;

        while (current != NULL && strcmp(current->word, word) != 0) {
            prev = current;
            current = current->next;
        }
        
        if (current != NULL && strcmp(current->word, word) == 0) {
            current->count++;
        } else {
            WordCount *new_node = malloc(sizeof(WordCount));
            strncpy(new_node->word, word, MAX_WORD_LEN - 1);
            new_node->word[MAX_WORD_LEN - 1] = '\0';
            new_node->count = 1;
            new_node->next = hash_table[h];
            hash_table[h] = new_node;
        }
    }
}

// 打印单词统计结果
void print_word_counts(WordCount **hash_table) {
  printf("Word Count Statistics:\n");
  printf("======================\n");

    // TODO: 在这里添加你的代码
    for (int i = 0; i < HASH_SIZE; i++) {
        WordCount *current = hash_table[i];
        while (current != NULL) {
            printf("%-20s %d\n", current->word, current->count); 
            current = current->next;
        }
    }
}

// 释放哈希表内存
void free_hash_table(WordCount **hash_table) {
    // TODO: 在这里添加你的代码
    for (int i = 0; i < HASH_SIZE; i++) {
        WordCount *current = hash_table[i];
        while (current != NULL) {
            WordCount *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hash_table);
}

// 处理文件并统计单词
void process_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  WordCount **hash_table = create_hash_table();
  char word[MAX_WORD_LEN];
  int word_pos = 0;
  int c;

  while ((c = fgetc(file)) != EOF) {
    if (is_valid_word_char(c)) {
      if (word_pos < MAX_WORD_LEN - 1) {
        word[word_pos++] = to_lower(c);
      }
    } else {
      if (word_pos > 0) {
        word[word_pos] = '\0';
        add_word(hash_table, word);
        word_pos = 0;
      }
    }
  }

  if (word_pos > 0) {
    word[word_pos] = '\0';
    add_word(hash_table, word);
  }

  fclose(file);
  print_word_counts(hash_table);
  free_hash_table(hash_table);
}
