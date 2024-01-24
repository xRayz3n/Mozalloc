#include <unistd.h>

#define MIN_BLOCK_LENGTH 1024

struct block_header
{
    int length;
    enum flag { occupied = 1, free = 0 };
    struct block_header *previous ;
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

void cut_block(struct block_header target, int size)
{

}

int main()
{

}