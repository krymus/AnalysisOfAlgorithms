#include <iostream>
#include <algorithm>
using namespace std;

int compares = 0;
int swaps = 0;
int n;

bool compare(int a, int b)
{
    compares++;
    if(a<=b) return true;
    else return false;
}

void displayTab(int *tab, int begin, int end)
{
    for(int i=begin; i<=end; i++) cout<<tab[i]<<" ";
    cout<<endl;
}


int partition(int* tab, int begin, int end, int p)
{
    if(end!=p)
    {
        swap(tab[p], tab[end]); // move pivot to the end
        swaps++;
    }

    int i = begin - 1;
    for (int j = begin; j < end; j++)
    {
        if (compare(tab[j], tab[end]))
        {
            i++;
            swap(tab[i], tab[j]);
            swaps++;
        }
    }
    swap(tab[i+1], tab[end]); // move pivot to its final position
    swaps++;
    return i+1;
}

void quickSort(int *tab, int begin, int end) {
    if (begin < end) {
        int p = partition(tab, begin, end, end);
        quickSort(tab, begin, p - 1);
        quickSort(tab, p + 1, end);
    }
}

int SELECT(int *tab, int begin, int end, int k, bool display) {
    if (begin == end) {
        return tab[begin];
    }
    int pivotIndex = begin;
    while (true) {
        int pivotNewIndex = partition(tab, begin, end, pivotIndex);
        int pivotDist = pivotNewIndex - begin + 1;
        if (k == pivotDist) {
            return tab[pivotNewIndex];
        } else if (k < pivotDist) {
            end = pivotNewIndex - 1;
        } else {
            k = k - pivotDist;
            begin = pivotNewIndex + 1;
        }
        // Choose pivot using median of medians
        if (end - begin + 1 > 9) {
            int numGroups = (end - begin + 1) / 9;
            int medians[numGroups];
            for (int i = 0; i < numGroups; i++) {
                sort(tab + begin + i * 9, tab + begin + i * 9 + 9);
                medians[i] = tab[begin + i * 9 + 4];
            }
            int medianOfMedians = SELECT(medians, 0, numGroups - 1, numGroups / 2, false);
            for (int i = begin; i <= end; i++) {
                if (tab[i] == medianOfMedians) {
                    pivotIndex = i;
                    break;
                }
            }
        } else {
            pivotIndex = begin + (end - begin) / 2;
        }
        if(display)
        {
            displayTab(tab, begin, end);
        }
    }
} 


int main(int argc, char *argv[])
{
    n = argc-2;
    int *tab = new int[n];
    int k = stoi(argv[1]);

    for(int i = 0; i<n; i++)
    {
        try{
            int x = stoi(argv[i+2]);
            tab[i] = x;
        }
        catch(exception e)
        {
            cerr<<"Problem with storing tabay"<<endl;
            return 0;
        }
    }
  //  cout<<"Start state: ";
  //  displayTab(tab, 0, n-1);

    int k_thNumber;
    if(n<40)
    {
        k_thNumber = SELECT(tab, 0, n-1, k, true);
    } else k_thNumber = SELECT(tab, 0, n-1, k, false);

    //cout<<"Number on "<<k<<"-th position: "<<k_thNumber<<endl;
/*
    cout<<"End state: ";
    displayTab(tab, 0, n-1);

    cout<<"Number on "<<k<<"-th position: "<<k_thNumber<<endl;

    sort(tab, tab+n);
    cout<<"Sorted tabay: ";
    displayTab(tab, 0, n-1);
    
    
    

    double x = compares/(double)n;
    double y = swaps/(double)n;
    cout<<compares<<" "<<swaps<<" "<<x<<" "<<y<<endl;*/
    
    cout<<compares<<" "<<swaps<<endl;
    delete [] tab;
    return 0;
}