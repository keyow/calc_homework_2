#include "header.h"
#include <stack>
#include <unordered_map>

bool is_operation(const std::string& c) {
    if (c == "+" || c == "-" || c == "*" || c == "/") {
        return true;
    }
    return false;
}

std::vector<std::string> parse(const std::string& expr) {
    std::vector<std::string> parsed_infix;
    std::string operand;

    for (const char c : expr) {
        if (c == ' ') {
            continue;
        }

        if (is_operation(std::string(1, c)) || c == ')' || c == '(') {
            if (!operand.empty()) {
                parsed_infix.push_back(operand);
                operand.clear();
            }
            parsed_infix.emplace_back(1, c);
        } else {
            operand += c;
        }
    }
    if (!operand.empty()) {
        parsed_infix.emplace_back(operand);
    }

    return parsed_infix;
}

std::vector<std::string> inToPost(const std::vector<std::string>& infix) {
    std::unordered_map<std::string, size_t> precedence {
            {"+", 1},
            {"-", 1},
            {"*", 2},
            {"/", 2}
    };

    std::vector<std::string> postfix;
    std::stack<std::string> stk;

    for (const std::string& s : infix) {

        if (s == "(") {
            stk.push(s);
        } else if (s == ")") {
            while (stk.top() != "(") {
                postfix.push_back(stk.top());
                stk.pop();
            }
            stk.pop();
        } else if (is_operation(s)) {
            while (!stk.empty() && stk.top() != "(" && precedence[stk.top()] >= precedence[s]) {
                postfix.push_back(stk.top());
                stk.pop();
            }
            stk.push(s);
        } else {
            postfix.push_back(s);
        }

    }

    while (!stk.empty()) {
        postfix.push_back(stk.top());
        stk.pop();
    }

    return postfix;
}