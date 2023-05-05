#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <algorithm>
using namespace std;
using namespace chrono;

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

int partition(int *tab, int begin, int end) {
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
    
    return (i + 1);
}
 
void quickSort(int *tab, int begin, int end) {
    if (begin < end) {
        int p = partition(tab, begin, end);
        quickSort(tab, begin, p - 1);
        quickSort(tab, p + 1, end);
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
    ofstream file("qs.txt");

    
    for(int n = 100; n < 10001; n+=100)
    {
        for(int m = 0; m < 30; m++)
        {
            int *tab = new int[n];
            for(int i=0; i<n; i++) tab[i] = random(1, 2*n);

            auto start = high_resolution_clock::now();
            quickSort(tab, 0, n-1);
            auto end = high_resolution_clock::now();

            auto duration = duration_cast<nanoseconds>(end - start);
            double timeInSeconds = duration.count() / 1e9;
            file << compares << " " << timeInSeconds << " " << swaps << endl;
            delete [] tab;
            compares = 0;
            swaps = 0;
        }
    }

    
    file.close();
    return 0;
}