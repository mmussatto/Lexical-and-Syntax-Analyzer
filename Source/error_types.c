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

#include "Headers/error_types.h"


error* create_errors_vector(int n)
{
    error* vec_error = (error*) calloc(n, sizeof(error));
    return vec_error;
}


void free_errors_vector(error* vec_error)
{
    int i;

    for (i = 0; i < NUM_ERRORS; i++){
        free(vec_error[i].error_token.name);
        free(vec_error[i].error_token.type);
    }
    free(vec_error);
}


void populate_errors_vector(error* vec_errors, char* file_name)
{ 
    FILE *tsv = open_file(file_name, 'r');

    read_error_tsv_file(tsv, vec_errors);

    fclose(tsv);

}


void read_error_tsv_file(FILE *tsv, error *vec_errors)
{
    //Consider the file already opened

    //Control variables
    int i;
    char buff[100];
    char s_error[100];

    //Reading the errors from a tsv file
    for(i = 1; i < NUM_ERRORS; i++){
       
        //Reads line from file and puts it in a buffer
        fgets(buff, sizeof(buff), tsv);

        //Get only the error from the buffer
        sscanf(buff, "%[^\n]s", s_error);

        //Add to the matrix
        vec_errors[i].error_token.type = strdup(s_error);

        //printf("%s\n", s_error);      //Debug print to terminal
    }

}


synt_error_vec* create_synth_error_vector(int n)
{
    //Alloc the synt error vector
    synt_error_vec* vec_synt_error = (synt_error_vec*) malloc(sizeof(synt_error_vec));
    
    //Stores the size
    vec_synt_error->size = n;

    vec_synt_error->list_size = 0;

    //Initialize the error description
    vec_synt_error->list_errors = (synt_error *) malloc(n*sizeof(synt_error));

    return vec_synt_error;
}


//Add syntatic errors to vector
void add_synt_error(synt_error_vec* vec_synt_error, char *description, int linha)
{
    //Checks if it needs to reallocate memory
    if(vec_synt_error->list_size >= vec_synt_error->size - 1)
    {
        vec_synt_error->size += 10;
        vec_synt_error->list_errors = realloc(vec_synt_error->list_errors, vec_synt_error->size*sizeof(synt_error));
    }

    //Adds the error
    vec_synt_error->list_errors[vec_synt_error->list_size].desc = strndup(description, strlen(description) - 1);
    vec_synt_error->list_errors[vec_synt_error->list_size].line = linha;

    //Increases the number of errors in the vector
    vec_synt_error->list_size++;
}


void free_synt_errors_vector(synt_error_vec* vec_synt_error)
{
    int i;

    //Deallocate the description strings
    for (i = 0; i < vec_synt_error->list_size; i++){
        free(vec_synt_error->list_errors[i].desc);
    }

    //Free vector
    free(vec_synt_error->list_errors);
    free(vec_synt_error);
}


//Sorts error vector using its line
void sort_synt_error_vec(synt_error_vec *vec_synt_error){
    
    int i,j;
    int bigger;

    char *temp_desc;
    int temp_line;

    for (i = vec_synt_error->list_size - 1; i >= 0; i--){
        bigger = i;
        
        //Get greatest line to move it
        for (j = i - 1; j >= 0; j--){
            if(vec_synt_error->list_errors[j].line > vec_synt_error->list_errors[i].line)
                bigger = j;
        }

        //If needs to change positions
        if (i != bigger){
            //Invert desc and line
            temp_line = vec_synt_error->list_errors[bigger].line;
            temp_desc = vec_synt_error->list_errors[bigger].desc;

            vec_synt_error->list_errors[bigger].line = vec_synt_error->list_errors[i].line;
            vec_synt_error->list_errors[bigger].desc = vec_synt_error->list_errors[i].desc;

            vec_synt_error->list_errors[i].line = temp_line;
            vec_synt_error->list_errors[i].desc = temp_desc;
        }

    }
    
}


void write_error_file(FILE *fp, synt_error_vec *vec_synt_error, vec_token *vec_tokens)
{
    //Control variables
    int i;
    synt_error er;
    char *substring;

    //Run the tokens vector searching for errors
    for(i = 0; i< vec_tokens->size; i++)
    {
        //Token type with less than 14 letters can't be errors
        if(strlen(vec_tokens->tokens[i].type) > 14)
        {
            substring = strndup(vec_tokens->tokens[i].type, 14);
            if(strcmp(substring, "Lexical Error:") == 0)
            {
                //Get error token name
                char error_char[10] = "";
                sprintf(error_char, "(%.6s) ", vec_tokens->tokens[i].name);

                //Add error token name to error message
                int length = strlen(vec_tokens->tokens[i].type) + strlen(error_char) + 1;
                vec_tokens->tokens[i].type = realloc(vec_tokens->tokens[i].type, length * sizeof(char));
                strcat(vec_tokens->tokens[i].type, error_char);

                //Remove \r from the error message
                if (vec_tokens->tokens[i].type[strcspn(vec_tokens->tokens[i].type, "\r")] != 0)
                    vec_tokens->tokens[i].type[strcspn(vec_tokens->tokens[i].type, "\r")] = ' ';
                
                //Add error to the vector
                add_synt_error(vec_synt_error, vec_tokens->tokens[i].type, vec_tokens->tokens[i].line);
            }

            free(substring);
        }
    }


    //Sort the errors vector
    sort_synt_error_vec(vec_synt_error);

    //No errors
    if(vec_synt_error->list_size == 0)
    {
        //Compilation sucessful 
        fprintf(fp, "Compilation successful.\nI can finally rest and watch the sun rise on a grateful universe.\n");
        
        return;
    }

    //Traverse the tokens vector
    for(i = 0; i < vec_synt_error->list_size; i++)
    {   
        //Get the current token
        er = vec_synt_error->list_errors[i];

        //Write the name of the token
        fwrite(er.desc, sizeof(char), strlen(er.desc), fp);

        //Write comma and space
        fwrite(", ", sizeof(char), 2, fp);

        //Write the line of the problem
        fprintf(fp, "%d \n", er.line);
    } 
}