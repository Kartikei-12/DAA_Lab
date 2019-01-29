#include<iostream>
    using namespace std;
//Implementation of BFS and DFS with
//maximum degree defined using adjancey array.
#define degree 5

template <typename T>
class Node
{
public:
    T data;
    Node<T>* Links[degree];
    bool visited;
    Node(T a)
    {
        data=a;
        for(int i=0; i<degree; ++i)
            Links[i] = NULL;
        visited = false;
    }
};


void DFS(Node<auto>* root)
{
    root->visited=true;
    cout<<"Data: "<<root->data<<endl;
    for(int i=0; i<degree && root->Links[i]!=NULL; ++i)
        if(!(root->Links[i]->visited))
            DFS(root->Links[i]);
}
int main()
{
    Node<char>* a1 = new Node<char>('A');
    Node<char>* a2 = new Node<char>('B');
    Node<char>* a3 = new Node<char>('C');
    Node<char>* a4 = new Node<char>('D');
    Node<char>* a5 = new Node<char>('E');
    Node<char>* a6 = new Node<char>('F');
    
    a1->Links[0] = a3;
    a1->Links[1] = a2;

    a2->Links[0] = a1;
    a2->Links[1] = a3;
    a2->Links[2] = a5;
    a2->Links[3] = a4;
    
    a3->Links[0] = a1;
    a3->Links[1] = a5;
    a3->Links[2] = a4;
    a3->Links[3] = a2;
    
    a4->Links[0] = a2;
    a4->Links[1] = a3;
    a4->Links[2] = a5;
    a4->Links[3] = a6;

    a5->Links[0] = a6;
    a5->Links[1] = a4;
    a5->Links[2] = a2;
    a5->Links[3] = a3;

    a6->Links[0] = a4;
    a6->Links[1] = a5;

    DFS(a1);

    return 0;
}