#include <stdio.h>

int main()
{
    int a, b, c;
    int temp;
    int x;
    while(scanf("%d %d", &a, &b) != EOF)
    {
        if (b < a)
        {
            c = b;
            b = a;
            a = c;
        } 
        b--;
        if (a < 2 || b < 2)
        {
            printf("Invalid input\n");
            continue;
        }
        x = 0;
        
        for (int i = a; i <= b; i++)
        {
            temp = 0;
            for (int j = 2; j <= i; j++)
            {
                if (i % j == 0 && i != j){
                temp++;
                break;
                }  
            }
            if (temp == 0)x++;
        }
        printf("%d\n", x);
    }
    return 0;
}