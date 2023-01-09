#include <stdio.h>

int main(){
    int c;
    while(c = (getchar() != EOF)){
        printf("is not EOF: %d\n", c);
    }
    printf("is not EOF: %d\n", c);
    return 0;
}