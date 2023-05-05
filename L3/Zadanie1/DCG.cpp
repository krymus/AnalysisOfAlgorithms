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

    for(int i=n; i>0; i--) cout<<i<<" ";

    cout<<endl;

    
    return 0;
}