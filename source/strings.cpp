

#include "strings.h"
#include <string.h>
void display_strings_valid(FILE* file,CallbackFunction callback)
{
    size_t CHUNK_SIZE = 4 * 1024 * 1024;
    size_t byteRead = 0; 

    char* ret = (char*) malloc(CHUNK_SIZE); 
    char* buffer = (char* ) malloc( CHUNK_SIZE);
    fseek(file, 0, SEEK_SET);
    // Dat o ngoai vi o vung bien
    size_t index;
    size_t index_str = 0; 
    while(1)
    {
        size_t byte_index = fread(buffer, 1, CHUNK_SIZE,file); 
        if( byte_index == 0)
        {
            free(ret);
            free(buffer);
            return ;
        }
        byteRead += byte_index;

        for (index = 0; index < byte_index; index++)
        {
            if ( buffer[index] >= 32 && buffer[index] <= 126)
            {
                ret[index_str] = buffer[index]; 
                index_str++;
            } else 
            {
                if ( index_str >= 4)
                {
                    ret[index_str] = '\0'; 
                    printf("%s\n",strdup(ret));
                    callback(strdup(ret));
                } 
                index_str = 0; 
                ret[0] = '\0';
            }
        }
    }
    free(ret);
}