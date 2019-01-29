#include<iostream>
    using namespace std;

#define degree 5

template <typename T>
class Node
{
public:
    T data;
    Node* Links[degree];
    bool visited;
    Node(T a)
    {
        data=a;
        for(int i=0; i<degree; ++i)
            Links[i] = NULL;
        visited = false;
    }
};


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

    a3->Links[0] = a1;
    a3->Links[1] = a5;
    a3->Links[2] = a4;
    a3->Links[3] = a2;
    
    a3->Links[0] = a1;
    a3->Links[1] = a5;
    a3->Links[2] = a4;
    a3->Links[3] = a2;

    a3->Links[0] = a1;
    a3->Links[1] = a5;
    a3->Links[2] = a4;
    a3->Links[3] = a2;

    a3->Links[0] = a1;
    a3->Links[1] = a5;
    a3->Links[2] = a4;
    a3->Links[3] = a2;

    return 0;
}