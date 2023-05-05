#include <iostream>
using namespace std;

int compares = 0;
int swaps = 0;

bool compare(int a, int b)
{
    compares++;
    if(a>b) return true;
    else return false;
}

void displayTab(int n, int *tab)
{
    for(int i=0; i<n; i++) cout<<tab[i]<<" ";
    cout<<endl;
}

void insertionSort(int n, int *tab, bool display)
{
   for(int i=1; i<n; i++)
   {
        int j=i;
        while(j>0 && compare(tab[j-1],tab[j]) == true)
        {
            swap(tab[j], tab[j-1]);
            swaps++;
            j = j-1;
        }

        if(display) displayTab(n, tab);
   } 
}

bool isSorted(int *tab, int n)
{
    for(int i=0; i<n-1; i++)
    {
        int j=i+1;
        if(tab[i]>tab[j]) return false;
    }
    return true;
}


int main(int argc, char *argv[])
{
    int n = argc-1;
    int *tab = new int[n];

    for(int i = 0; i<n; i++)
    {
        try{
            int x = stoi(argv[i+1]);
            tab[i] = x;
        }
        catch(exception e)
        {
            cerr<<"Problem with storing array"<<endl;
            return 0;
        }
    }

    insertionSort(n, tab, false);
    
/*
    if(n<40)
    {
        displayTab(n, tab);
        insertionSort(n, tab, true);
        displayTab(n, tab);
    } else insertionSort(n,tab,false);
    
    if(isSorted(tab, n)) cout<<"Array is sorted"<<endl;
    else cout<<"Array is not sorted"<<endl;
    cout<<"Number of compares: "<<compares<<endl;
    cout<<"Number of swaps: "<<swaps<<endl;*/

    double x = compares/(double)n;
    double y = swaps/(double)n;
    cout<<compares<<" "<<swaps<<" "<<x<<" "<<y<<endl;

    delete [] tab;
    return 0;
}