#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Node {
public:
    Node* left;
    Node* right;
    int val;
};

class BstTree {
public:
    Node* root;
    BstTree() { root = NULL; }
    void inOrderSeq();
    void postOrderSeq();
    void preOrderSeq();
    int bstInsert(int _val);
    int bstSearch(int _val);
    ~BstTree();
private:
    void inOrder(Node*);
    void postOrder(Node*);
    void preOrder(Node*);
    void deleteNode(Node*);
};

BstTree::~BstTree() { deleteNode(root); }

void BstTree::deleteNode(Node* curr) {
    if (curr != NULL) {
        deleteNode(curr->left);
        deleteNode(curr->right);
        delete curr;
    }
}

int BstTree::bstInsert(int _val) {
    if (root == NULL) {
        Node* n = new Node;
        n->val = _val;               
        n->left = n->right = NULL;
        root = n;
        return 1;
    }
    Node* curr = root;
    while (true) {
        if (_val == curr->val) {
            return 0;
        }
        else if (_val < curr->val) {
            if (curr->left == NULL) {
                Node* n = new Node;
                n->val = _val;
                n->left = n->right = NULL;
                curr->left = n;
                return 1;
            }
            else {
                curr = curr->left;
            }
        }
        else {
            if (curr->right == NULL) {
                Node* n = new Node;
                n->val = _val;
                n->left = n->right = NULL;
                curr->right = n;
                return 1;
            }
            else {
                curr = curr->right;
            }
        }
    }
}

int BstTree::bstSearch(int _val) {
    Node* curr = root;
    while (curr != NULL) {
        if (_val == curr->val) return 1;
        else if (_val < curr->val) curr = curr->left;
        else curr = curr->right;
    }
    return 0;
}

void BstTree::preOrderSeq() { preOrder(root); cout << "\n"; }
void BstTree::preOrder(Node* curr) {
    if (curr != NULL) {              
        cout << curr->val << ' ';    
        preOrder(curr->left);
        preOrder(curr->right);
    }
}

void BstTree::inOrderSeq() { inOrder(root); cout << "\n"; }
void BstTree::inOrder(Node* curr) {
    if (curr != NULL) {
        inOrder(curr->left);
        cout << curr->val << ' ';
        inOrder(curr->right);
    }
}

void BstTree::postOrderSeq() { postOrder(root); cout << "\n"; }
void BstTree::postOrder(Node* curr) {
    if (curr != NULL) {              
        postOrder(curr->left);
        postOrder(curr->right);
        cout << curr->val << ' ';
    }
}

int main() {
    int z, n;
    string zstr, nstr;
    getline(cin, zstr);
    istringstream(zstr) >> z;
    while (z) {
        getline(cin, nstr);
        istringstream(nstr) >> n;
        BstTree bstTree;
        for (int i = 0; i < n; i++) {
            string line;
            getline(cin, line);
            string instr;
            int num;
            istringstream iss(line);
            iss >> instr >> num;     
            if (instr == "INSERT")
                cout << bstTree.bstInsert(num) << "\n";
            else if (instr == "SEARCH")
                cout << bstTree.bstSearch(num) << "\n";
            else if (instr == "PREORDER")
                bstTree.preOrderSeq();
            else if (instr == "INORDER")
                bstTree.inOrderSeq();
            else if (instr == "POSTORDER")
                bstTree.postOrderSeq();
        }
        z--;
    }
}
