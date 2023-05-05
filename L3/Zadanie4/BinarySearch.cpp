#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <random>
using namespace std;
using namespace std::chrono;

int compares = 0;
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
    if(a<b) return true;
    else return false;
}

void displayTab(int *tab, int begin, int end)
{
    for(int i=begin; i<=end; i++) cout<<tab[i]<<" ";
    cout<<endl;
}

bool BinarySearch(int tab[], int begin, int end, int target, bool display) {

    if (begin > end) {
        return false; 
    }

    if(display) displayTab(tab, begin, end);
    
    int mid = begin + (end - begin) / 2;
    
    if (tab[mid] == target) {
        return true; // Target found
    }
    else if (compare(tab[mid],target)) {
        return BinarySearch(tab, mid + 1, end, target, display); // Search in the right half
    }
    else {
        return BinarySearch(tab, begin, mid - 1, target, display); // Search in the left half
    }
}





int main(int argc, char *argv[])
{
    ofstream file("bsearchRandom.txt");

    
    for(int n = 1000; n < 1000001; n+=1000)
    {
        for(int m = 0; m < 30; m++)
        {
            int *tab = new int[n];
        for(int i=0; i<n; i++) tab[i] = i;

        auto start = high_resolution_clock::now();
        bool result = BinarySearch(tab, 0, n - 1, random(0, n-1), false);
        auto end = high_resolution_clock::now();

        auto duration = duration_cast<nanoseconds>(end - start);
        double timeInSeconds = duration.count() / 1e6;
        file << compares << " " << timeInSeconds << endl;
        delete [] tab;
        compares = 0;
        }
        
    }

    
    file.close();
    return 0;
}