//Author: Kartikei Mittal
//ID: 2017KUCP1032
//DFS Implementation on simple tree
#include<iostream>
using namespace std;
class Tree
{
public:
    char data;
    Tree *left, *right;
    Tree(int d=0)
    {
        data=d;
        left=right=NULL;
    }
};
/*
void insert(Tree *root, char value)
{
    //Assuming root is non empty
    if(root->data<=value)
        if(root->left==NULL)
            root->left = new Tree(value);
        else
            insert(root->left, value);
    else
        if(root->right==NULL)
            root->right = new Tree(value);
        else
            insert(root->right, value);
}
*/
void DFS(Tree *root)
{
    cout<<"Data: "<<root->data<<endl;
    if(root->left != NULL)
        DFS(root->left);
    if(root->right != NULL)
        DFS(root->right);
}

int main(int argc, char const *argv[])
{
    Tree *root = NULL;
    root = new Tree('A');
    root->left = new Tree('B');
    root->right = new Tree('C');
    root->left->left = new Tree('D');
    root->left->right = new Tree('E');
    root->right->left = new Tree('F');
    root->right->right = new Tree('G');
    DFS(root);
    return 0;
}
