#include <stdio.h>

#define BLANK 1
#define NOT_BLANK 0

int main() {

    int c;
    int blank = NOT_BLANK;
    while((c = getchar()) != EOF){
        if(c == ' '){
            if(blank == NOT_BLANK){
                blank = BLANK;
                printf("%c", c);
            }
        }
        else{
            printf("%c", c);
            blank = NOT_BLANK;
        }
    }


    return 0;
}