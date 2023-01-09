#include <stdio.h>

int main() {

    int nb, nt, nl;
    nb = nt = nl = 0;
    char c;
    while((c = getchar()) != EOF){
        if(c == ' ') ++nb;
        if(c == '\t') ++nt;
        if(c == '\n') ++nl;
    }
    printf("\nNumber of blanks: %d\nNumber of tabs: %d\nNumber of newlines: %d\n", nb, nt, nl);
    return 0;
}