#include <iostream>
using namespace std;

int compares = 0;
int swaps = 0;
int n;

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

int partition(int *tab, int begin, int end, bool display) {
    int p = tab[end];
    int i = (begin - 1);
  
    for (int j = begin; j <= end - 1; j++) {
        if (compare(tab[j], p)) {
            i++;
            swap(tab[i], tab[j]);
            swaps++;
        }
    }
    swap(tab[i + 1], tab[end]);
    swaps++;

    if(display)
    {
        cout<<"Placing "<<p<<" : ";
        displayTab(tab, 0 ,n-1);
    }
    
    return (i + 1);
}
 
void quickSort(int *tab, int begin, int end, bool display) {
    if (begin < end) {
        int p = partition(tab, begin, end, display);
        quickSort(tab, begin, p - 1, display);
        quickSort(tab, p + 1, end, display);
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
    n = argc-1;
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

    quickSort(tab, 0, n-1, false);

/*
    cout<<"Start state: ";
    displayTab(tab, 0, n-1);
    if(n<40)
    {
        quickSort(tab, 0, n-1, true);
    } 
    else quickSort(tab, 0, n-1, false);

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