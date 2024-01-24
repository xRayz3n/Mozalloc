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

static block_header* ENTRY_POINTER = NULL;

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

    if (ENTRY_POINTER == NULL) ENTRY_POINTER = extension;

    return extension;

}

int insert_block()
{

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

block_header* search_free_block(int size)
{
    if (ENTRY_POINTER == NULL) return NULL;

    block_header* current = ENTRY_POINTER;
    while(1)
    {
        if(current->flag == FREE && current->length >= size) return current;

        if(current->next != NULL) {current = current->next;}
        else { return NULL; }
    }
}

void print_all_block()
{
    if (ENTRY_POINTER != NULL) 
    {
        block_header* current = ENTRY_POINTER;
        int counter = 0;
        while(1)
        {
            printf("_____Block n°%i_____ :\n", counter);
            printf("Flag : %i\n", (int) current->flag);
            printf("Length : %zu\n", current->length);
            printf("Place in memory : %p\n", current);
            printf("Place of next : %p\n", current->next);            
            if(current->next == NULL){break;}
            current = current->next;
            counter++;
        }
    }

}

int main()
{
block_header* block = create_block(2048);  // Allocate a block of size 2048 bytes

    if (block != NULL) {
        printf("Block created successfully:\n");
        printf("Length: %zu\n", block->length);
        printf("Flag: %s\n", (block->flag == FREE) ? "FREE" : "OCCUPIED");
        printf("Next: %p\n", (void*)block->next);
        print_all_block();
    } else {
        printf("Failed to create block\n");
    }

    return 0;
}