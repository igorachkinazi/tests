// infix_calculator.cpp
// calculator implementation based on infix/postfix for user input string

#include <iostream>
#include <stack>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

string infixToPostfix(string infixexpr) {
    //performs the postfix process.
    unordered_map <char,int> prec;
    prec['*']=3;
    prec['/']=3;
    prec['+']=2;
    prec['-']=2;
    prec['(']=1;
    stack<char> opStack;
    vector<char> postfixVector;
    string letsnums = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    for (char token:infixexpr) {
        //for each character in infixexpr
        if (token == ' ') {
            continue;
        }
        else if (letsnums.find(token)<=letsnums.length()) { //finds if the token is inside of letsnums
            postfixVector.emplace_back(token); // appends to the end of the container.
        } else if (token == '(') {
            opStack.push(token);
        } else if (token == ')') {
            char topToken;
            topToken = opStack.top();
            opStack.pop();
            while (topToken != '(') {
                postfixVector.emplace_back(topToken);
                topToken=opStack.top();
                opStack.pop();
            }
        } else { //if the token is not inside of letsnums.
            while (!opStack.empty() && (prec[opStack.top()]>=prec[token])) //while the stack is not empty and
                                                                           //the top item of the stack is on a
                                                                           //higher level of PEMDAS than token.
            {
                postfixVector.emplace_back(opStack.top());
                opStack.pop();
                }
            opStack.push(token);
        }
    }
    while (!opStack.empty()) {
        postfixVector.emplace_back(opStack.top());
        opStack.pop();
    }

    string s(postfixVector.begin(),postfixVector.end());

    return s;
}

int doMath(char op, int op1, int op2) {
    //Does math based on what op is passed as.
    if (op == '*') {
        return (op1 * op2);
    } else if (op == '/') {
        return (op1 / op2);
    } else if (op == '+') {
        return (op1 + op2);
    } else {
        return (op1 - op2);
    }
}

int postfixEval(string postfixExpr) {
    stack<int> operandStack;
    string nums = "0123456789";

    for (char i : postfixExpr) {
        if ((nums.find(i) <= nums.length())) { // Check if the current char is a number
            operandStack.push(int(i) - 48); // conversion from char to ascii
            // then subtract 48 to get the int value
            } else if (i != ' ') {
                          int operand2 = operandStack.top();
                          operandStack.pop();
                          int operand1 = operandStack.top();
                          operandStack.pop();
                          int result = doMath(i, operand1, operand2);
                          operandStack.push(result);
                  }
    }
    return operandStack.top();
}

int main() {
    string str;
    cout << "Enter expression with single digit numbers" << endl;
    getline(cin, str);
    string infixStr = infixToPostfix(str);
    cout << postfixEval(infixStr) << endl;
    return 0;
}
