#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person
{
    int year;
    int month;
    int day;
    char *name;
};

struct Node
{
    struct Person data;
    struct Node *left;
    struct Node *right;
};

char *getln()
{
    char x;
    int size = 1;
    char *temp = malloc(size);
    getc(stdin);
    while ((x = getc(stdin)) && x != '\n' && x != EOF)
    {

        size++;
        temp = realloc(temp, size);
        temp[size - 2] = x;
        temp[size - 1] = '\0';
    }
    return temp;
}


struct Person GenerateNewPerson()
{
    char year[5];
    char month[3];
    char day[3];
    scanf("%s %s %s", year, month, day);
    struct Person data;
    data.name = getln();
    data.day = atoi(day);
    data.month = atoi(month);
    data.year = atoi(year);
    return data;
}

int comparePpl(struct Person person1, struct Person person2)
{
    if (person1.year == person2.year)
    {
        if (person1.month == person2.month)
        {
            if (person1.day == person2.day)
            {
                if (strcmp(person1.name, person2.name) == 0)
                {
                    return 0;
                }
                return (strcmp(person1.name, person2.name) > 0) ? 1 : 2;
            }
            return (person1.day > person2.day) ? 1 : 2;
        }
        return (person1.month > person2.month) ? 1 : 2;
    }
    return (person1.year > person2.year) ? 1 : 2;
}

struct Node *FindMin(struct Node *root)
{
    while (root->left != NULL)
        root = root->left;
    return root;
}

struct Node *Insert(struct Node *root, struct Person data)
{
    if (root == NULL)
    {
        struct Node *temp = malloc(sizeof(struct Node));
        root = temp;
        root->data = data;
        root->left = root->right = NULL;
        printf("Stored\n");
    }
    else if (comparePpl(data, root->data) == 2)
    {
        root->left = Insert(root->left, data);
    }
    else if (comparePpl(data, root->data) == 1)
    {
        root->right = Insert(root->right, data);
    }
    else
    {
        printf("Already stored\n");
    }
    return root;
}

void Find(struct Node *root, struct Person data)
{
    if (root == NULL)
    {
        printf("Not found\n");
        return;
    }
    if (comparePpl(root->data, data) == 0)
    {
        printf("Found\n");
        return;
    }
    if (comparePpl(root->data, data) == 1)
        Find(root->left, data);
    if (comparePpl(root->data, data) == 2)
        Find(root->right, data);
}

struct Node *Delete(struct Node *root, struct Person data)
{
    if (root == NULL)
    {
        printf("Not found\n");
        return root;
    }
    else if (comparePpl(root->data, data) == 1)
        root->left = Delete(root->left, data);
    else if (comparePpl(root->data, data) == 2)
        root->right = Delete(root->right, data);
    else
    {
        // Caso 1: No tiene hijos
        if (root->left == NULL && root->right == NULL)
        {
            free(root->data.name);
            free(root);
            root = NULL;
            printf("Deleted\n");
        }
        // Caso 2: Tiene 1 hijo
        else if (root->left == NULL)
        {
            struct Node *temp = root;
            root = root->right;
            free(temp->data.name);
            free(temp);
            printf("Deleted\n");
        }
        else if (root->right == NULL)
        {
            struct Node *temp = root;
            root = root->left;
            free(temp->data.name);
            free(temp);
            printf("Deleted\n");
        }
        // Caso 3: Tiene 2 Hijos
        else
        {
            struct Node *temp = FindMin(root->right);
            root->data = temp->data;
            root->data.name = malloc(strlen(temp->data.name) + 1);
            strcpy(root->data.name, temp->data.name);        
            root->right = Delete(root->right, temp->data);
        }
    }
    return root;
}

void Inorder(struct Node *root)
{
    if (root == NULL)
        return;
    Inorder(root->left);
    printf("%d, %d, %d, %s\n", root->data.year, root->data.month, root->data.day, root->data.name);
    Inorder(root->right);
}


int main()
{
    struct Node *root = NULL;
    char pee[2];
    while (scanf("%s", pee) != EOF)
    {
        struct Person data = GenerateNewPerson();
        if (pee[0] == 'S')
            root = Insert(root, data);
        if (pee[0] == 'F')
            Find(root, data);
        if (pee[0] == 'D')
            root = Delete(root, data);
    }
    return 0;
}
