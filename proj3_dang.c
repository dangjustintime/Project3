#include <stdio.h>
#include <stdlib.h>

struct Mem_Ref {
  int address;
  int tag;
  int index;
  int offset;
  int result;
  char rw;
};

struct Cache {
  int num_ref;
  int hits;
  int misses;
  int num_mem_ref;
};

int main() {
  struct Cache write_through_no_write;
  struct Cache write_back_write;
  struct Mem_Ref mem_ref[100];
  char line[30];
  int block_size;
  int num_sets;
  int set_associativity;
  int num_ref = 0;
  int i = 0;

  // read input
  scanf("%i\n", &block_size);
  scanf("%i\n", &num_sets);
  scanf("%i\n", &set_associativity);
  while (scanf("%c %i\n", &mem_ref[num_ref].rw,
        &mem_ref[num_ref].address) != EOF) {
    num_ref++; 
  }

  // print
  printf("%i\n", block_size);
  printf("%i\n", num_sets);
  printf("%i\n", set_associativity);

  while (i < num_ref) {
    printf("%c %i\n", mem_ref[i].rw, mem_ref[i].address);
    i++;
  }
  

  return 0;
}
