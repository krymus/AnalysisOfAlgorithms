#include <iostream>
#include <chrono>
#include <time.h>
using namespace std;
using namespace chrono;

/*
Structure node implements element in list
*/
template<typename T>
struct node
{
    T value;
    node* next;
    node* previous;
};

template<typename T>
class list
{
public:     
    
    node<T>* first;
    int size;

    list()
    {
        first = NULL;
        size = 0;
    }

    void add(T value) // Adding method
    {
        node<T>* newNode = new node<T>;
        newNode -> value = value;

        if(first == NULL) first = newNode;
        else
        {
            node<T>* temp = first;

            for(int i=1; i<size; i++)
            {
                temp = temp -> next;
            }

            temp -> next = newNode;
            newNode -> next = first;
            first -> previous = temp;
        }

        size++;
    }

    void printElementOfIndex(int index) //Method prints element of a given index
    {
        if(index<0 || index>size-1)
        {
            cout<<"Wrong index"<<endl;
            return;
        }

        node<T>* temp = first;

        for(int i=0; i<index; i++)
        {
           temp = temp -> next;
        }

        cout<<temp -> value<<endl;

    }

    void printlist()
    {
        node<T>* temp = first;
        for(int i=0; i<size; i++)
        {
            cout<<temp -> value<<endl;
            temp = temp -> next;
        }
    }

    void walk(int steps) // method prints elements one by one 
    {
        node<T>* temp = first;
        for(int i=0; i<steps; i++)
        {
            cout<<temp->value<<endl;
            temp = temp ->next;
        }
    }
};

template<typename T> // Method merges to lists
void merge(list<T>& l1, list<T>& l2)
{
    if(l1.size == 0)
    {
        l1.first = l2.first;
        l1.size = l2.size;
        return;
    }

    if(l2.size == 0)
    {
        l2.first = l1.first;
        l2.size = l1.size;
        return;
    }


    node<T>* temp = l1.first;
    for(int i=1; i<l1.size; i++)
    {
        temp = temp -> next;
    }

    temp -> next = l2.first;
    l2.first -> previous = temp;

    temp = l2.first;
    for(int i=1; i<l2.size; i++)
    {
        temp = temp -> next;
    }

    temp->next = l1.first;
    l1.first->previous = temp;
    l1.size = l1.size + l2.size;
    l2.size = l1.size;
}

int main()
{
    list<int> l1;
    l1.add(3);
    l1.add(2);

    list<int> l2;
    l2.add(4);
    l2.add(5);

    merge(l1,l2);

    l1.printlist();
    
    
    
    return 0;
}