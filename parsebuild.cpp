#include <iostream>
#include <cstdlib>
#include <stack>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


class BinaryTree {

    private:
        string key;
        BinaryTree *leftChild;
        BinaryTree *rightChild;
    public:
        BinaryTree(string rootObj){
            this->key = rootObj;
            this->leftChild = NULL;
            this->rightChild = NULL;
        }

        void insertLeft(string newNode){
            if (this->leftChild == NULL){
            this->leftChild = new BinaryTree(newNode);
            }
            else {
            BinaryTree *t = new BinaryTree(newNode);
            t->leftChild = this->leftChild;
            this->leftChild = t;
            }
        }

        void insertRight(string newNode){
            if (this->rightChild == NULL){
            this->rightChild = new BinaryTree(newNode);
            }
            else {
            BinaryTree *t = new BinaryTree(newNode);
            t->rightChild = this->rightChild;
            this->rightChild = t;
            }
        }

        BinaryTree *getRightChild(){
            return this->rightChild;
        }

        BinaryTree *getLeftChild(){
            return this->leftChild;
        }

        void setRootVal(string obj){
            this->key = obj;
        }

        string getRootVal(){
            return this->key;
        }
};

void tokenize(const string& expr, vector<string>& tokens) {
    string token;

    for (char c : expr) {
        if (std::isdigit(c)) {
            token += c;
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(string(1, c));
        } else if (c == '(' || c == ')') {
             if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(string(1, c));
        }
    }
}

BinaryTree *buildParseTree(const string& expr){
    vector<string> tokenlist;
    tokenize(expr, tokenlist);

    BinaryTree *root = new BinaryTree("");
    stack<BinaryTree*> parentStack;
    parentStack.push(root);
    BinaryTree *currentTree = root;

    for (size_t i = 0; i < tokenlist.size(); i++){
        if (tokenlist[i] == "("){
            // rule 1: open parenthesis
            currentTree->insertLeft("");
            parentStack.push(currentTree);
            currentTree = currentTree->getLeftChild();
        } else if (tokenlist[i] == "+" || tokenlist[i] == "-" ||
                   tokenlist[i] == "/" || tokenlist[i] == "*"){
            // rule 2: operator
            currentTree->setRootVal(tokenlist[i]);
            currentTree->insertRight("");
            parentStack.push(currentTree);
            currentTree = currentTree->getRightChild();
        } else if (tokenlist[i] == ")") {
            // rule 4: closing parenthesis
            currentTree = parentStack.top();
            parentStack.pop();
        } else {
            // rule 3: number
            currentTree->setRootVal(tokenlist[i]);
            BinaryTree *parent = parentStack.top();
            parentStack.pop();
            currentTree = parent;
        }
    }

    return root;
}

void postorder(BinaryTree *tree){
    if (tree != NULL){
        postorder(tree->getLeftChild());
        postorder(tree->getRightChild());
        cout << tree->getRootVal() << endl;
    }
}

int main() {

    BinaryTree *pt = buildParseTree("( ( 10 + 5 ) * 3 )");
    postorder(pt);

    return 0;
}

