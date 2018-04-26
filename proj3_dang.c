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
  struct Mem_Ref * mem_ref;
};

int main() {
  struct Cache write_through_no_allocate;
  struct Cache write_back_allocate;
  struct Mem_Ref mem_ref[100];
  int block_size;
  int num_index_bits;
  int num_offset_bits;
  int num_sets;
  int num_tag_bits;
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

  write_through_no_allocate.num_ref = num_ref;
  write_back_allocate.num_ref = num_ref;

  // dynamically allocate Mem_Ref array
  write_through_no_allocate.mem_ref = (struct Mem_Ref *) malloc
      (num_ref * sizeof(struct Mem_Ref));
  write_back_allocate.mem_ref = (struct Mem_Ref *) malloc
      (num_ref * sizeof(struct Mem_Ref));

  // print
  printf("Block size: %i\n", block_size);
  printf("Number of sets: %i\n", num_sets);
  printf("Associativity: %i\n", set_associativity);
  printf("Number of offset bits: %i\n", num_offset_bits);
  printf("Number of index bits: %i\n", num_index_bits);
  printf("Number of tag bits: %i\n", num_tag_bits);
  printf("****************************************\n");
  printf("Write-through with No Write Allocate\n");
  printf("****************************************\n");
  printf("Total number of references: %i\n", write_through_no_allocate.num_ref);
  printf("Hits: %i\n", write_through_no_allocate.hits);
  printf("Misses: %i\n", write_through_no_allocate.misses);
  printf("Memory References: %i\n", write_through_no_allocate.num_mem_ref);
  printf("****************************************\n");
  printf("Write-back with Write Allocate\n");
  printf("****************************************\n");
  printf("Total number of references: %i\n", write_back_allocate.num_ref);
  printf("Hits: %i\n", write_back_allocate.hits);
  printf("Misses: %i\n", write_back_allocate.misses);
  printf("Memory References: %i\n", write_back_allocate.num_mem_ref);

  // deallocate array
  free(write_through_no_allocate.mem_ref);
  free(write_back_allocate.mem_ref);
  
  return 0;
}
