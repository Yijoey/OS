#include "../include/allocation.h"
#include <stdlib.h>
#include <stdio.h>

/// Allocates an array of n elements of size member_size in bytes utilizing calloc if the clear flag is set, malloc otherwise.
///	Testing with certain values will show different behavior between calloc and malloc.
/// \param size_t - member size in bytes (can be gotten using the sizeof operator e.g. sizeof(int)
/// \param size_t - number of members in the array
///	\param bool -   1 will clear memory (calling calloc), 0 will not (calling malloc).
/// \return void* - pointer to allocated memory.
void* allocate_array(size_t member_size, size_t nmember,bool clear)
{
    if(clear == 1){
        void *c = calloc(nmember,member_size);
        return c;
    }else{
        void *m = malloc(nmember * member_size);
        return m;
    }

}

/// - Does not initialize expanded memory
/// - Original contents remain unchanged
/// - If passed a null pointer then a malloc will occur.
/// - May move memory to a new location

/// Simple wrapper around realloc.
/// \param void* - pointer to memory to resize.
/// \param size_t - size of memory to allocate
/// \return void* - pointer to reallocated memory region, may be same as original pointer.
void* reallocate_array(void* ptr, size_t size)
{
    if(ptr == NULL){
        return malloc(0);  //  So realloc(NULL, 0) is the same as malloc(0)
    }
    return realloc(ptr,size); 
}


// Free
// - Should not be called on a null pointer or a pointer not received from allocation.
// - Free does not reinitialize the memory region.
// - An "Invalid Pointer" error may be a sign of bad memory operations or an overflow from a memset, memcpy, or allocation or freeing a pointer twice.
// - If the received pointer is null no operation is performed.

/// \param void* - pointer to memory to free.

void deallocate_array(void** ptr)
{
    if(*ptr == NULL){
        return;
    }
    
    free(*ptr);      /// Wrapper around free. Frees memory and sets received pointer to NULL.
    *ptr = NULL;
    return;          /// \return Nothing


}


/// Takes a file name and reads a line into a newly allocated buffer
/// \param char* - filename to read from
/// \return char* - Pointer to malloced heap space containing buffer

char* read_line_to_buffer(char* filename)
{
    if(filename == NULL){
        return filename;
    }
    FILE *file = fopen(filename,"r");
    if(file != NULL){
        char* NewBuffer = malloc(512);      // maximum number of characters that can be transferred through our standard input stream, stdin.
        fgets(NewBuffer,512,file);         // char *fgets(char *str, int n, FILE *stream)
        fclose(file);
        return NewBuffer;
    }
    return filename;
}
