#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
using namespace std;
using namespace chrono;

int n;
int swaps = 0;
int compares = 0;

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

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
    swaps++;
}

random_device rd;
mt19937 gen(rd());

int random(int low, int high)
{
    uniform_int_distribution<> dist(low, high);
    return dist(gen);
}


int partition(int* tab, int begin, int end, int* lp)
{
	if (smaller(tab[end], tab[begin]))
		swap(&tab[begin], &tab[end]);
	int j = begin + 1;
	int g = end - 1;
    int k = begin + 1;
    int p = tab[begin];
    int q = tab[end];

	while (k<=g) {

        if(j-begin<q-end)
        {
            if (smallerOrEqual(q, tab[k])) 
            {
			    while (smaller(q, tab[g]) && (k<g)) g--;
			    swap(&tab[k], &tab[g]);
			    g--;
			    if (smaller(tab[k],p)) 
                {
				    swap(&tab[k], &tab[j]);
				    j++;
			    }
		    }

		    else if (smallerOrEqual(tab[k],p)) 
            {
			swap(&tab[k], &tab[j]);
			j++;
		    }
        }
        else
        {
            if (smaller(tab[k], p)) 
            {
			    swap(&tab[k], &tab[j]);
			    j++;
		    }

		    else if (smallerOrEqual(q, tab[k])) 
            {
			    while (smaller(q, tab[g]) && (k<g)) g--;
			    swap(&tab[k], &tab[g]);
			    g--;
			    if (tab[k]< p) 
                {
				    swap(&tab[k], &tab[j]);
				    j++;
			    }
    		}
        }

		k++;
	}
	j--;
	g++;

	swap(&tab[begin], &tab[j]);
	swap(&tab[end], &tab[g]);

	*lp = j; 

	return g;
}

void dualPivotSort(int* tab, int begin, int end)
{
	if (begin < end) {
		int lp, rp;
		rp = partition(tab, begin, end, &lp);
        
		dualPivotSort(tab, begin, lp - 1);
		dualPivotSort(tab, lp + 1, rp - 1);
		dualPivotSort(tab, rp + 1, end);
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

void displayTab(int *tab, int begin, int end)
{
    for(int i=begin; i<=end; i++) cout<<tab[i]<<" ";
    cout<<endl;
}

int main(int argc, char *argv[])
{
    ofstream file("dqs.txt");

    
    for(int n = 100; n < 10001; n+=100)
    {
        for(int m = 0; m < 30; m++)
        {
            int *tab = new int[n];
            for(int i=0; i<n; i++) tab[i] = random(1, 2*n);

            auto start = high_resolution_clock::now();
            dualPivotSort(tab, 0, n-1);
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
