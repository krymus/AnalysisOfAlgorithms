#include <iostream>
#include <random>
using namespace std;

random_device rd;
mt19937 gen(rd());
 
int random(int low, int high)
{
    uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

int main(int argc, char *argv[])
{
    int n;
    try {
        n = stoi(argv[1]);
    } catch(exception e)
    {
        cerr<<"Wrong input"<<endl;
        return 0;
    }

    mt19937_64 mt;

	for (int i=0; i<n; i++)
	{
        cout << random(1, 2*n-1) <<" "; 
	}

	cout<<endl;


    
    return 0;
}