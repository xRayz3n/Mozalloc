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
            printf("______________Block n°%i____________\n", counter);
            printf("Flag : %s\n", (current->flag == FREE) ? "FREE" : "OCCUPIED");
            printf("Length : %zu\n", current->length);
            printf("Place in memory : %p\n", current);
            printf("Place of next : %p\n", current->next);            
            printf("__________________________________\n");
            if(current->next == NULL){break;}
            current = current->next;
            counter++;
        }
    }
    else 
    {
        printf("No block to show\n");
    }

}

int main()
{
    block_header* block1 = create_block(2048);
    block_header* block2 = create_block(4096);
    
    print_all_block();

    return 0;
}