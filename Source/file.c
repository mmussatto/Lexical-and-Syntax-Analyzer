#include"Source/file.h"

FILE* ReadFile(char *name, char mode)
{
    FILE *arq;

    arq = fopen(name, &mode);

    return arq;
}

bool ReadCharacter(FILE* arq, char *ch)
{
    return (fscanf(arq, "%c", ch) == 1);
}

void ReturnPointer(FILE  *arq, int shift)
{
    fseek(arq, SEEK_SET + (SEEK_CUR-shift), SEEK_CUR);
}
