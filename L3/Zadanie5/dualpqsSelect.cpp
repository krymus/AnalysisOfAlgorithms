#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
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

bool smaller(int a, int b)
{
    compares++;
    if(a<b) return true;
    else return false;
}

bool smallerOrEqual(int a, int b)
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

void QS(int tab[], int begin, int end)
{
    if(begin>=end) return;
    int pivot = partition(tab,begin, end);
    QS(tab, begin, pivot-1);
    QS(tab, pivot + 1, end);
}

int SELECT(int tab[], int begin, int end, int k);

void partition(int tab[], int begin, int end, int leftpivot, int rightpivot, int &leftPivot, int &rightPivot)
{
    if(end - begin == 1)
    {
        if(smaller(tab[end], tab[begin]))
        {
            swap(tab[begin], tab[end]);
            swaps++;
        } 

        leftPivot = begin;
        rightPivot = end;
        return;
    }
    
    if(leftpivot == rightpivot)
    {
        swap(tab[leftpivot], tab[end]);
        swaps++;

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
        leftPivot = i+1;
        rightPivot = i+1;
        return;
    }

    if(tab[leftpivot]<= tab[rightpivot])
    {
        swap(tab[begin], tab[leftpivot]);
        swap(tab[end], tab[rightpivot]);
        swaps = swaps + 2;
    }
    else{
        swap(tab[begin], tab[rightpivot]);
        swap(tab[end], tab[leftpivot]);
        swaps = swaps + 2;
    }

    int j = begin + 1;
    int g = end - 1, k = begin + 1, p = tab[begin], q = tab[end];

    while (k <= g)
    {
        if (smaller(tab[k], p))
        {
            swap(tab[k], tab[j]);
            swaps++;
            j++;
        }
        else if (smallerOrEqual(q, tab[k]))
        {
            while (smaller(q, tab[g]) && k < g)
                g--;

            swap(tab[k], tab[g]);
            swaps++;
            g--;

            if (smaller(tab[k], p))
            {
                swap(tab[k], tab[j]);
                swaps++;
                j++;
            }
        }

        k++;
    }

    j--;
    g++;

    swap(tab[begin], tab[j]);
    swap(tab[end], tab[g]);
    swaps = swaps + 2;

    leftPivot = j;
    rightPivot = g;
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

int medianOfMedians(int* tab, int begin, int end)
{
    if (end - begin + 1 <= 5) {
        QS(tab, begin, end);
        return tab[begin + (end-begin) / 2];
    }

    int numGroups = (end - begin + 1) / 5;
    int medians[numGroups];
    for (int i = 0; i < numGroups; i++) {
        int groupBegin = begin + i * 5;
        int groupEnd = groupBegin + 4;
        if (groupEnd > end) {
            groupEnd = end;
        }
        medians[i] = medianOfMedians(tab, groupBegin, groupEnd);
    }
    int medianOfMediansElement = SELECT(medians, 0, numGroups - 1, numGroups / 2);
    return medianOfMediansElement;
}

int SELECT(int tab[], int begin, int end, int k) {
    if (begin == end) return tab[begin];
    
    int element = medianOfMedians(tab, begin, end);
    int index;
    for(int i=begin; i<=end; i++) if(tab[i] == element) index = i;
    int pivot = partition(tab, begin, end, index);
    
    if(pivot == k) return tab[pivot];
    if(k < pivot) return SELECT(tab, begin, pivot-1, k);
    else return SELECT(tab, pivot + 1, end, k);
} 

void DQS(int tab[], int begin, int end)
{
	if (begin >= end) return;
	int leftElementIndex;
    int rightElementIndex;
	int leftElement = SELECT(tab, begin, end, begin + (end-begin)/3);
    int rightElement = SELECT(tab, begin, end, begin + ((end-begin)*2)/3);
    
   for (int i = begin; i <= end; i++) {
    if (tab[i] == leftElement) {
        leftElementIndex = i;
    } 
    if (tab[i] == rightElement) {
        rightElementIndex= i;
    }
    }

    int leftpivot;
    int rightpivot;
    partition(tab, begin, end, leftElementIndex, rightElementIndex, leftpivot, rightpivot);
    
	DQS(tab, begin, leftpivot-1);
    DQS(tab, leftpivot+1, rightpivot-1);
    DQS(tab, rightpivot+1, end);
	
}




int main(int argc, char *argv[])
{
    ofstream file("dqsSELECT.txt");

    
    for(int n = 100; n < 10001; n+=100)
    {
        for(int m = 0; m < 30; m++)
        {
            int *tab = new int[n];
            for(int i=0; i<n; i++) tab[i] = random(1, 2*n);

            auto start = high_resolution_clock::now();
            DQS(tab, 0, n-1);
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