#include <iostream>
#include <chrono>
#include <time.h>
using namespace std;
using namespace chrono;

/*
Structure node implements element in queue
*/
template<typename T>
struct node
{
    T value;
    node* next;
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

/**
 * Adding method
*/
    void add(T value)
    {
        node<T>* newNode = new node<T>;
        newNode -> value = value;
        newNode -> next = NULL;

        if(first == NULL) first = newNode;
        else
        {
            node<T>* temp = first;

            while(temp -> next != NULL)
            {
                temp = temp -> next;
            }

            temp -> next = newNode;
        }

        size++;
    }

/**
 * Method finding element of given index
*/
    void printElementOfIndex(int index)
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
        while(temp != NULL)
        {
            cout<<temp -> value<<endl;
            temp = temp -> next;
        }
    }

    void deletelist()
    {
        if(first == NULL) return;

        node<T>* temp = first;

        while(temp -> next != NULL)
        {
            temp = first -> next;
            delete first;
            first = temp;
        }

        delete first;
    }

};

/**
 * Method merges two lists 
*/
template<typename T>
void merge(list<T>& l1, list<T>& l2)
    {
       l1.size = l1.size + l2.size;

       if(l1.first == NULL)
       {
            l1.first = l2.first;
            return;
       } 
        node<T>* temp = l1.first;
       while(temp -> next != NULL)
       {
           temp = temp -> next;
       }

       temp -> next = l2.first;
}


int main()
{
    list<int> l1;
    int index = 2345; //index to search

    srand(time(NULL));

    for(int i=0; i<10000; i++) //Adding elements
    {
        l1.add(rand() % 10000);
    }

// Measuring time for given index
    int avgtime=0;
    for (int i = 0; i<50; i++)
    {
        auto start = high_resolution_clock::now();
        l1.printElementOfIndex(index);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop-start);
        cout<<" "<<duration.count()<<endl;
        avgtime = avgtime + duration.count();
    }
    avgtime = avgtime/50;

    cout<<"Average time to print "<<index<<"th element: "<<avgtime<<" microseconds"<<endl;

// Meeasuring time to random index
    avgtime=0;
    for (int i = 0; i<50; i++)
    {
        auto start = high_resolution_clock::now();
        l1.printElementOfIndex(rand()%10000);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop-start);
        cout<<" "<<duration.count()<<endl;
        avgtime = avgtime + duration.count();
    }
    avgtime = avgtime/50;

    cout<<"Average time to print random element: "<<avgtime<<" microseconds"<<endl;

    l1.deletelist();

    /*  Merging example
    list<int> l1;
    l1.add(3);
    l1.add(2);

    list<int> l2;
    l2.add(4);
    l2.add(5);

    merge(l1,l2);

    l1.printlist();
    */
    
    
    
    


    return 0;
}