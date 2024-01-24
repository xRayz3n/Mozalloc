#include <unistd.h>
#include <stdio.h>

#define MIN_BLOCK_LENGTH 1024
#define HEADER_LENGTH sizeof(block_header)

typedef struct block_header
{
    size_t length;
    enum { occupied = 1, free = 0 } flag;
    struct block_header *next ;
} block_header;

void* mozalloc(int size)
{

}

void mozafree(void* target)
{

}

int create_block()
{

}

int insert_block()
{

}

block_header* cut_block(block_header *target, int size)
{
    if (target->flag == free && target->length > size + HEADER_LENGTH)
    {
        block_header *new_block = target + HEADER_LENGTH +size;
        new_block->next = target->next;
        new_block->flag = free;
        new_block->length = target->length - size - HEADER_LENGTH;

        target->length = size;
        target->next = new_block;

        return new_block;
    }
    return NULL;
}

int main()
{
    printf("%i\n", (int)sizeof(block_header));
}