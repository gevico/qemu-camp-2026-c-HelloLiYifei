#include "mywc.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  const char* filepath = "./text.txt";

  WordCount *hash_table = calloc(HASH_SIZE, sizeof(WordCount));
  process_file(filepath);
  print_word_counts(hash_table);
  free_hash_table(hash_table);
  return 0;
}
