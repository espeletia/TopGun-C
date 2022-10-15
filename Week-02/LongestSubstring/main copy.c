#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Pair{
    char x;
    char y;
} Pair;

char *polindrome(Pair array[],char str[]);


int main()
{
    char del;
    int pairs;
    if(scanf("%d", &pairs) == EOF)return 0;
    Pair *AllPairs = (Pair*) malloc(sizeof(Pair) * pairs);
    for (int i = 0; i < pairs; i++)
    {
        if(scanf(" %c %c", &AllPairs[i].x, &AllPairs[i].y) == EOF) return 0;

    }
    for (int i = 0; i < pairs; i++)
    {
        printf("%c <-> %c\n",AllPairs[i].x, AllPairs[i].y);
    }
    char str[101];
    
    while (scanf("%s", str) != EOF)
    {
        polindrome(AllPairs, str);
    }
    

    
    
    return 0;
}
 
char *polindrome(Pair array[],char str[]){

    int lenght = strlen(str);
        int sublenght = 2;
        int middle = lenght / 2;
        int offset = 1;
        char *substr = malloc(sublenght);
        int num;
        if(lenght % 2 == 0){
            num = 2;
            sublenght = 3;
            while(1){
                substr = realloc(substr, sublenght);
                substr = strncpy(substr, &str[middle - offset] , num);
                substr[strlen(substr)] = '\0';
                // printf("Substring is: %s\n", substr);
                // printf("characters %c %c\n", str[middle - offset], str[middle + offset - 1]);
                if (offset == middle)
                {
                    break;
                }
                
                offset++;
                sublenght += 2;
                num += 2;
            }
            printf("%s\n", substr);
        }

}