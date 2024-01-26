# Custom Memory Allocation Library
Project made by Sébastien LAM, Théo LISSARRAGUE, Maëlle ROCHE, Paul RAGUET

## Overview

This C library provides custom memory allocation functions, similar to `malloc` and `free`, for dynamic memory management in C programs. It uses a linked list of block headers to keep track of memory blocks.

## Key Components

- **Block Header Structure (`block_header`):** This structure represents each block of memory. It includes the block size, a flag indicating if the block is occupied or free, and a pointer to the next block.

- **Global Variables:**
  - `ENTRY_POINTER`: A static pointer to the first block header in the memory allocation list.

- **Functions:**
  1. `data_to_header(void* ptr)`: Converts a data pointer to its corresponding block header.
  2. `header_to_data(block_header* target)`: Converts a block header pointer to its corresponding data pointer.
  3. `insert_block(block_header* target)`: Inserts a block into the linked list.
  4. `create_block(size_t size)`: Creates a new memory block using `sbrk(2)`.
  5. `cut_block(block_header* target, size_t size)`: Splits a block into two if it's large enough.
  6. `search_free_block(size_t size)`: Searches for a free block of sufficient size.    
  7. `print_all_block()`: Prints details of all blocks for debugging.
  8. `mozalloc(size_t size)`: Custom allocation function.
  9. `mozafree(void* ptr)`: Custom deallocation function.

## Usage

- **mozalloc(size_t size):**
  Allocates a block of memory of at least `size` bytes and returns a pointer to it. The function first searches for a free block that can accommodate the requested size. If no suitable block is found, a new block is created.

- **mozafree(void* ptr):**
  Frees the block of memory pointed to by `ptr`. The corresponding block is marked as free and can be reused in future allocations.

## Implementation Details

- The library maintains a singly linked list of memory blocks.
- Each block has a header that stores its metadata.
- The `ENTRY_POINTER` points to the first block in the list.
- When allocating memory, the library searches for a sufficiently large free block or creates a new one if necessary.
- When freeing memory, the corresponding block is simply marked as free.

## Notes

- The implementation includes a `print_all_block()` function for debugging, which prints the status of all blocks in the list.
- The minimum block length and header length are defined as constants (`MIN_BLOCK_LENGTH` and `HEADER_LENGTH`).
- Error checking, particularly in `create_block()`, ensures that memory allocation is successful.

## Example

```c
int main() {
    // Allocate memory
    void* my_block = mozalloc(100);

    // Use the memory...

    // Free memory
    mozafree(my_block);

    return 0;
}
```

 ## How to implement with LD_PRELOAD
 You first need to create `mozalloc.so` file from the `main.c` using the following command in the CLI at the `main.c` folder location:
 ```bash
gcc -fPIC -shared -o mozalloc.so main.c
```
You can then run your target file using the LD_PRELOAD command:
```bash
LD_PRELOAD=./mozalloc.so ./myTestingProgram
```

Ensure to include necessary headers and this custom library in your C program for memory allocation and deallocation using `mozalloc` and `mozafree`.

---

*Note: The above documentation assumes a single-threaded environment and does not address thread safety or memory fragmentation issues.*