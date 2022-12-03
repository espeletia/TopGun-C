
#include <stdio.h>


int main(){

    int a,b;
    int x,y;
    int count = 0;
    int valid;
    while(scanf("%d %d", &a, &b) != EOF){
        valid = 0;
        count = 0;
        if(a < 0){
            a = a * -1;  
        }
        if(b < 0){
            b = b * -1;
        }
        x = (a > b) ? a : b;
        y = (b < a) ? b : a;
        if(a == 0 && b != 0){
            printf("%d\n", b);
            continue;
        }
        if(a != 0 && b == 0){
            printf("%d\n", a);
            continue;
        }
        if(a == 0 && b == 0) continue;
        for (int i = 1; i <= y; i++)
        {
            if (x % i == 0 && y % i == 0)
            {
                count = i;
            }
            
        }
        printf("%d\n", count);
        }



    return 0;
}