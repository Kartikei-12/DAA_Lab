//Author: Kartikei Mittal
//ID: 2017KUCP1032
#include<iostream>
    using namespace std;
//Implementation of cycle detection algorithm with
//maximum degree defined using adjancey array.
#define degree 5

class Node
{
public:
    char data;
    Node* Links[degree];
    bool visited;
    Node(char a)
    {
        data=a;
        for(int i=0; i<degree; ++i)
            Links[i] = NULL;
        visited = false;
    }
};

void is_cycle_present(Node* root, bool &isCycle)
{
    if(!isCycle)
    {
        root->visited=true;
        cout<<"Data: "<<root->data<<endl;
        for(int i=0; i<degree && root->Links[i]!=NULL; ++i)
            if(!(root->Links[i]->visited))
            {
                int a=i;
                i = degree;
                is_cycle_present(root->Links[a], isCycle);
            }
            else
            {
                /*
                bool isParaent = false;
                Node* curr_node = root->Links[i];
                for(int j=0; j<degree && curr_node->Links[j]!=NULL; ++j)
                    if(curr_node->Links[j] == root)
                    {
                        isParaent = true;
                        break ;
                    }
                if(!isParaent)
                {
                    isCycle = true;
                    cout<<"Cycle detected at: \n"<<curr_node->data;
                    return ;
                }
                */
                isCycle=true;
                cout<<"Cycle Detected at: "<<root->Links[i]->data;
            }
    }          
}

int main()
{
    Node* a1 = new Node('A');
    Node* a2 = new Node('B');
    Node* a3 = new Node('C');
    Node* a4 = new Node('D');
    Node* a5 = new Node('E');
    Node* a6 = new Node('F');
    
    a1->Links[0] = a3;
    
    a2->Links[0] = a3;
    a2->Links[1] = a4;
    
    a3->Links[0] = a4;
    a3->Links[1] = a5;

    a4->Links[0] = a6;
    
    a5->Links[0] = a6;
    
    a6->Links[0] = a3;


    //Add for undirected graph
    /*
    a3->Links[2] = a4;
    a3->Links[3] = a5;
    a3->Links[4] = a6;

    a4->Links[1] = a2;
    a4->Links[2] = a3;

    a5->Links[1] = a3;
    
    a6->Links[1] = a4;
    a6->Links[2] = a5;
        
    */
    bool a = false;
    is_cycle_present(a1, a);

    return 0;
}