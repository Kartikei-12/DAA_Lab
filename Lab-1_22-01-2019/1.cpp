//Author: Kartikei Mittal
//ID: 2017KUCP1032
//Implementation of Binary Search Tree, (insertion and Pre-order traversal)
#include<iostream>
using namespace std;
class BST
{
public:
    int data;
    BST *left, *right;
    BST(int d=0)
    {
        data=d;
        left=right=NULL;
    }
};

void insert(BST *root, int value)
{
    //Assuming root is non empty
    if(root->data<=value)
        if(root->left==NULL)
            root->left = new BST(value);
        else
            insert(root->left, value);
    else
        if(root->right==NULL)
            root->right = new BST(value);
        else
            insert(root->right, value);
}

void display(BST *root)
{
    cout<<"Data: "<<root->data<<endl;
    if(root->left != NULL)
        display(root->left);
    if(root->right != NULL)
        display(root->right);
}

int main(int argc, char const *argv[])
{
    BST *root = NULL;
    root = new BST(1);
    for(int i=10; i>=2; --i)
        insert(root, i);
    display(root);
    return 0;
}
