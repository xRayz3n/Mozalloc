#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#define MIN_BLOCK_LENGTH 1024
#define HEADER_LENGTH sizeof(block_header)



typedef struct block_header
{
    size_t length;
    enum flag { OCCUPIED = 1, FREE = 0 } flag;
    struct block_header* next ;
} block_header;

static block_header* ENTRY_POINTER = NULL;

void* mozalloc(size_t size)
{
}

void mozafree(void* target)
{

}

void insert_block(block_header* target)
{
    block_header* current;
    while (1) { // get the last block
            current = current->next;
        if (current->next == NULL) break;
    }
    current->next = target;
}


block_header* create_block(size_t size)
{
    block_header* extension;
    if (size < MIN_BLOCK_LENGTH) size = MIN_BLOCK_LENGTH;

    extension = sbrk(size + HEADER_LENGTH);
    if (extension == (void *) -1) return NULL;

    extension->length = size;
    extension->flag = FREE;
    extension->next = NULL;

    if (ENTRY_POINTER == NULL) {
        ENTRY_POINTER = extension;
    } else insert_block(extension);

    return extension;

}


block_header* cut_block(block_header *target, int size)
{
    if (target->flag == FREE && target->length > size + HEADER_LENGTH)
    {
        block_header *new_block = target + HEADER_LENGTH +size;
        new_block->next = target->next;
        new_block->flag = FREE;
        new_block->length = target->length - size - HEADER_LENGTH;

        target->length = size;
        target->next = new_block;

        return new_block;
    }
    return NULL;
}

void print_all_block()
{

}

int main()
{
    block_header* block1 = create_block(2048);
    block_header* block2 = create_block(4096);


    if (block1 != NULL) {
        printf("Block created successfully:\n");
        printf("Length: %zu\n", block1->length);
        printf("Flag: %s\n", (block1->flag == FREE) ? "FREE" : "OCCUPIED");
        printf("Next: %p\n", (void*)block1->next);
    } else {
        printf("Failed to create block\n");
    }

    return 0;
}