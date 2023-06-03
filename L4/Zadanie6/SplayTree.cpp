#include <iostream>
#include <fstream>
#include <random>

using namespace std;

long int compares = 0;
long int pointers = 0;

struct Node {
	int data; 
	Node *parent; 
	Node *left; 
	Node *right; 
};

random_device rd;
mt19937 gen(rd());

int random(int low, int high)
{
    uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

char* left_trace; 
char* right_trace; 

typedef Node *NodePtr;

class SplayTree {
private:
	NodePtr root;

	NodePtr searchTreeHelper(NodePtr node, int key) {
		pointers++;
		if (node == nullptr || key == node->data) {
			return node;
		}

		compares++;
		if (key < node->data) {
			return searchTreeHelper(node->left, key);
		} 
		return searchTreeHelper(node->right, key);
	}

	void deleteNodeHelper(NodePtr node, int key) {
		NodePtr x = nullptr;
		NodePtr t, s;
		while (node != nullptr){
			pointers++;

			if (node->data == key) {
				x = node;
			}
			compares++;
			if (node->data <= key) {
				node = node->right;
			} else {
				node = node->left;
			}
			pointers++;
		}

		pointers++;
		if (x == nullptr) {
			cout<<"Couldn't find key in the tree"<<endl;
			return;
		}
		split(x, s, t); 
		if (s->left){ 
			s->left->parent = nullptr;
			pointers++;
		}
		root = join(s->left, t);
		delete(s);
		s = nullptr;
	}



	void leftRotate(NodePtr x) {
		NodePtr y = x->right;
		x->right = y->left;
		pointers++;
		pointers++;
		if (y->left != nullptr) {
			y->left->parent = x;
			pointers++;
		}
		y->parent = x->parent;
		pointers++;
		pointers++;
		if (x->parent == nullptr) {
			this->root = y;
			pointers++;
		} else if (x == x->parent->left) {
			pointers++;
			pointers++;
			x->parent->left = y;
		} else {
			x->parent->right = y;
			pointers++;
			pointers++;
		}
		y->left = x;
		x->parent = y;
		pointers++;
		pointers++;
	}

	void rightRotate(NodePtr x) {
		NodePtr y = x->left;
		x->left = y->right;
		pointers++;
		pointers++;
		if (y->right != nullptr) {
			y->right->parent = x;
			pointers++;
		}
		y->parent = x->parent;
		pointers++;
		pointers++;
		if (x->parent == nullptr) {
			pointers++;
			this->root = y;
		} else if (x == x->parent->right) {
			pointers++;
			pointers++;
			x->parent->right = y;
		} else {
			x->parent->left = y;
			pointers++;
			pointers++;
		}
		y->right = x;
		x->parent = y;
		pointers++;
		pointers++;
	}

	void splay(NodePtr x) {
		while (x->parent) {
			pointers++;
			pointers++;
			if (!x->parent->parent) {
				pointers++;
				if (x == x->parent->left) {
					rightRotate(x->parent);
				} else {
					leftRotate(x->parent);
				}
			} else if (x == x->parent->left && x->parent == x->parent->parent->left) {
				pointers++;
				pointers++;
				rightRotate(x->parent->parent);
				rightRotate(x->parent);
			} else if (x == x->parent->right && x->parent == x->parent->parent->right) {
				pointers++;
				pointers++;
				pointers++;
				pointers++;
				leftRotate(x->parent->parent);
				leftRotate(x->parent);
			} else if (x == x->parent->right && x->parent == x->parent->parent->left) {
				pointers++;
				pointers++;
				pointers++;
				pointers++;
				pointers++;
				pointers++;
				leftRotate(x->parent);
				rightRotate(x->parent);
			} else {
				pointers++;
				pointers++;
				pointers++;
				pointers++;
				pointers++;
				pointers++;
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
		pointers++;
		t->parent = x;
		pointers++;
		return x;
	}

	void split(NodePtr &x, NodePtr &s, NodePtr &t) {
		splay(x);
		pointers++;
		if (x->right) {
			t = x->right;
			pointers++;
			t->parent = nullptr;
			pointers++;
		} else {
			t = nullptr;
			pointers++;
		}
		s = x;
		s->right = nullptr;
		pointers++;
		pointers++;
		x = nullptr;
	} 

public:
	SplayTree() {
		root = nullptr;
	}

	int height(NodePtr x, int i)
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

	NodePtr successor(NodePtr x) {
		if (x->right != nullptr) {
			return minimum(x->right);
		}


		NodePtr y = x->parent;
		while (y != nullptr && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}


	NodePtr predecessor(NodePtr x) {
		if (x->left != nullptr) {
			return maximum(x->left);
		}

		NodePtr y = x->parent;
		while (y != nullptr && x == y->left) {
			x = y;
			y = y->parent;
		}

		return y;
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
			pointers++;
			y = x;
			if (node->data < x->data) {
				compares++;
				x = x->left;
			} else {
				x = x->right;
			}
		}

		node->parent = y;
		pointers++;
		if (y == nullptr) {
			root = node;
			pointers++;
		} else if (node->data < y->data) {
			y->left = node;
			pointers++;
		} else {
			y->right = node;
			pointers++;
		}

		compares++;


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


vector<int> getElements(int n) {
    vector<int> permutation;
    
    for (int i = 1; i <= n; i++) {
        permutation.push_back(i);
    }
    
    random_device rd;
    mt19937 g(rd());
    //shuffle(permutation.begin(), permutation.end(), g);
    
    return permutation;
}

vector<int> getDel(int n) {
    vector<int> permutation;
    
    
    for (int i = 0; i < n; i++) {
        permutation.push_back(i);
    }
    
    random_device rd;
    mt19937 g(rd());
    shuffle(permutation.begin(), permutation.end(), g);
    
    return permutation;
}


int main() {

    ofstream incheights("incheightsINC.txt");
    ofstream decheights("decheightsINC.txt");
    ofstream file("fileINC.txt");

    for(int n = 10000; n<100001; n+=10000)
    {
        cout<<n<<endl;
        for(int k=0; k<5; k++)
        {
            vector<int> elements = getElements(n);
            SplayTree t;
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
                t.deleteNode(elements[del]);

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
