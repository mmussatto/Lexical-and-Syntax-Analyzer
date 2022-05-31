#include <stdio.h>
#include <stdlib.h>
#include "Source/file.h"

int main(int argc, char** argv)
{
    //Minion Gostoso  ^-^
    FILE *program = Read_File(argv[1],'r');
    char token;

    if(argc != 2)
    {
        printf("Provide just the name of the file\n");
        return 1;
    }
   
    if(program == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }
    
    /*------ Lexical analyser logic --------*/
    while(Read_Character(program, &token))
    {
        printf("%c", token);
        //Implementing the finite state
    }
    
    fclose(program);
    return 0;
}