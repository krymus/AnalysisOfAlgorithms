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
    node<T>* first; //first element to dequeue (= oldest enqueued element)
    node<T>* last;  //last element to dequeue (= recently enqueued element)

public:

    queue() // constructor
    {
        first = NULL;
        last = NULL;
    }

    void enqueue(T value) // enqueuing method
    {
        node<T>* newNode = new node<T>;
        newNode -> value = value;
        newNode -> next = NULL;

       if(first == NULL)
       {
         first = newNode;
         last = newNode;
        }
        else
        {
           last -> next = newNode; 
           last = last -> next;
        } 
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
        delete temp;
    }


    void deleteQueue() //deleting method release all alocated memory 
    {
        node<T>* i = first;
        while(i != NULL)
        {
            node<T>* temp = i;
            i = i->next;
            delete temp;
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

    for(int i=0; i<100; i++)
    {
        q.enqueue(i);
    }

    for(int i=0; i<101; i++)
    {
        q.dequeue();
    }
    
    q.deleteQueue();
    return 0;
}