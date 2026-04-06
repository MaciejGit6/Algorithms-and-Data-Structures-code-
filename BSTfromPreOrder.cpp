#include <iostream>
#include <string>
#include <sstream>
#include <vector>


using namespace std;

class Node
{
	public:
		Node *left;
		Node *right;
		int val;
};

class BstTree
{
	public:
		Node* root;
		BstTree(vector<int>& preOrder, int size);
		void inOrderSeq();	
		void postOrderSeq();
		~BstTree();
	private:
		void postOrder(Node *);
		void deleteNode(Node*);
		Node* pre(vector<int>& preOrder, int preOrderL, int size);
};

/* constructor: constructs BstTree from PreOrder sequence and the size size.
Uses auxiliary function pre that constructs bst tree from the sequence PreOrder.
*/
BstTree::BstTree(vector<int>& preOrder, int size)
{
	root = pre(preOrder, 0, size);
}

BstTree::~BstTree()
{
	deleteNode(root);
}

void BstTree::deleteNode(Node* curr)
{
	if (curr!=NULL)
	{
		deleteNode(curr->left);
		deleteNode(curr->right);
		//cout << "Usuwanie noda z kluczem:" << curr ->val << "\n" ;
		delete curr;
	}
}


/* constructs bst-tree from the sequence preOrder that starts at index preOrderL
 and has size size */
Node* BstTree::pre(vector<int>& preOrder, int preOrderL, int size)
{
	if (size <= 0)
	{
		return NULL;
	}

	Node* newNode = new Node();
	newNode->val = preOrder[preOrderL];
	newNode->left = NULL;
	newNode->right = NULL;

	int leftSize = 0;
	for (int i = 1; i < size; i++)
	{
		if (preOrder[preOrderL + i] < newNode->val)
		{
			leftSize++;
		}
		else
		{
			break;
		}
	}

	newNode->left = pre(preOrder, preOrderL + 1, leftSize);

	newNode->right = pre(preOrder, preOrderL + 1 + leftSize, size - 1 - leftSize);

	return newNode;
}

void BstTree::postOrderSeq()
{
	postOrder(root);
}

void BstTree::postOrder(Node * curr)
{
	if (curr == NULL) 
	{
		cout << "";
		return;
	}
	postOrder(curr->left);
	postOrder(curr->right);
	cout << curr->val <<" ";
}

int main()
{
	vector<int> preOrder; 
	int z,n;
	cin >> z;
	while(z)
	{		
		cin >> n;
		preOrder.clear();
		for(int i =0; i<n; i++)
		{
			int val;
			cin >> val;
			preOrder.push_back(val);
		}
		BstTree bstTree = BstTree(preOrder, n);// constructs the bst-tree bstTree
		bstTree.postOrderSeq(); // prints bstTree in PostOrder sequence
		cout << "\n";
		z--;
	}
}

