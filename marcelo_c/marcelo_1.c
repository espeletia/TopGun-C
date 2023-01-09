#include <stdio.h>

void notGoingToRun() {
    printf("I will not be printed\n");
}

int main() {
    printf("cigani skurveny\n");
    notGoingToRun();
    return 0;
}