#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/arrays.h"

// LOOK INTO MEMCPY, MEMCMP, FREAD, and FWRITE

bool array_copy(const void *src, void *dst, const size_t elem_size, const size_t elem_count)
{
    if( !src || !dst || elem_count == 0 || elem_size == 0){
        return false;
    }
    memcpy(dst,src,elem_size * elem_count);
    return true;
}

bool array_is_equal(const void *data_one, void *data_two, const size_t elem_size, const size_t elem_count)
{
    if( data_one == NULL || data_two == NULL || elem_count * elem_size == 0){
        return false;
    }
    if(!memcmp(data_one,data_two,elem_count * elem_size)){
        return true;
    }
    return false;
}

ssize_t array_locate(const void *data, const void *target, const size_t elem_size, const size_t elem_count)
{
    if( !data || !target || elem_count == 0 || elem_size == 0){
        return -1;
    }
    char* checking = (char*) data;

    for(ssize_t i = 0; i < elem_count; i++){
        int compare = 0;
        compare = memcmp(checking,target,elem_size);
        if(compare == 0){
            return i;
        }
        checking = checking + elem_size;
    }
    return -1;
}

bool array_serialize(const void *src_data, const char *dst_file, const size_t elem_size, const size_t elem_count)
{
    if(!src_data || !dst_file || elem_count == 0 || elem_size == 0 || strcmp(dst_file, "\n") == 0){  //  Failure Value of: array_serialize(data,dst_file,sizeof(int),5)
        return false;
    }

    FILE* file = fopen(dst_file, "w");
    if(file == NULL){
        return false;
    }

    size_t res = fwrite(src_data,elem_size,elem_count,file);
    fclose(file);

    if(res != elem_count){
        return false;
    }
    return true;

}

bool array_deserialize(const char *src_file, void *dst_data, const size_t elem_size, const size_t elem_count)
{
    if(!src_file || !dst_data || elem_count == 0 || elem_size == 0 || strcmp(src_file, "\n") == 0){
        return false;
    }
    FILE* file = fopen(src_file,"r");
    if(file == NULL){
        return false;
    }

    size_t res  = fread(dst_data,elem_size,elem_count,file);

    fclose(file);
    
    if(res != elem_count){
        return false;
    }
    return true;

}

