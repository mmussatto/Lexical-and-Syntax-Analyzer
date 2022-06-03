/*
 * **************************************************
 *                                                  *
 * SSC 0605 - Teoria da Computação e Compiladores   *
 *                                                  *
 * Autores:                                         *
 *  - Che Fan Pan                       - 11200421  *
 *  - Eduardo Cavalari Valença          - 11234381  *
 *  - Marcos Vinicius Firmino Pietrucci - 10770072  *
 *  - Murilo Mussatto                   - 11234245  *
 *                                                  *
 * São Carlos - SP                                  *
 * 2022                                             *
 *                                                  *
 * **************************************************
 */

#include"Headers/file.h"

FILE* open_file(char *name, char mode)
{
    FILE *fp;

    fp = fopen(name, &mode);

    return fp;
}

bool read_character(FILE* fp, char *ch)
{
    return (fscanf(fp, "%c", ch) == 1);
}

char* read_file_string(FILE *program, int size)
{
    char *string = (char*) malloc(sizeof(char)*size);
    fread(string, sizeof(char), size, program);
    return string;
}

void move_back_fp(FILE  *fp, int shift)
{
    fseek(fp, SEEK_SET + (SEEK_CUR-shift), SEEK_CUR);
}

int check_EOF(FILE *fp)
{
    char value;

    //Didnt read anything, EOF
    if(!fread(&value, sizeof(char), 1, fp))
        return 1;
    else
    {
        //Return the pointer, this is not EOF
        move_back_fp(fp, 1);
        return 0;
    }

}

//Write in the file file the combination of token name and type
void write_tokens_file(FILE *fp, vec_token *vec_tokens)
{
    int i;
    char comma_space[3] = {',', ' ', '\0'};
    char backspace = '\n';
    token t;

    for(i = 0; i < vec_tokens->size; i++)
    {   
        //Get the current token
        t = vec_tokens->tokens[i];

        //Write the name of the token
        fwrite(&t.name, sizeof(char), strlen(t.name), fp);

        //Write comma and space
        fwrite(&comma_space, sizeof(char), strlen(comma_space), fp);

        //Write the type of the token
        fwrite(&t.type, sizeof(char), strlen(t.type), fp);

        //Write \n
        fwrite(&backspace, sizeof(char), 1, fp);
    } 
}
