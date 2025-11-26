#include <assert.h>
#include <stddef.h>
#include <unistd.h>
#include <stdbool.h>
#define BLOCK_SIZE sizeof(BlockMeta)

struct BlockMeta{
	struct BlockMeta *next;
	size_t size;
	bool free;
};

typedef struct BlockMeta BlockMeta;

BlockMeta* global_block = NULL;

BlockMeta* request_space(BlockMeta* last, size_t size){
	BlockMeta* block = sbrk(0);
	void* request = sbrk(size + BLOCK_SIZE);
	if(request != block){
		return NULL;
	}
	if(last){
		last->next = block;
	}
	block->next = NULL;
	block->size = size;
	block->free = false;
	return block;
}

BlockMeta* find_free_block(BlockMeta **last, size_t size){
	BlockMeta* current = *last;
	while(current && !(current->free && current->size >= size)){
		*last = current;
		current = current->next;
	}
	return current;
}

void* malloc(size_t size){
	BlockMeta* block = NULL;
	if(size <= 0) return NULL;
	if(!global_block){
		block = request_space(NULL, size);
		if(!block) return NULL;
		global_block = block;
	}else{
		block = find_free_block(&global_block, size);
		if(block == NULL){
			block = request_space(global_block, size);
			if(block == NULL) return NULL;
		}else{
			block->free = 0;
		}
	}
	return (block + 1);
}
void free(void* ptr){
	if(!ptr) return;
	BlockMeta* block = (BlockMeta*) ptr - 1;
	assert(block->free == false);
	block->free = 1;
}
