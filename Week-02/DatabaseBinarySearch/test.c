#include <stdio.h>
#include <stdlib.h>

char *getln();
int main(int argc, char const *argv[])
{
    
    char *pp, *pp1;
    
    pp = getln();
    printf("%s", pp);

    return 0;
}

char *getln()
{
    char x;
    int size = 1;
    char *temp = malloc(size);
    while (1)
    {
        x = getc(stdin);
        if (x == '\n' || x == EOF|| x == ' ')
            break;
        size++;
        temp = realloc(temp, size);
        temp[size - 2] = x;
        temp[size - 1] = '\0';
    }
    return temp;
}
