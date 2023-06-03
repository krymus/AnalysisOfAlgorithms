#include<iostream>
#include<random>
#include<vector>
using namespace std;

random_device rd;
mt19937 gen(rd());

int random(int low, int high)
{
    uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

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
        if(t == NULL)
        {
            t = new node;
            t->data = x;
            t->left = t->right = NULL;
        }
        else if(x < t->data)
            t->left = insert(x, t->left);
        else if(x > t->data)
            t->right = insert(x, t->right);
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
        if(t == NULL)
            return NULL;
        else if(x < t->data)
            t->left = remove(x, t->left);
        else if(x > t->data)
            t->right = remove(x, t->right);
        else if(t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
        else
        {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
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

    // global variables used in `print_BST`
    char* left_trace; // needs to be allocaded with size
    char* right_trace; // needs to be allocaded with size


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

vector<int> getRandomPermutation() {
    vector<int> permutation;
    
    for (int i = 1; i <= 50; i++) {
        permutation.push_back(i);
    }
    
    random_device rd;
    mt19937 g(rd());
    shuffle(permutation.begin(), permutation.end(), g);
    
    return permutation;
}

int main() {


    
    BST t;
    
    vector<int> permutation = getRandomPermutation();

    for(int i=0; i<50; i++)
    {
        int value = permutation[i];
        t.insert(value);
        cout<<"inserting "<<value<<endl;
        t.print_BST(t.root , 0 , '-');
    }

    vector<int> del = getRandomPermutation();
    for(int i=0; i<50; i++)
    {
        int value = permutation[del[i]];
        t.remove(value);
        cout<<"removing "<<value<<endl;
        t.print_BST(t.root , 0 , '-');
    }


/*
    for(int i=1; i<=50; i++)
    {
        t.insert(i);
        cout<<"inserting "<<i<<endl;
        t.print_BST(t.root , 0 , '-');
    }


    vector<int> permutation = getRandomPermutation();

    for(int i=0; i<50; i++)
    {
        
        int value = permutation[i];
        t.remove(value);
        cout<<"removing "<<value<<endl;
        t.print_BST(t.root , 0 , '-');
    }
*/

    return 0; 
}