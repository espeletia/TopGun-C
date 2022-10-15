#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Pair
{
    char x;
    char y;
} Pair;
int Alias(Pair arr[], char l, char r, int size);
char *palindrome(char str[]);
char *getlen();

int main()
{
    int pairs = -1;
    scanf("%d", &pairs);
    if(pairs < 0){
        printf("Invalid input\n");
        return 0;
    }
    
        Pair *AllPairs = (Pair *)malloc(sizeof(Pair) * pairs);
        for (int i = 0; i < pairs; i++)
        {
            if (scanf(" %c %c", &AllPairs[i].x, &AllPairs[i].y) == EOF)
                return 0;
        }
        // for (int i = 0; i < pairs; i++)
        // {
        //     printf("%c <-> %c\n", AllPairs[i].x, AllPairs[i].y);
        // }
    
    char str[10000];
    while (scanf("%s", str) != EOF)
    {
        //char *str = getlen();
        //printf("ORIGINAL STRING:%s\n", str);
        char *substr = malloc(1);
        int l, r;
        int bigS = 0;
        for (int i = 0; i < strlen(str); i++)
        {
            l = i;
            r = i;

            while (l >= 0 && r <= strlen(str) - 1)
            {
                // printf("\nL: %c, R: %c, I: %c\n", str[l], str[r], str[i]);
                if (str[r] != str[l] && Alias(AllPairs, str[l], str[r], pairs) == 0)break;
                    
                if (r - l + 1 > bigS)
                {
                    bigS = r - l + 1;
                    substr = realloc(substr, bigS);
                    strncpy(substr, &str[l], bigS);
                    substr[bigS] = '\0';
                }
                l -= 1;
                r += 1;
            }
            l = i;
            r = i + 1;
            while (l >= 0 && r <= strlen(str) - 1)
            {
                // printf("\nL: %c, R: %c, I: %c\n", str[l], str[r], str[i]);
                if (str[r] != str[l] && Alias(AllPairs, str[l], str[r], pairs) == 0)break;
                if (r - l + 1 > bigS)
                {
                    bigS = r - l + 1;
                    substr = realloc(substr, bigS);
                    strncpy(substr, &str[l], bigS);
                    substr[bigS] = '\0';
                }
                l -= 1;
                r += 1;
            }
        }
        printf("%s\n", substr);
    }

    return 0;
}

int Alias(Pair arr[], char l, char r, int size){
    for (int i = 0; i < size; i++)
    {
        if(arr[i].x == l && arr[i].y == r)return 1;
        if(arr[i].y == l && arr[i].x == r)return 1;
    }
    return 0;
    



}

char *getlen()
{
    char x;
    int size = 1;
    char *temp = NULL;
    while ((x = getc(stdin)) && x != '\n' && x != ' ' && x != EOF)
    {
        size++;
        temp = realloc(temp, size);
        temp[size - 2] = x;
        temp[size - 1] = '\0';
    }
    return temp;
}