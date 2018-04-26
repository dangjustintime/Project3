#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct Mem_Ref {
  int address;
  int tag;
  int index;
  int offset;
  int result;
  int mem_ref;
  int update_cache;
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
  int i;
  int j;

  // read input
  scanf("%i\n", &block_size);
  scanf("%i\n", &num_sets);
  scanf("%i\n", &set_associativity);
  
  // parse input
  while (scanf("%c %i\n", &mem_ref[num_ref].rw,
      &mem_ref[num_ref].address) != EOF) {
    num_ref++;
  }
 
  // get number of bits
  num_offset_bits = log2(block_size);
  num_index_bits = log2(num_sets);
  num_tag_bits = 32 - (num_offset_bits + num_index_bits);
  
  // get tag, index, and offset
  for(i = 0; i < num_ref; i++) {
    mem_ref[i].tag = (mem_ref[i].address >> (32 - num_tag_bits))
        & (int) pow(2, num_tag_bits);
    mem_ref[i].index = (mem_ref[i].address >> num_offset_bits)
        & ((int) pow(2, num_index_bits) - 1);
    mem_ref[i].offset = mem_ref[i].address
        & ((int) pow(2, num_offset_bits) - 1);
  }
  
  write_through_no_allocate.num_ref = num_ref;
  write_back_allocate.num_ref = num_ref;

  // dynamically allocate Mem_Ref array
  write_through_no_allocate.mem_ref = (struct Mem_Ref *) malloc
      (num_ref * sizeof(struct Mem_Ref));
  write_back_allocate.mem_ref = (struct Mem_Ref *) malloc
      (num_ref * sizeof(struct Mem_Ref));
 
  // initialize hits
  write_through_no_allocate.hits = 0;
  write_back_allocate.hits = 0;
  write_through_no_allocate.num_mem_ref = 0;
  write_back_allocate.num_mem_ref = 0;
  
  for(i = 0; i < num_ref; i++) {
    mem_ref[i] = write_through_no_allocate.mem_ref[i];
    mem_ref[i] = write_back_allocate.mem_ref[i];
    write_through_no_allocate.mem_ref[i].mem_ref = 1;
    write_back_allocate.mem_ref[i].mem_ref = 1;
    write_back_allocate.num_mem_ref++;
    write_through_no_allocate.num_mem_ref++;
    write_back_allocate.mem_ref[i].update_cache = 1;
    
    // find hits and misses
    for (j = 0; j < i; j++) {
      if (mem_ref[j].address + mem_ref[j].offset == mem_ref[i].address) {
        write_through_no_allocate.mem_ref[i].result = 1;
        write_back_allocate.mem_ref[i].result = 1;
        write_through_no_allocate.hits++;
        write_back_allocate.hits++;
      } else {
        write_through_no_allocate.mem_ref[i].result = 0;
        write_back_allocate.mem_ref[i].result = 0;
      }
    }
    
    // simulate write-through with no write allocate
    if (mem_ref[i].rw == 'W' &&
        write_through_no_allocate.mem_ref[i].result == 0) {
      write_through_no_allocate.mem_ref[i].update_cache = 0;
    } else {
      write_through_no_allocate.mem_ref[i].update_cache = 1;
    }
    
    // simulate write-back with write allocate
    if (write_back_allocate.mem_ref[i].result == 1) {
      write_back_allocate.mem_ref[i].mem_ref = 0;
      write_back_allocate.num_mem_ref--;
      if (write_back_allocate.mem_ref[i].rw == 'R') {
        write_back_allocate.mem_ref[i].update_cache = 0;
      }
    }
  
  }

  // misses
  write_through_no_allocate.misses = write_through_no_allocate.num_ref - write_through_no_allocate.hits;
  write_back_allocate.misses = write_back_allocate.num_ref - write_back_allocate.hits;
  
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
