#include <iostream>
#include <random>

using namespace std;

struct Node {
	int data; 
	Node *parent; 
	Node *left; 
	Node *right; 
};


char* left_trace; 
char* right_trace; 

random_device rd;
mt19937 gen(rd());

int random(int low, int high)
{
    uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

typedef Node *NodePtr;

class SplayTree {
private:
	NodePtr root;

	NodePtr searchTreeHelper(NodePtr node, int key) {
		if (node == nullptr || key == node->data) {
			return node;
		}

		if (key < node->data) {
			return searchTreeHelper(node->left, key);
		} 
		return searchTreeHelper(node->right, key);
	}

	void deleteNodeHelper(NodePtr node, int key) {
		NodePtr x = nullptr;
		NodePtr t, s;
		while (node != nullptr){
			if (node->data == key) {
				x = node;
			}

			if (node->data <= key) {
				node = node->right;
			} else {
				node = node->left;
			}
		}

		if (x == nullptr) {
			cout<<"Couldn't find key in the tree"<<endl;
			return;
		}
		split(x, s, t); 
		if (s->left){ 
			s->left->parent = nullptr;
		}
		root = join(s->left, t);
		delete(s);
		s = nullptr;
	}



	void leftRotate(NodePtr x) {
		NodePtr y = x->right;
		x->right = y->left;
		if (y->left != nullptr) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void rightRotate(NodePtr x) {
		NodePtr y = x->left;
		x->left = y->right;
		if (y->right != nullptr) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->right) {
			x->parent->right = y;
		} else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	void splay(NodePtr x) {
		while (x->parent) {
			if (!x->parent->parent) {
				if (x == x->parent->left) {
					rightRotate(x->parent);
				} else {
					leftRotate(x->parent);
				}
			} else if (x == x->parent->left && x->parent == x->parent->parent->left) {
				rightRotate(x->parent->parent);
				rightRotate(x->parent);
			} else if (x == x->parent->right && x->parent == x->parent->parent->right) {
				leftRotate(x->parent->parent);
				leftRotate(x->parent);
			} else if (x == x->parent->right && x->parent == x->parent->parent->left) {
				leftRotate(x->parent);
				rightRotate(x->parent);
			} else {
				rightRotate(x->parent);
				leftRotate(x->parent);
			}
		}
	}

	NodePtr join(NodePtr s, NodePtr t){
		if (!s) {
			return t;
		}

		if (!t) {
			return s;
		}
		NodePtr x = maximum(s);
		splay(x);
		x->right = t;
		t->parent = x;
		return x;
	}

	void split(NodePtr &x, NodePtr &s, NodePtr &t) {
		splay(x);
		if (x->right) {
			t = x->right;
			t->parent = nullptr;
		} else {
			t = nullptr;
		}
		s = x;
		s->right = nullptr;
		x = nullptr;
	} 

public:
	SplayTree() {
		root = nullptr;
	}

	
	NodePtr searchTree(int k) {
		NodePtr x = searchTreeHelper(this->root, k);
		if (x) {
			splay(x);
		}
		return x;
	}


	NodePtr minimum(NodePtr node) {
		while (node->left != nullptr) {
			node = node->left;
		}
		return node;
	}


	NodePtr maximum(NodePtr node) {
		while (node->right != nullptr) {
			node = node->right;
		}
		return node;
	}

	void insert(int key) {
		NodePtr node = new Node;
		node->parent = nullptr;
		node->left = nullptr;
		node->right = nullptr;
		node->data = key;
		NodePtr y = nullptr;
		NodePtr x = this->root;

		while (x != nullptr) {
			y = x;
			if (node->data < x->data) {
				x = x->left;
			} else {
				x = x->right;
			}
		}

		node->parent = y;
		if (y == nullptr) {
			root = node;
		} else if (node->data < y->data) {
			y->left = node;
		} else {
			y->right = node;
		}

		splay(node);
	}

	NodePtr getRoot(){
		return this->root;
	}

	void deleteNode(int data) {
		deleteNodeHelper(this->root, data);
	}

	

     // global variables used in `print_BST`
    char* left_trace; // needs to be allocaded with size
    char* right_trace; // needs to be allocaded with size

    void print_BST( NodePtr root, int depth,char prefix)
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

};

vector<int> getElements() {
    vector<int> permutation;
    

    for (int i = 1; i <= 50; i++) {
        permutation.push_back(i);
    }
    

    random_device rd;
    mt19937 g(rd());
    //shuffle(permutation.begin(), permutation.end(), g);
    
    return permutation;
}

vector<int> getDel() {
    vector<int> permutation;
    
    for (int i = 0; i < 50; i++) {
        permutation.push_back(i);
    }
    
    random_device rd;
    mt19937 g(rd());
    shuffle(permutation.begin(), permutation.end(), g);
    
    return permutation;
}


int main() {
	SplayTree bst;
	
    bst.left_trace = (char*)malloc( 50*sizeof(char) );
    bst.right_trace = (char*)malloc( 50*sizeof(char) );
    for(int i=0; i<50; i++)
    {
        bst.left_trace[i]=' ';
        bst.left_trace[i]=' ';
    }

	vector<int> permutation = getElements();
	

    for(int i=0; i<50; i++)
    {
        int value = permutation[i];
        bst.insert(value);
        cout<<"inserting "<<value<<endl;
        bst.print_BST(bst.getRoot() , 0 , '-');
		cout<<endl;
    }

    vector<int> del = getDel();
	

    for(int i=0; i<50; i++)
    {
		
        int value = permutation[del[i]];
        bst.deleteNode(value);
        cout<<"removing "<<value<<endl;
        bst.print_BST(bst.getRoot() , 0 , '-');
		cout<<endl;
    }

	
	

	return 0;
}