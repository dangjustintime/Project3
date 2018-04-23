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
  int i = 0;

  // read input
  scanf("%i", &block_size);
  scanf("%i", &num_sets);
  scanf("%i", &set_associativity);
  while (scanf("%c %i", &mem_ref[i].rw, &mem_ref[i].address)) {
    i++; 
  }


  return 0;
}
