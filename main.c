#include <unistd.h>
#include <stdio.h>
#define MIN_BLOCK_LENGTH 1024
#define HEADER_LENGTH sizeof(block_header)

typedef struct block_header
{
    size_t length;
    enum flag { OCCUPIED = 1, FREE = 0 } flag;
    struct block_header* next ;
} block_header;

void* mozalloc(size_t size)
{

}

void mozafree(void* target)
{

}

block_header* create_block(size_t size) // function I need to write
{
    block_header* extension;
    if (size < MIN_BLOCK_LENGTH) size = MIN_BLOCK_LENGTH;

    extension = sbrk(size + HEADER_LENGTH);
    if (extension == (void *) -1) return NULL;

    extension->length = size;
    extension->flag = FREE;
    extension->next = extension;

    return extension;

}

int insert_block()
{

}

void cut_block(block_header target, int size)
{

}

int main()
{
block_header* block = create_block(2048);  // Allocate a block of size 2048 bytes

    if (block != NULL) {
        printf("Block created successfully:\n");
        printf("Length: %zu\n", block->length);
        printf("Flag: %s\n", (block->flag == FREE) ? "FREE" : "OCCUPIED");
        printf("Next: %p\n", (void*)block->next);
    } else {
        printf("Failed to create block\n");
    }

    return 0;
}