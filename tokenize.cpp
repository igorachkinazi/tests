#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

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

    tokens.push_back(token);
}

int main() {
    vector<string> tokens;
    tokenize("((10+5)*3)", tokens);

    for (const std::string& token : tokens) {
        std::cout << token << std::endl;
    }

    return 0;
}
