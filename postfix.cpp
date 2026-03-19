// postfix.cpp
// Solves a postfix math problem.
// handles errors in input string

#include <iostream>
#include <stack>
#include <string>

using namespace std;

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
                          if(operandStack.empty()) {
                              cout << "empty operandStack at " << i << endl;
                              return -1;
                          }
                          int operand2 = operandStack.top();
                          operandStack.pop();
                          if(operandStack.empty()) {
                              cout << "empty operandStack before " << i << endl;
                              return -1;
                          }
                          int operand1 = operandStack.top();
                          operandStack.pop();
                          int result = doMath(i, operand1, operand2);
                          operandStack.push(result);
                  }
    }
    return operandStack.top();
}

int main() {
    cout << (" 5 3 *  4 2 - / ") << endl;
    cout << postfixEval(" 5 3 * 4 2 - / ") << endl;
    cout << (" 5 * 3 / (4 - 2)") << endl;
    cout << postfixEval(" 5 * 3 / (4 - 2)") << endl;
    return 0;
}

