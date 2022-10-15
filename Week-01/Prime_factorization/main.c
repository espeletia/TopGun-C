#include <stdio.h>

int main(){

    
    int a;
    int divisor = 3;
    while(scanf("%d", &a) != EOF){
        divisor = 3;
        if(a < 2){
            printf("Invalid input\n");
            continue;
        }
        if(a == 2){
                printf("%d\n", 2);
                a = a/2;
                continue;
        }
        while(a % 2 == 0){
            printf("%d ", 2);
            a = a / 2;
        }
        while(divisor <= a && a >= 2){
            if(a == divisor){
                printf("%d\n", divisor);
                a = a / divisor;
                break;
            }
            if(a % divisor == 0){
                printf("%d ", divisor);
                a = a / divisor;
            }
            else{
                divisor += 2;
            }
        }
        
        
    }

    

    return 0;
}