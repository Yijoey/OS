#include "../include/bitmap.h"
#include <math.h>
// data is an array of uint8_t and needs to be allocated in bitmap_create
//      and used in the remaining bitmap functions. You will use data for any bit operations and bit logic
// bit_count the number of requested bits, set in bitmap_create from n_bits
// byte_count the total number of bytes the data contains, set in bitmap_create



/// Creates a bitmap to contain 'n' bits (zero initialized)
/// \param n_bits
/// \return New bitmap pointer, NULL on error

// typedef struct bitmap {
//     uint8_t *data;
//     size_t bit_count, byte_count;
// } bitmap_t;




bitmap_t *bitmap_create(size_t n_bits)
{
    if(n_bits == 0){
        return NULL;
    }
    bitmap_t *bitmap = malloc(n_bits);
    if(bitmap != NULL){
        bitmap->bit_count = n_bits;
        bitmap->byte_count = ceil(n_bits/8.0);      //ceil() & floor()  incompatible implicit declaration of built-in function ‘ceil’
        // bitmap->data = calloc(bitmap->byte_count,sizeof(bitmap->data));
        bitmap->data = calloc(bitmap->byte_count,sizeof(*bitmap->data));
        if(bitmap->data == NULL){
            free(bitmap);
            return NULL;
        }
    }
    return bitmap;
}


/// Sets the requested bit in bitmap
/// \param bitmap The bitmap
/// \param bit The bit to set
bool bitmap_set(bitmap_t *const bitmap, const size_t bit)
{
	if(bitmap == NULL || bit > bitmap->bit_count){
        return false;
    }
    int index = bit/8;
    int pos = bit%8;
    unsigned int flag = 1;
    flag = flag << pos;                   // flag = 0000...010...000   (shifted k positions)
    bitmap->data[index] = bitmap->data[index] | flag;  //Set the bit at the k-th position in A[i]
    return true;

}

bool bitmap_reset(bitmap_t *const bitmap, const size_t bit)
{
    if(bitmap == NULL || bit > bitmap->bit_count){
        return false;
    }
    int index = bit/8;
    int pos = bit%8;
    unsigned int flag = 1;
    flag = flag << pos;   
    flag = ~flag;     // // flag = 1111...101..111
    bitmap->data[index] = bitmap->data[index] & flag;
    return true;

    
}



/// Returns bit in bitmap
/// \param bitmap The bitmap
/// \param bit The bit to queried
/// \return State of requested bit
bool bitmap_test(const bitmap_t *const bitmap, const size_t bit)
{
   if(bitmap == NULL || bit > bitmap->bit_count){
       return false;
   }
    int index = bit/8;
    int pos = bit%8;
    unsigned int flag = 1;
    flag = flag << pos;       // flag = 0000...010000000

    if(bitmap->data[index] & flag){ //0000...00010000000
        return true;
    }
    return false;
}


/// Find the first set bit
/// \param bitmap The bitmap
/// \return The first one bit address, SIZE_MAX on error/Not found
size_t bitmap_ffs(const bitmap_t *const bitmap)
{
    if(bitmap == NULL ){
        return SIZE_MAX;
    }
    size_t addr;               //‘for’ loop initial declarations are only allowed in C99 mode
    for(addr = 0; addr<bitmap->bit_count; addr++){
        if(bitmap_test(bitmap,addr) == true){
            return addr;
        }
    } 
    return SIZE_MAX;
}


/// Find first zero bit
/// \param bitmap The bitmap
/// \return The first zero bit address, SIZE_MAX on error/Not found
size_t bitmap_ffz(const bitmap_t *const bitmap)
{
    if(bitmap == NULL ){
        return SIZE_MAX;
    }
    size_t addr; 
    for(addr = 0; addr < bitmap->bit_count; addr++){
        if(!bitmap_test(bitmap,addr)){  //if it's 0 it will return 0
            return addr;
        }
    }
    return SIZE_MAX;
}


/// Destructs and destroys bitmap object
/// \param bit The bitmap
/// \return The Success or Failure of destruct and destroy bitmap object
bool bitmap_destroy(bitmap_t *bitmap)
{
    if(bitmap == NULL){
        return false;
    }
    free(bitmap->data);
    bitmap->data = NULL;

    free(bitmap);
    bitmap = NULL;
    return true;
}
