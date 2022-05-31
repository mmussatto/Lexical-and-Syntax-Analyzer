#include"Source/file.h"

FILE* read_file(char *name, char mode)
{
    FILE *arq;

    arq = fopen(name, &mode);

    return arq;
}

bool read_character(FILE* arq, char *ch)
{
    return (fscanf(arq, "%c", ch) == 1);
}

void return_pointer(FILE  *arq, int shift)
{
    fseek(arq, SEEK_SET + (SEEK_CUR-shift), SEEK_CUR);
}
