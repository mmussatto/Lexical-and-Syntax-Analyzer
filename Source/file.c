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
    fseek(fp, - shift, SEEK_CUR); 
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


//Write in the file the combination of token name and type
void write_tokens_file(FILE *fp, vec_token *vec_tokens)
{
    int i;
    char backspace = '\n';
    token t;

    for(i = 0; i < vec_tokens->size; i++)
    {   
        //Get the current token
        t = vec_tokens->tokens[i];

        //Write the name of the token
        fwrite(t.name, sizeof(char), strlen(t.name), fp);

        //Write comma and space
        fwrite(", ", sizeof(char), 2, fp);

        //Write the type of the token
        fwrite(t.type, sizeof(char), strlen(t.type), fp);

        //Write \n
        fwrite(&backspace, sizeof(char), 1, fp);
    } 
}


void read_matrix_csv_file(FILE *csv, int **matrix)
{
    //Consider the file already opened

    //Control variables
    int value, row = 0, col = 0;
    char trash;

    //Reading the transition matrix from a csv file
    for(row = 0; row < NUM_STATES; row++)
        for(col = 0; col < VALID_CHARACTERS; col++)
        {
            //Read the integer
            fscanf(csv, "%d", &value);

            //Read the comma
            fscanf(csv, "%c",&trash);

            //Add to the matrix
            matrix[row][col] = value;
        }
}

void read_reserved_csv_file(FILE *csv, reserved* vec_reserved)
{
    //Consider the file already opened

    //Control variables
    int i;

    //Reading the transition matrix from a csv file
    for(i = 0; i < NUM_RESERVEDS; i++)
    {
        //Read the integer
        fscanf(csv, "%s%*c %s", vec_reserved[i].reserved_symb.name, vec_reserved[i].reserved_symb.type);
    }
}


void read_error_csv_file(FILE *csv, error *vec_errors)
{
    //Consider the file already opened

    //Control variables
    int i;
    char buff[50];
    char s_error[20];

    //Reading the transition matrix from a csv file
    for(i = 1; i < NUM_ERRORS; i++){
       
        // fgets(buff, sizeof(buff), csv);

        // sscanf(buff, "%s", s_error);

        // printf("%s\n", s_error);

        // //Add to the matrix
        // vec_errors[i].error_token.type = strdup(s_error);
    }

}
