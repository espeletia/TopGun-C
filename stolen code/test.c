#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct Osoba
{
    int rok;
    int mesic;
    int den;

    char *jmeno;

} Osoba;

struct node
{
    Osoba key;
    struct node *left, *right;
};
struct node *minValueNode(struct node *node)
{
    struct node *current = node;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}
void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d %d %d %s\n", root->key.rok, root->key.mesic, root->key.den, root->key.jmeno);
        inorder(root->right);
    }
}
struct node *newNode(Osoba itemy)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = itemy;
    temp->left = temp->right = NULL;
    return temp;
}
struct node *deleteNode(struct node *root, Osoba Informace)
{

    if (root == NULL)
    {

        printf("Not found\n");
        return root;
    }

    int kontrola = strcmp(root->key.jmeno, Informace.jmeno);
    if (Informace.rok < root->key.rok)
        root->left = deleteNode(root->left, Informace);

    else if (Informace.rok > root->key.rok)
        root->right = deleteNode(root->right, Informace);

    else if (kontrola == 0 && root->key.rok == Informace.rok && root->key.mesic == Informace.mesic && root->key.den == Informace.den)
    {

        printf("Deleted\n");
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

        struct node *temp = minValueNode(root->right);

        root->key = temp->key;

        root->right = deleteNode(root->right, temp->key);
    }
    else
    {
        if (root->key.mesic > Informace.mesic)
        {

            root->left = deleteNode(root->left, Informace);
        }
        else if (root->key.mesic < Informace.mesic)
        {
            root->right = deleteNode(root->right, Informace);
        }

        if (root->key.den > Informace.den)
        {
            root->left = deleteNode(root->left, Informace);
        }
        else if (root->key.den < Informace.den)
        {
            root->right = deleteNode(root->right, Informace);
        }

        char str[100][100], s[100];
        strcpy(str[0], root->key.jmeno);
        strcpy(str[1], Informace.jmeno);

        for (int i = 0; i < 2; i++)
        {
            for (int j = i + 1; j < 2; j++)
            {
                if (strcmp(str[i], str[j]) > 0)
                {
                    strcpy(s, str[i]);
                    strcpy(str[i], str[j]);
                    strcpy(str[j], s);
                }
            }
        }

        if (str[0] == Informace.jmeno)
        {
            root->left = deleteNode(root->left, Informace);
        }
        else if (str[0] == root->key.jmeno)
        {
            root->right = deleteNode(root->right, Informace);
        }
    }
    return root;
}

struct node *ifNodeExists(struct node *node, Osoba informace)
{
    if (node == NULL)
    {
        printf("Not found\n");
        return node;
    }

    int kontrola = strcmp(node->key.jmeno, informace.jmeno);
    if (kontrola == 0 && informace.rok == node->key.rok && informace.den == node->key.den && informace.mesic == node->key.mesic)
    {
        printf("Found\n");
        return node;
    }

    if (node->key.rok > informace.rok)
    {
        node->left = ifNodeExists(node->left, informace);
    }
    else if (node->key.rok < informace.rok)
    {
        node->right = ifNodeExists(node->right, informace);
    }

    if (node->key.rok == informace.rok)
    {

        if (node->key.mesic > informace.mesic)
        {

            node->left = ifNodeExists(node->left, informace);
        }
        else if (node->key.mesic < informace.mesic)
        {
            node->right = ifNodeExists(node->right, informace);
        }

        if (node->key.den > informace.den)
        {
            node->left = ifNodeExists(node->left, informace);
        }
        else if (node->key.den < informace.den)
        {
            node->right = ifNodeExists(node->right, informace);
        }

        char str[100][100], s[100];
        strcpy(str[0], node->key.jmeno);
        strcpy(str[1], informace.jmeno);

        for (int i = 0; i < 2; i++)
        {
            for (int j = i + 1; j < 2; j++)
            {
                if (strcmp(str[i], str[j]) > 0)
                {
                    strcpy(s, str[i]);
                    strcpy(str[i], str[j]);
                    strcpy(str[j], s);
                }
            }
        }

        if (str[0] == informace.jmeno)
        {
            node->left = ifNodeExists(node->left, informace);
        }
        else if (str[0] == node->key.jmeno)
        {
            node->right = ifNodeExists(node->right, informace);
        }
    }

    return node;
}

struct node *insert(struct node *node, Osoba informace)
{

    if (node == NULL)
    {
        printf("Stored\n");
        return newNode(informace);
    }

    int kontrola1 = strcmp(node->key.jmeno, informace.jmeno);
    if (kontrola1 == 0 && node->key.rok == informace.rok && informace.mesic == node->key.mesic && node->key.den == informace.den)
    {
        printf("Already stored\n");

        return node;
    }

    if (node->key.rok > informace.rok)
    {
        node->left = insert(node->left, informace);
    }
    else if (node->key.rok < informace.rok)
    {
        node->right = insert(node->right, informace);
    }

    if (node->key.rok == informace.rok)
    {

        if (node->key.mesic > informace.mesic)
        {

            node->left = insert(node->left, informace);
        }
        else if (node->key.mesic < informace.mesic)
        {
            node->right = insert(node->right, informace);
        }

        if (node->key.den > informace.den)
        {
            node->left = insert(node->left, informace);
        }
        else if (node->key.den < informace.den)
        {
            node->right = insert(node->right, informace);
        }
        char str[100][100], s[100];
        strcpy(str[0], node->key.jmeno);
        strcpy(str[1], informace.jmeno);

        for (int i = 0; i < 2; i++)
        {
            for (int j = i + 1; j < 2; j++)
            {
                if (strcmp(str[i], str[j]) > 0)
                {
                    strcpy(s, str[i]);
                    strcpy(str[i], str[j]);
                    strcpy(str[j], s);
                }
            }
        }

        if (str[0] == informace.jmeno)
        {
            node->left = insert(node->left, informace);
        }
        else if (str[0] == node->key.jmeno)
        {
            node->right = insert(node->right, informace);
        }
    }

    return node;
}

char *scanc(char x, char *y)
{
    int i = 0;

    while (1)
    {
        scanf("%c", &x);
        if (x == '\n' || x == EOF)
            return y;
        y = realloc(y, i + 1);
        y[i++] = x;
        y[i] = '\0';
    }
}

int main()
{
    char prvnipismeno;
    Osoba informace;
    struct node *root = NULL;

    while (scanf("%c: ", &prvnipismeno) != EOF)
    {
        scanf("%d %d %d ", &informace.rok, &informace.mesic, &informace.den);

        informace.jmeno = (char *)malloc(1 * sizeof(char));

        informace.jmeno = scanc(' ', malloc(1));

        /*  scanf("%c", &pomocnachar);
          while(pomocnachar != '\n' && pomocnachar != EOF ){
           informace.jmeno = realloc(informace.jmeno, pomocna+1 * sizeof(char));
           informace.jmeno[pomocna]  = pomocnachar;
              ++pomocna;
              scanf("%c", &pomocnachar);

          }
          printf("%s", informace.jmeno); */

        if (prvnipismeno == 'S')
        {

            root = insert(root, informace);
        }
        if (prvnipismeno == 'D')
        {
            root = deleteNode(root, informace);
        }
        if (prvnipismeno == 'F')
        {
            ifNodeExists(root, informace);
        }
    }

    return 0;
}