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

class Operator {
    public:
        int add(int x, int y)    { return x + y; }
        int sub(int x, int y)    { return x - y; }
        int mul(int x, int y)    { return x * y; }
        int div(int x, int y)    { return x / y; }
        int op_and(int x, int y) { return x & y; }
        int op_or(int x, int y)   { return x | y; }
        int op_not(int x)        { return !x; }
};

int to_int(string str) {
    stringstream convert(str);
    int x = 0;
    convert >> x;
    return x;
}

/*string to_string(int num) {
    string str;
    ostringstream convert;
    convert << num;
    str = convert.str();
    return str;
}*/

void tokenize(const string& expr, vector<string>& tokens) {
    string token;

    for (char c : expr) {
        if (std::isdigit(c)) {
            token += c;
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '&' || c == '|' || c == '!') {
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
            if(tokenlist[i+1] != "!") {
               // rule 1: open parenthesis
               currentTree->insertLeft("");
               parentStack.push(currentTree);
               currentTree = currentTree->getLeftChild();
            }
        } else if (tokenlist[i] == "+" || tokenlist[i] == "-" ||
                   tokenlist[i] == "/" || tokenlist[i] == "*" ||
                   tokenlist[i] == "&" || tokenlist[i] == "|" ||
                   tokenlist[i] == "!") {
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
        if(tree->getLeftChild())
           postorder(tree->getLeftChild());
        postorder(tree->getRightChild());
        cout << tree->getRootVal() << endl;
    }
}

string evaluate(BinaryTree *parseTree) {
    Operator Oper;

    BinaryTree *leftC = parseTree->getLeftChild();
    BinaryTree *rightC = parseTree->getRightChild();

    if (leftC && rightC) {
        if (parseTree->getRootVal() == "+") {
            return to_string(Oper.add(to_int(evaluate(leftC)), to_int(evaluate(rightC))));
        } else if (parseTree->getRootVal() == "-") {
            return to_string(Oper.sub(to_int(evaluate(leftC)), to_int(evaluate(rightC))));
        } else if (parseTree->getRootVal() == "*") {
            return to_string(Oper.mul(to_int(evaluate(leftC)), to_int(evaluate(rightC))));
        } else if (parseTree->getRootVal() == "/") {
            return to_string(Oper.div(to_int(evaluate(leftC)), to_int(evaluate(rightC))));
        } else if(parseTree->getRootVal() == "&") {
            return to_string(Oper.op_and(to_int(evaluate(leftC)), to_int(evaluate(rightC))));
        } else if(parseTree->getRootVal() == "|") {
            return to_string(Oper.op_or(to_int(evaluate(leftC)), to_int(evaluate(rightC))));
        }
        else
            return "";
    } else if(rightC) {
        if(parseTree->getRootVal() == "!") {
            return to_string(Oper.op_not(to_int(evaluate(rightC))));
        }
        else return "";
    }
    else {
        return parseTree->getRootVal();
    }
}

int main() {

    BinaryTree *pt = buildParseTree("(((10+5)+(!1))*(3+(3&0))");
    postorder(pt);
    cout << endl << "Evaluate: ";
    cout << evaluate(pt) << endl;

    return 0;
}

