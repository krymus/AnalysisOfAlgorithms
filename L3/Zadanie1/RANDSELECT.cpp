#include <iostream>
#include <algorithm>
#include <random>
using namespace std;

int compares = 0;
int swaps = 0;
int n;

random_device rd;
mt19937 gen(rd());

int random(int low, int high)
{
    uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

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

int partition(int *tab, int begin, int end, bool display) {
    int tos = random(begin, end);
    swap(tab[end], tab[tos]);
    swaps++;
    int p = tab[end];
    int i = -1;
  
    for (int j = begin; j <= end - 1; j++) {
        if (compare(tab[j], p)) {
            i++;
            swap(tab[i+begin], tab[j]);
            swaps++;
        }
    }
    swap(tab[i + 1 + begin], tab[end]);
    swaps++;
    
    return (i + 1);
}


int RANDSELECT(int *tab, int begin, int end, int k, bool display)
{
    if(begin==end) return tab[begin];
    int p = partition(tab, begin, end, display);
    if(display)
    {
        cout<<"----"<<endl;
        displayTab(tab, begin ,end);
        cout<<"begin: "<<begin<<" end: "<<end<<" k: "<<k<<endl;
        cout<<" p: "<<p<<endl;
    } 
    if(p+1==k) return tab[begin+p];
    else if (p+1<k) return RANDSELECT(tab, begin+p+1, end, k-p-1, display);
    else return RANDSELECT(tab, begin, begin+p-1, k, display);
    return -1;
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
            cerr<<"Problem with storing array"<<endl;
            return 0;
        }
    }
  //  cout<<"Start state: ";
  //  displayTab(tab, 0, n-1);

    int k_thNumber;
    if(n<40)
    {
        k_thNumber = RANDSELECT(tab, 0, n-1, k, true);
    } else k_thNumber = RANDSELECT(tab, 0, n-1, k, false);

    cout<<"Number on "<<k<<"-th position: "<<k_thNumber<<endl;
/*
    cout<<"End state: ";
    displayTab(tab, 0, n-1);

    cout<<"Number on "<<k<<"-th position: "<<k_thNumber<<endl;

    sort(tab, tab+n);
    cout<<"Sorted array: ";
    displayTab(tab, 0, n-1);
    
    
    

    double x = compares/(double)n;
    double y = swaps/(double)n;
    cout<<compares<<" "<<swaps<<" "<<x<<" "<<y<<endl;*/
    
    cout<<compares<<" "<<swaps<<endl;
    delete [] tab;
    return 0;
}