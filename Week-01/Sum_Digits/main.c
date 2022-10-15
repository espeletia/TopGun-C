#include <stdio.h>
#include <stdlib.h>

int main(){
    
    char num[32];
    int sum = 0;
    int count = 0;
    int x = 0;
    int balls = 0;
    while(scanf("%s", num) != EOF){
        sum = 0;
        x = 0;
        balls = 0;
        count =0;
        while(x == 0){
            switch (num[count])
            {
            case '\0':
                x = 1;
                break;
            case '0':
                break;
            case '1':
                sum += 1;
                break;
            case '2':
                sum += 2;
                break;
            case '3':
                sum += 3;
                break;
            case '4':
                sum += 4;
                break;
            case '5':
                sum += 5;
                break;
            case '6':
                sum += 6;
                break;
            case '7':
                sum += 7;
                break;
            case '8':
                sum += 8;
                break;
            case '9':
                sum += 9;
                break;
            case '-':
                break;
            default:
                printf("Invalid input\n");
                balls = 1;
                x = 1;
                break;
            }
            count++;
        }
        if(balls == 0){
        printf("%d\n",sum);

        }
        

    }

    return 0;
}