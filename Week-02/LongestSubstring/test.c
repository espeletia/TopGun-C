#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
int main(void)
{
    char text[24] = "The test string is here";
    char *subtext = malloc(40);
    char *lol;
    strncpy(subtext,&text[9],40);
    //subtext[6] = '\0';
    // lol = subtext;
    // subtext = "pp";
    printf("The original string is: %s\n",text);
    printf("Substring is: %s",subtext);
    
    

    return 0;
}