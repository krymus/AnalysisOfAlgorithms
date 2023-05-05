#include <iostream>
using namespace std;

int compares = 0;
int swaps = 0;

void displayTab(int *tab, int begin, int end)
{
    for(int i=begin; i<=end; i++) cout<<tab[i]<<" ";
    cout<<endl;
}

bool compare(int a, int b)
{
    compares++;
    if(a<=b) return true;
    else return false;
}

void merge(int *tab, int begin, int mid,
           int end, bool display)
{
    int tab1size = mid - begin + 1;
    int tab2size = end - mid;
 

    int *tab1= new int[tab1size];
    int *tab2= new int[tab2size];
 
    for (int i = 0; i < tab1size; i++)
        tab1[i] = tab[begin + i];
    for (int i = 0; i < tab2size; i++)
        tab2[i] = tab[mid + 1 + i];
 
    int indextab1 = 0;
    int indextab2 = 0;
    int indextab = begin;

    if(display)
    {
       for(int i=begin; i<=end; i++)
       {
            cout<<tab[i]<<" ";
            if(i==mid) cout<<"  ";
       }
       cout<<endl;
    } 
 
    while (indextab1 < tab1size
           && indextab2 < tab2size) {
        if (compare(tab1[indextab1], tab2[indextab2])) 
        {
            tab[indextab] = tab1[indextab1];
            indextab1++;
        }
        else {
            tab[indextab] = tab2[indextab2];
            indextab2++;
        }
        indextab++;
    }
    
    while (indextab1 < tab1size) {
        tab[indextab] = tab1[indextab1];
        indextab1++;
        indextab++;
    }
   
    while (indextab2 < tab2size) {
        tab[indextab] = tab2[indextab2];
        indextab2++;
        indextab++;
    }

    delete[] tab1;
    delete[] tab2;
}

void mergeSort(int *tab, int begin, int end, bool display)
{
    if (begin >= end)
        return; // Returns recursively

    if(display) displayTab(tab, begin, end);
 
    int mid = begin + (end - begin) / 2;
    mergeSort(tab, begin, mid, display);
    mergeSort(tab, mid + 1, end, display);

    merge(tab, begin, mid, end, display);
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

    mergeSort(tab, 0, n-1, false);

    /*
    if(n<40)
    {
        mergeSort(tab, 0, n-1, true);
        displayTab(tab,0,n-1);
    } 
    else mergeSort(tab, 0, n-1, false);

    if(isSorted(tab, n)) cout<<"Array is sorted"<<endl;
    else cout<<"Array is not sorted"<<endl;
    cout<<"Number of compares: "<<compares<<endl;
    cout<<"Number of swaps: "<<n<<endl;*/

    double x = compares/(double)n;
    double y = swaps/(double)n;
    cout<<compares<<" "<<swaps<<" "<<x<<" "<<y<<endl;

    delete [] tab;
    return 0;
}