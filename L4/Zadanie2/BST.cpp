#include<iostream>
#include<random>
#include<vector>
#include <fstream>

using namespace std;

int compares = 0;
int pointers = 0;

bool compare(int a, int b)
{
    compares++;
    if(a<b) return true;
    return false;
}
vector<int> tab;

random_device rd;
mt19937 gen(rd());

int random(int low, int high)
{
    uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

// global variables used in `print_BST`
char* left_trace; // needs to be allocaded with size
char* right_trace; // needs to be allocaded with size


class BST {
    
public:

    struct node {
        int data;
        node* left;
        node* right;
    };

    node* root;

    node* makeEmpty(node* t) {
        if(t == NULL)
            return NULL;
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        return NULL;
    }

    node* insert(int x, node* t)
    {
        pointers++;
        if(t == NULL)
        {
            t = new node;
            t->data = x;
            t->left = t->right = NULL;
            pointers++;
        }
        else if(compare(x, t->data))
            t->left = insert(x, t->left);
        else if(compare(t->data, x))
            t->right = insert(x, t->right);
        compares += 1;
        return t;
    }

    node* findMin(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    int height(node* x, int i)
    {
        if(x == NULL) return i;
        if(x->left == NULL && x->right == NULL) return i;
        int left = height(x->left, i+1);
        int right = height(x->right, i+1);

        if(x->left == NULL) return right; 
        if(x->right == NULL) return left;

        if(left>right) return left;
        else return right;
        

    }

    int height(){
        return height(root, 1);
    }

    node* findMax(node* t) {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    node* remove(int x, node* t) {
        node* temp;
        pointers++;
        if(t == NULL)
            return NULL;
        else if(compare(x, t->data))
            t->left = remove(x, t->left);
        else if(compare(t->data, x))
            t->right = remove(x, t->right);
        else if(t->left && t->right)
        {
            pointers += 3;
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
        else
        {
            temp = t;
            if(t->left == NULL) t = t->right;
             
            else if(t->right == NULL) t = t->left;
        
            pointers ++;
            
            delete temp;
        }

        return t;
    }

    void inorder(node* t) {
        if(t == NULL)
            return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }

    node* find(node* t, int x) {
        if(t == NULL)
            return NULL;
        else if(x < t->data)
            return find(t->left, x);
        else if(x > t->data)
            return find(t->right, x);
        else
            return t;
    }

    


    void print_BST( struct node * root, int depth,char prefix)
    {
        if( root == NULL ) return;
        if( root->left != NULL ){
            print_BST(root->left, depth+1, '/');
        }
        if(prefix == '/') left_trace[depth-1]='|';
        if(prefix == '\\') right_trace[depth-1]=' ';
        if( depth==0) cout<<"-";
        if( depth>0) cout<<" ";
        for(int i=0; i<depth-1; i++)
            if( left_trace[i]== '|' || right_trace[i]=='|' ) {
            cout<<"| ";
            } else {
            cout<<"  ";
            }
            
        if( depth>0 ) cout<<prefix<<"-";
    
        cout<<"["<<root->data<<"]\n";
        
        left_trace[depth]=' ';
        if( root->right != NULL ){
            right_trace[depth]='|';
            print_BST(root->right, depth+1, '\\');
        }
    }


    BST() {
        root = NULL;
    }

    ~BST() {
        root = makeEmpty(root);
    }

    void insert(int x) {
        root = insert(x, root);
    }

    void remove(int x) {
        root = remove(x, root);
    }

    void display() {
        inorder(root);
        cout << endl;
    }

    void search(int x) {
        root = find(root, x);
    }
};


vector<int> getINCElements(int n) {
    vector<int> permutation;
   
    for (int i = 1; i <= n; i++) {
        permutation.push_back(i);
    }
    return permutation;
}

int main()
{
    left_trace = (char*)malloc( 10*sizeof(char) );
    right_trace = (char*)malloc( 10*sizeof(char) );
    for(int i=0; i<10; i++)
    {
        left_trace[i]=' ';
        left_trace[i]=' ';
    }

    ofstream incheights("incheightsINC.txt");
    ofstream decheights("decheightsINC.txt");
    ofstream file("fileINC.txt");

    for(int n = 10000; n<100001; n+=10000)
    {
        cout<<n<<endl;
        for(int k=0; k<5; k++)
        {
            vector<int> elements = getINCElements(n);
            BST t;
            int maxcomp = 0;
            int maxpoint = 0;
            for(int i=1; i<=n; i++)
            {
                int value = elements[i-1];
                int compBefore = compares;
                int pointersBefore = pointers;
                t.insert(value);
                int diffc = compares - compBefore;
                if(diffc > maxcomp) maxcomp = diffc;
                
                int diffp = pointers - pointersBefore;
                if(diffp > maxpoint) maxpoint = diffp;

                
                int h = t.height();
                incheights << h << endl;
            }
            
            

            

            for(int i=1; i<=n; i++)
            {
                int compBefore = compares;
                int pointersBefore = pointers;

                int del = random(0, n-i);
                t.remove(elements[del]);

                int diffc = compares - compBefore;
                if(diffc > maxcomp) maxcomp = diffc;
                
                int diffp = pointers - pointersBefore;
                if(diffp > maxpoint) maxpoint = diffp;

                elements.erase(elements.begin() + del);

                int h = t.height();
                decheights << h << endl;
            }

        
            int avgcompares = compares/2/n;
            int avgpointers = pointers/2/n;

            file << avgcompares << " " << avgpointers << " " << maxcomp << " " << maxpoint << endl;

            compares = 0;
            pointers = 0;
        }
        
    } 

    incheights.close();
    decheights.close();
    file.close();

   

    return 0; 
}