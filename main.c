#include <unistd.h>
#include <stdio.h>

#define MIN_BLOCK_LENGTH 1024

typedef struct block_header
{
    int length;
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

void cut_block(block_header target, int size)
{

}

int main()
{
    printf("%i\n", (int)sizeof(block_header));
}