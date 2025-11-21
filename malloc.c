#include <stddef.h>
#include <unistd.h>
#include <stdbool.h>

struct Block{
	struct Block *next_block;
	size_t size;
	bool free;
};

typedef struct Block Block;

Block* global_block = NULL;

void* initiate_block(){
	void* base = sbrk(0);
	void* r = sbrk(sizeof(Block));
	if(base != r || r == (void*) - 1){
		return (void*) - 1;
	}
	return r;
}

void* mallocd(int size){
	void* base = sbrk(0);
	void* new_base = sbrk(size);
	if(global_block == NULL){
		void* r =initiate_block();	
		if(r == (void*) - 1){
			return (void*) - 1;
		}
		global_block = (Block*) r;
	}
	void * r = initiate_block();
	if(r == (void*) - 1) return (void*) - 1;
	global_block->next_block = (Block*) r;
	global_block->size = size;
	global_block->free = 0;
	global_block = global_block->next_block;
	return global_block;
}
void* realloc(void* ptr, size_t size){

}
