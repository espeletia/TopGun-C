#include <stdio.h>

int main()
{
    int num;
    int a, b, c;
    int x, y, z;
    scanf("%d", &num);
    x = a = num;
    scanf("%d", &num);
    y = b = num;
    scanf("%d", &num);
    z = c = num;
    int sum = a + b + c;
    while (scanf("%d", &num) != EOF)
    {
        a = b;
        b = c;
        c = num;
        if (sum > a + b + c)
        {
            sum = a + b + c;
            x = a;
            y = b;
            z = c;
        }
    }
    printf("%d\n%d\n%d\n", x, y, z);
    return 0;
}

// #include <stdio.h>

// int main() {
//     int num;
//     int a,b,c;
//     int x,y,z;
//     scanf("%d", &num);
//     x = a = num;
//     scanf("%d", &num);
//     y = b = num;
//     scanf("%d", &num);
//     z = c = num;
//     int sum = a + b + c;
//     while(scanf("%d", &num) != EOF){
//         a = b;
//         b = c;
//         c = num;
//         if(a < 0 && b < 0 && c < 0 && sum > a + b + c){
//             x = a;
//             y = b;
//             z = c;
//         }
//         sum = a + b + c;
//     }
//     printf("%d\n%d\n%d\n", x, y ,z);
//     return 0;
// }