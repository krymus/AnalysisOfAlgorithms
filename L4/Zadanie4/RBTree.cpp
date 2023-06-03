#include <iostream>
#include <random>
#include <fstream>

using namespace std;

int pointers = 0;
int compares = 0;

// global variables used in `print_BST`
char* left_trace; // needs to be allocaded with size
char* right_trace; // needs to be allocaded with size


struct Node {
	int data; 
	Node *parent; 
	Node *left; 
	Node *right; 
	int color; // 1 -> Red, 0 -> Black
};

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
    return false;
}

typedef Node *NodePtr;

class RBTree {
private:
	NodePtr root;
	NodePtr TNULL;

	void initializeNULLNode(NodePtr node, NodePtr parent) {
		node->data = 0;
		node->parent = parent;
		node->left = nullptr;
		node->right = nullptr;
		node->color = 0;
	}

	NodePtr searchTreeHelper(NodePtr node, int key) {
		if (node == TNULL || key == node->data) {
			return node;
		}

		if (key < node->data) {
			return searchTreeHelper(node->left, key);
		} 
		return searchTreeHelper(node->right, key);
	}

	void fixDelete(NodePtr x) {
		NodePtr s;
		while (x != root && x->color == 0) {
			pointers++;
			pointers++;
			if (x == x->parent->left) {
				s = x->parent->right;
				pointers++;
				if (s->color == 1) {
					s->color = 0;
					x->parent->color = 1;
					leftRotate(x->parent);
					s = x->parent->right;
					pointers++;
				}


				
				if (s->left->color == 0 && s->right->color == 0) {
					s->color = 1;
					x = x->parent;
					pointers++;
				} else {
					if (s->right->color == 0) {
						s->left->color = 0;
						s->color = 1;
						rightRotate(s);
						s = x->parent->right;
						pointers++;
					} 

					s->color = x->parent->color;
					x->parent->color = 0;
					s->right->color = 0;
					leftRotate(x->parent);
					x = root;
					pointers++;
				}
			} else {
				s = x->parent->left;
				pointers++;
				if (s->color == 1) {
					s->color = 0;
					x->parent->color = 1;
					rightRotate(x->parent);
					s = x->parent->left;
					pointers++;
				}

				if (s->right->color == 0 && s->right->color == 0) {
					s->color = 1;
					x = x->parent;
					pointers++;
				} else {
					if (s->left->color == 0) {
						s->right->color = 0;
						s->color = 1;
						leftRotate(s);
						s = x->parent->left;
						pointers++;
					} 

					s->color = x->parent->color;
					x->parent->color = 0;
					s->left->color = 0;
					rightRotate(x->parent);
					x = root;
					pointers++;
				}
			} 
		}
		x->color = 0;
	}


	void rbTransplant(NodePtr u, NodePtr v){
		pointers++;
		if (u->parent == nullptr) {
			root = v;
			pointers++;
		} else if (u == u->parent->left){
			pointers += 2;
			u->parent->left = v;
		} else {
			pointers += 2;
			u->parent->right = v;
		}
		v->parent = u->parent;
		pointers++;
	}

	void deleteNodeHelper(NodePtr node, int key) {
		NodePtr z = TNULL;
		NodePtr x, y;
		while (node != TNULL){
			pointers++;

			if (node->data == key) {
				compares++;
				z = node;
			}

			if (node->data <= key) {
				compares++;
				pointers++;
				node = node->right;
			} else {
				pointers++;
				node = node->left;
			}
		}

		if (z == TNULL) {
			pointers++;
			//cout<<"Couldn't find key in the tree"<<endl;
			return;
		} 

		y = z;
		int y_original_color = y->color;

		pointers++;
		if (z->left == TNULL) {
			x = z->right;
			pointers++;
			rbTransplant(z, z->right);
		} else if (z->right == TNULL) {
			pointers+=2;
			x = z->left;
			rbTransplant(z, z->left);
		} else {
			pointers+=2;
			y = minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			pointers++;
			if (y->parent == z) {
				x->parent = y;
				pointers++;
			} else {
				rbTransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
				pointers += 2;
			}

			rbTransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			pointers += 2;
			y->color = z->color;
		}
		delete z;
		if (y_original_color == 0){
			fixDelete(x);
		}
	}
	

