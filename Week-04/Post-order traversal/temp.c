#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int value;
    struct node *left;
    struct node *right;
};

struct node *createNode(int value)
{
    struct node *newNode = malloc(sizeof(struct node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

char *getlen()
{
    char x;
    int size = 1;
    char *temp = NULL;
    while ((x = getc(stdin)) && x != EOF)
    {
        if (x == '\n' || x == ' ' || x == '\t')
            continue;
        size++;
        temp = realloc(temp, size);
        temp[size - 2] = x;
        temp[size - 1] = '\0';
    }

    return temp;
}

void postorderTraversal(struct node *root)
{
    if (root == NULL)
        return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d\n", root->value);
}

int leftOrRight(char temp[])
{
    if (strcmp(temp, "{") == 0)
    {
        return 1;
    }
    if (strcmp(temp, "[") == 0)
    {
        return 2;
    }
    if (strcmp(temp, "}") == 0)
    {
        return 3;
    }
    if (strcmp(temp, "]") == 0)
    {
        return 4;
    }
    return -1;
}

int i = 0;

char *number(char *str, int z)
{
    int a = 0;
    int b = 0;
    char *temp = NULL;
    int size = 1;
    while (1)
    {
        switch (str[i])
        {
        case '\0':
            if(z > 0)
            return NULL;
            return temp;
            break;
        case '0':
            break;
        case '1':
            break;
        case '2':
            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
            break;
        case '6':
            break;
        case '7':
            break;
        case '8':
            break;
        case '9':
            break;
        case '-':
            if(b == 0)
            a++;
            else{
               printf("Invalid input\n");
                exit(0); 
            }
            break;
        case '{':
            if(i != 0)
            return temp;
            printf("Invalid input\n");
                exit(0); 
            break;
        case '[':
            if(i != 0)
            return temp;
            printf("Invalid input\n");
                exit(0); 
            break;
        case '}':
            if(i != 0)
            return temp;
            printf("Invalid input\n");
                exit(0); 
            break;
        case ']':
            if(i != 0)
            return temp;
            printf("Invalid input\n");
                exit(0); 
            break;
        default:
            printf("Invalid input\n");
            exit(0);
            break;
        }
        size++;
        temp = realloc(temp, size);
        temp[size - 2] = str[i];
        temp[size - 1] = '\0';
        i++;
        b++;
    }
}

struct node *parseInput(char *str, int y, int z) // y: opening character, z: recursion depth (debug tool)
{
    char *temp = NULL;
    int left = 0;
    int right = 0;   
    if (str == NULL)
    {
        exit(0);
    }

    temp = number(str, z);
    //printf("\n\t%d\n", atoi(temp));
    if (temp == NULL && y > 0) 
    {
        printf("Invalid input\n");
        exit(0);
    }
    
    int n = atoi(temp);
    //printf("%d, (%d, %d), %d, %c\n", n, symbol, y, i, str[i]);
    struct node *root = createNode(n);
    while (str[i] != '\0')
    {
        
        //printf("%c %d\n", str[i], z);
        if (str[i] == '{')
        {
            if(left > 0){
                printf("Invalid input\n");
            exit(0);    
            }
            int b = z + 1;
            //printf("calling left %d\n", z);
            i++;
            left++;
            root->left = parseInput(str, 1, b);
        }
        if (str[i] == '[')
        {
            //printf("calling right %d, %c\n", i, str[i]);
            if(right > 0){
                printf("Invalid input\n");
            exit(0);    
            }
            int b = z + 1;
            i++;
            right++;
            root->right = parseInput(str, 2, b);
        }
        if (str[i] == '}')
        {
            //printf("Closing Left (%c, %d)\n", str[i], z);
            i++;
            if (y == 1){
                //printf("%d", z);
                return root;
            }
            printf("Invalid input\n");
            exit(0);
        }
        if (str[i] == ']')
        {
            //printf("Closing Right (%c, %d)\n", str[i], z);
            i++;
            if (y == 2){
                //printf("%d", z);
                return root;
            }
            printf("Invalid input\n");
            exit(0);
        }
        // if (str[i] == '{')
        //     symbol = 1;
        // if (str[i] == '[')
        //     symbol = 2;
        // if (str[i] == '}')
        //     symbol = 3;
        // if (str[i] == ']')
        //     symbol = 4;

    }
    if(z > 0){

        printf("Invalid input\n");
        exit(0);
    }
    //printf("\nRETURNING MAIN ROOT %d\n", z);
    return root;
}

int main()
{
    char *temp = getlen();
    // printf("====TESTING ASCII====\n");
    // int g = 0;
    // while(temp[g] != '\0'){
    //     printf("%d\t%c:%d\n", g, temp[g],temp[g]);
    //     g++;
    // }
    // printf("====TESTING ASCII====\n");
    //printf("%s", temp);
    struct node *root = parseInput(temp, 0, 0);

    postorderTraversal(root);
    return 0;
}