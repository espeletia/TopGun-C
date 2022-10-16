#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node* FindMin(struct Node *root){
    while(root->left != NULL) root = root->left;
    return root;
}

struct Node* Delete(struct Node *root, int data){
    if(root == NULL) return root;
    else if(data < root->data) root->left =  Delete(root->left, data);
    else if(data > root->data) root->right = Delete(root->right, data);
    else{
        //Caso 1: No tiene hijos
        if(root->left == NULL && root->right == NULL){
            free(root);
            root = NULL;
        }
        //Caso 2: Tiene 1 hijo
        else if(root->left == NULL){
            struct Node *temp = root;
            root = root->right;
            free(temp);
        }
        else if(root->right == NULL){
            struct Node *temp = root;
            root = root->left;
            free(temp);
        }
        //Caso 3: Tiene 2 Hijos
        else{
            struct Node *temp = FindMin(root->right);
            root->data = temp->data;
            root->right = Delete(root->right, temp->data);
        }
    }
    return root;
}

struct Node* Insert(struct Node *root, char data) {
    if(root == NULL) {
        struct Node *temp = malloc(sizeof(struct Node));
        root = temp;
        root->data = data;
        root->left = root->right = NULL;
    }
    else if(data <= root->data){
        root->left = Insert(root->left, data);
    }
    else {
        root->right = Insert(root->right, data);
    }
    return root;
}

void Inorder(struct Node *root){
    if(root == NULL) return;
    Inorder(root->left);
    printf("%d, ", root->data);
    Inorder(root->right);
}

int main(){
    struct Node* root = NULL;
    root = Insert(root,5);
    root = Insert(root,10);
    root = Insert(root,3);
    root = Insert(root,4);
    root = Insert(root,1);
    root = Insert(root,11);
    root = Delete(root,3);
    printf("Inorder: ");
    Inorder(root);
    printf("\n");
}