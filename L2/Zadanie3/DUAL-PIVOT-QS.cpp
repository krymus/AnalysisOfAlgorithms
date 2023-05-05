#include <iostream>
using namespace std;

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

void dualPivotSort(int* tab, int begin, int end, bool display)
{
	if (begin < end) {
		int lp, rp;
		rp = partition(tab, begin, end, &lp);
        if(display)
        {
            for(int i=0; i<lp; i++)
            {
                cout<<tab[i]<<" ";
            }
            cout<<"   <"<<tab[lp]<<">   ";
            for(int i=lp+1; i<rp; i++)
            {
                cout<<tab[i]<<" ";
            }
            cout<<"   <"<<tab[rp]<<">   ";
            for(int i=rp+1; i<n; i++)
            {
                cout<<tab[i]<<" ";
            }
            cout<<endl;
        }
		dualPivotSort(tab, begin, lp - 1, display);
		dualPivotSort(tab, lp + 1, rp - 1, display);
		dualPivotSort(tab, rp + 1, end, display);
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

    dualPivotSort(tab, 0, n-1, false);

/*
    cout<<"Start state: ";
    displayTab(tab, 0, n-1);
    if(n<40)
    {
        dualPivotSort(tab, 0, n-1, true);
    } 
    else dualPivotSort(tab, 0, n-1, false);

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