	void fixInsert(NodePtr k){
		NodePtr u;
		while (k->parent->color == 1) {
			pointers++;
			if (k->parent == k->parent->parent->right) {
				u = k->parent->parent->left; 
				pointers++;
				if (u->color == 1) {

					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
					pointers++;
				} else {
					if (k == k->parent->left) {
						k = k->parent;
						pointers++;
						rightRotate(k);
					}
					k->parent->color = 0;
					k->parent->parent->color = 1;
					leftRotate(k->parent->parent);
				}
			} else {
				u = k->parent->parent->right; 
				pointers++;

				if (u->color == 1) {
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;	
					pointers++;
				} else {
					if (k == k->parent->right) {
						k = k->parent;
						leftRotate(k);
					}
					k->parent->color = 0;
					k->parent->parent->color = 1;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root) {
				break;
			}
		}
		root->color = 0;
	}



public:
	RBTree() {
		TNULL = new Node;
		TNULL->color = 0;
		TNULL->left = nullptr;
		TNULL->right = nullptr;
		root = TNULL;
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
		return searchTreeHelper(this->root, k);
	}

	NodePtr minimum(NodePtr node) {
		while (node->left != TNULL) {
			pointers += 2;
			node = node->left;
		}
		return node;
	}


	NodePtr maximum(NodePtr node) {
		while (node->right != TNULL) {
			pointers += 2;
			node = node->right;
		}
		return node;
	}

	
	NodePtr successor(NodePtr x) {
		if (x->right != TNULL) {
			return minimum(x->right);
		}

		NodePtr y = x->parent;
		while (y != TNULL && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	
	NodePtr predecessor(NodePtr x) {
		
		if (x->left != TNULL) {
			return maximum(x->left);
		}

		NodePtr y = x->parent;
		while (y != TNULL && x == y->left) {
			x = y;
			y = y->parent;
		}

		return y;
	}

	void leftRotate(NodePtr x) {
		NodePtr y = x->right;
		x->right = y->left;
		pointers += 2;
		if (y->left != TNULL) {
			y->left->parent = x;
			pointers++;
		}
		y->parent = x->parent;
		pointers++;
		if (x->parent == nullptr) {
			pointers++;
			this->root = y;
		} else if (x == x->parent->left) {
			pointers++;
			x->parent->left = y;
		} else {
			x->parent->right = y;
			pointers++;
		}
		y->left = x;
		x->parent = y;
		pointers += 2;
	}

	void rightRotate(NodePtr x) {
		NodePtr y = x->left;
		x->left = y->right;
		pointers += 2;
		if (y->right != TNULL) {
			y->right->parent = x;
			pointers++;
		}
		y->parent = x->parent;
		pointers++;
		if (x->parent == nullptr) {
			pointers++;
			this->root = y;
		} else if (x == x->parent->right) {
			pointers += 2;
			x->parent->right = y;
		} else {
			pointers += 2;
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
		pointers += 2;
	}


	void insert(int key) {

		NodePtr node = new Node;
		node->parent = nullptr;
		node->data = key;
		node->left = TNULL;
		node->right = TNULL;
		node->color = 1; 

		NodePtr y = nullptr;
		NodePtr x = this->root;

		while (x != TNULL) {
			pointers += 2;
			y = x;
			if (compare(node->data, x->data)) {
				x = x->left;
			} else {
				x = x->right;
			}
		}

	
		node->parent = y;
		pointers += 3;
		if (y == nullptr) {
			root = node;
		} else if (compare(node->data, y->data)) {
			y->left = node;
		} else {
			y->right = node;
		}

	
		pointers++;
		if (node->parent == nullptr){
			node->color = 0;
			return;
		}

		pointers++;
		if (node->parent->parent == nullptr) {
			return;
		}

		fixInsert(node);
	}

	NodePtr getRoot(){
		return this->root;
	}

	void deleteNode(int data) {
		deleteNodeHelper(this->root, data);
	}



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

void shuffle(vector<int>& vec, int n) {
    for(int i = 0; i<n; i++)
	{
		swap(vec[random(0,vec.size())], vec[random(0,vec.size())]);
	}
}




int main()
{
    left_trace = (char*)malloc( 1000*sizeof(char) );
    right_trace = (char*)malloc( 1000*sizeof(char) );
    for(int i=0; i<1000; i++)
    {
        left_trace[i]=' ';
        left_trace[i]=' ';
    }

    ofstream incheights("incheightsRANDOM.txt");
    ofstream decheights("decheightsRANDOM.txt");
    ofstream file("fileRANDOM.txt");

    for(int n = 10000; n<100001; n+=10000)
    {
        cout<<n<<endl;
        for(int k=0; k<1; k++)
        {
            RBTree t;

			//vector<int> tab;
			//for(int i=0; i<n; i++) tab.push_back(i+1);

			//shuffle(tab, n);


            int maxcomp = 0;
            int maxpoint = 0;

            for(int i=1; i<=n; i++)
            {
                int compBefore = compares;
                int pointersBefore = pointers;
                t.insert(random(1, 2*n -1));

                int diffc = compares - compBefore;
                if(diffc > maxcomp) maxcomp = diffc;
                
                int diffp = pointers - pointersBefore;
                if(diffp > maxpoint) maxpoint = diffp;

                
                int h = t.height();
                incheights << h << endl;
            }
            
			cout<<"inserted"<<endl;

            for(int i=1; i<=n; i++)
            {
                int compBefore = compares;
                int pointersBefore = pointers;
				
				//int val = tab[n-i];
                t.deleteNode(random(1, 2*n -1));			

                int diffc = compares - compBefore;
                if(diffc > maxcomp) maxcomp = diffc;
                
                int diffp = pointers - pointersBefore;
                if(diffp > maxpoint) maxpoint = diffp;


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