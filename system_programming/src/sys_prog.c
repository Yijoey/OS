#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../include/sys_prog.h"

// LOOK INTO OPEN, READ, WRITE, CLOSE, FSTAT/STAT, LSEEK
// GOOGLE FOR ENDIANESS HELP

//https://www.thinkage.ca/gcos/expl/c/lib/open.html

// Read contents from the passed into an destination
// \param input_filename the file containing the data to be copied into the destination
// \param dst the variable that will be contain the copied contents from the file
// \param offset the starting location in the file, how many bytes inside the file I start reading
// \param dst_size the total number of bytes the destination variable contains
// return true if operation was successful, else false


bool bulk_read(const char *input_filename, void *dst, const size_t offset, const size_t dst_size) {
    if (input_filename == NULL || dst == NULL || offset < 0 || dst_size < 0) {
        return false;
    }
    int fd = open(input_filename, O_RDONLY);
    if (fd == -1) {
        return false;
    }

    if (lseek(fd, offset, SEEK_SET) < 0) {       //off_t  lseek(int fildes, off_t offset, int whence);
        close(fd);
        return false;
    }
    if (read(fd, dst, dst_size) == -1 ) {       //// ssize_t read(int fd, void *buf, size_t count);
        close(fd);
        return false;
    }
    close(fd);
    return true;
}


// Writes contents from the data source into the outputfile
// \param src the source of the data to be wrote to the output_filename
// \param output_filename the file that is used for writing
// \param offset the starting location in the file, how many bytes inside the file I start writing
// \param src_size the total number of bytes the src variable contains
// return true if operation was successful, else false
bool bulk_write(const void *src, const char *output_filename, const size_t offset, const size_t src_size)
{
    if(output_filename == NULL || src == NULL || offset < 0 || src_size < 0){
        return false;
    }
    int fd = open(output_filename , O_WRONLY);
    if(fd == -1){
        return false;
    }
    if(lseek(fd, offset, SEEK_SET) < 0 ){
        close(fd);
        return false;
    }
    if (write(fd, src, src_size) == -1){
        close(fd);
        return false;
    }
    close(fd);
    return true;

}

// Returns the file metadata given a filename
// \param query_filename the filename that will be queried for stats
// \param metadata the buffer that contains the metadata of the queried filename
// return true if operation was successful, else false

bool file_stat(const char *query_filename, struct stat *metadata)   //int stat(const char *path, struct stat *buf); 
{
    if(query_filename == NULL || metadata == NULL){                 //fstat()用来将参数fildes 所指的文件状态, 复制到参数buf 所指的结构中(struct stat)
        return false;
    }
    int res = stat(query_filename, metadata);
    if(res < 0){
        return false;
    }
    return true;
}


// Converts the endianess of the source data contents before storing into the dst_data.
// The passed source data bits are swapped from little to big endian and vice versa.
// \param src_data the source data that contains content to be stored into the destination
// \param dst_data the destination that stores src data
// \param src_count the number of src_data elements
// \return true if successful, else false for failure
bool endianess_converter(uint32_t *src_data, uint32_t *dst_data, const size_t src_count)
{
    if(src_data == NULL || dst_data == NULL || src_count == 0){
        return false;
    }
    size_t i;
    for( i = 0; i < src_count; i++){
        uint32_t num = src_data[i];
        uint32_t b0,b1,b2,b3;
        b0 = (num & 0x000000ff) << 24u;
        b1 = (num & 0x0000ff00) << 8u;
        b2 = (num & 0x00ff0000) >> 8u;
        b3 = (num & 0xff000000) >> 24u;
        dst_data[i] = b0|b1|b2|b3;

    }
    return true;
}

