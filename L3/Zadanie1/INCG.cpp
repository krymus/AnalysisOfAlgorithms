#include <iostream>
using namespace std;

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

    for(int i=1; i<=n; i++) cout<<i<<" ";

    cout<<endl;

    
    return 0;
}