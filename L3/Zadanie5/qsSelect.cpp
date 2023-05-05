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


int partition(int tab[], int begin, int end, int p)
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

void QS(int tab[], int begin, int end);

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

void sort(int tab[], int begin, int end)
{
    if(begin>=end) return;
    int pivot = partition(tab,begin, end);
    QS(tab, begin, pivot-1);
    QS(tab, pivot + 1, end);
}

int SELECT(int tab[], int begin, int end, int k) {
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
        if (end - begin + 1 > 5) {
            int numGroups = (end - begin + 1) / 5;
            int medians[numGroups];
            for (int i = 0; i < numGroups; i++) {
                sort(tab, begin + i * 5, begin + i * 5 + 4);
                medians[i] = tab[begin + i * 5 + 2];
            }
            int medianOfMedians = SELECT(medians, 0, numGroups - 1, numGroups / 2);
            for (int i = begin; i <= end; i++) {
                if (tab[i] == medianOfMedians) {
                    pivotIndex = i;
                    break;
                }
            }
        } else {
            pivotIndex = begin + (end - begin) / 2;
        }
    }
} 

void QS(int tab[], int begin, int end)
{
    if(begin>=end) return;
    int element = SELECT(tab, begin, end, (end-begin+1)/2);
    int index;
    for(int i = begin; i<=end; i++) if(tab[i] == element) index = i;

    int pivot = partition(tab,begin, end, index);
    QS(tab, begin, pivot-1);
    QS(tab, pivot + 1, end);
}




int main(int argc, char *argv[])
{
    ofstream file("qsSELECT.txt");

    
    for(int n = 100; n < 10001; n+=100)
    {
        for(int m = 0; m < 30; m++)
        {
            int *tab = new int[n];
            for(int i=0; i<n; i++) tab[i] = random(1, 2*n);

            auto start = high_resolution_clock::now();
            QS(tab, 0, n-1);
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