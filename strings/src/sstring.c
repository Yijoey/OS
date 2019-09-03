#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/sstring.h"


// Verifies if the passed character array is null terminated or not.
// \param str the character array that may be null terminated
// \param length to prevent buffer overflow while checking
// \return true if the character array is a string

bool string_valid(const char *str, const size_t length)
{
    if(str == NULL || length ==0){
        return false;
    }
    //return strlen(str) == length;

    if(str[length-1] == '\0'){
        return true;
    }
    //return *(str + length - 1) == '\0';
    return false;
}


// Copy the contents of the passed string upto the given length
// \param str is the string that will be copied into heap allocated string
// \param length the number of characters to copy
// \return an allocated pointer to new string, else NULL
char *string_duplicate(const char *str, const size_t length)
{
    if(str == NULL || length == 0){
        return NULL;
    }
    char *NewString = malloc(sizeof(char) * length);

    if(NewString != NULL){
        strncpy(NewString,str,length);  //char *strncpy(char *destinin, char *source, int maxlen);
        return NewString;
    }
    return NULL;
}



// Checks to see if both strings contain the same characters
// \param str_a the string that will be compared against
// \param str_b the string that will be compared with str_a
// \param length the number of characters to be compared
bool string_equal(const char *str_a, const char *str_b, const size_t length)
{
    if (str_a == NULL && str_b == NULL) {
        return true;
    }
    if(str_a == NULL || str_b == NULL || length == 0){
        return false;
    }

    // if(strcmp(str_a, str_b) == 0){
    //     return true;
    // }
    // return false;

    return strcmp(str_a, str_b) == 0;
}

// Finds the number of characters in the string, not including the null terminator
// \param str the string to count the number of characters in the string
// \param length the max possible string length for the application
// \return the length of the string or -1 for invalid string
int string_length(const char *str, const size_t length)
{
    if (str == NULL || length == 0){
        return -1;
    }
    return strlen(str);

}


// Split the incoming string to tokens that are stored in a passed allocated tokens string array
// \param str the string that will be used for tokenization
// \param delims the delimiters that will be used for splitting the str into segments
// \param str_length the lengt of the str
// \param tokens the string array that is pre-allocated and will contain the parsed tokens
// \param max_token_length the max length of a token string in the tokens string array with null terminator
// \param requested_tokens the number of possible strings that tokens string array can contain
// \return returns the number of actual parsed tokens, 0 for incorrect params, and -1 for incorrect token allocation
int string_tokenize(const char *str, const char *delims, const size_t str_length, char **tokens, const size_t max_token_length, const size_t requested_tokens)
{
    if(str == NULL || delims == NULL || str_length == 0 || tokens == NULL || max_token_length == 0 || requested_tokens == 0){
        return 0;
    }
    for(int i = 0; i <requested_tokens; i++){
        if(tokens[i] == NULL){
            return -1;
        }
    }

    char* StrCopy = malloc(sizeof(str));
    strncpy(StrCopy,str,str_length);  //char *strncpy(char *dest, const char *src, size_t n)

    char * token;
    int count = 0;
    token = strtok(StrCopy,delims); 
    strcpy(tokens[0], token);

    while(count < requested_tokens -1){
        count++;
        token = strtok(NULL, delims);     //char *strtok(char *str, const char *delim)
        strcpy(tokens[count], token);
    }
    free(StrCopy);
    return count+1;
}

// Converts the passed string into a integer
// \param str The string that contains numbers
// \param converted_value the value converted from the passed string str
// \return true for a successful conversion, else false

bool string_to_int(const char *str, int *converted_value)
{
    if(str == NULL || converted_value == NULL){
        return false;
    }
    if(atoi(str)==-1){
        return false;
    }
    else *converted_value = atoi(str);
    return true;
}
