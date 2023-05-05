#include <iostream>
using namespace std;

/*
    Structure node implements single element in queue
*/
template<typename T>
struct node
{
    T value;
    node* next;
};

/*
    Class queue implements queue of elements
*/
template<typename T>
class queue
{
    node<T>* first; //first element to dequeue (= recently enqueued element)

public:

    queue() // constructor
    {
        first = NULL;
    }

    void enqueue(T value) // enqueuing method
    {
        node<T>* newNode = new node<T>;
        newNode -> value = value;
        newNode -> next = first;

        first = newNode;
        cout<<value<<endl;
    }

    void dequeue() // dequeuing method
    {
        if(first == NULL)
        {
            cout<<"You are trying to dequeue empty queue."<<endl;
            return;
        }


        node<T>* temp = first;
        first = first->next;
        cout<<temp->value<<endl;
    }


    void deleteQueue() //deleting method release all alocated memory 
    {
        if(first == NULL) return;
       
        node<T>* i = first;
        while(i != NULL)
        {
            i = i->next;
            delete first;
            first = i;
        }
    }

    void printcontent() //tries to print all elements if possible
    {
        try
        {
            if (first == NULL)
            {
                cout<<endl<<"EMPTY QUEUE"<<endl;
                return;
            } 
            else
           {
             node<T>* temp = first;
             while(temp != NULL)
              {
                cout<<endl<<temp->value<<" ";
                temp = temp->next;
              }
            }
        }
        catch(exception e)
        {
            cout<<"Elements are not printable :( "<<endl;
        }
        
    }
};



int main()
{
    queue<int> q;

    cout<<"ENQUEUING"<<endl;
    for(int i=0; i<100; i++)
    {
        q.enqueue(i);
    }

    cout<<"DEQUEUING"<<endl;
    for(int i=0; i<101; i++)
    {
        q.dequeue();
    }
    
    q.deleteQueue();
    return 0;
}