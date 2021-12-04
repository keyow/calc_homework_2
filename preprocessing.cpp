#include "header.h"
#include <stack>
#include <unordered_map>

bool is_operation(const std::string& token) {
    if (token == "+" || token == "-" || token == "*" ||
        token == "/" || token == "(" || token == ")" ||
        token == "sin" || token == "cos" || token == "tg" ||
        token == "ctg" || token == "exp") {
        return true;
    }
    return false;
}

std::vector<std::string> parse(const std::string& expr) {
    std::vector<std::string> parsed_infix;
    std::string other;
    long double x;
    bool x_defined = false;

    for (const char c : expr) {
        if (c == ' ') {
            continue;
        }

        if (is_operation(std::string(1, c))) {
            if (!other.empty()) {
                if (other == "x") {
                    if (!x_defined) {
                        std::cin >> x;
                        x_defined = true;
                    }
                    parsed_infix.push_back(std::to_string(x));
                } else {
                    parsed_infix.push_back(other);
                }
                other.clear();
            }
            parsed_infix.emplace_back(1, c);
        } else {
            other += c;
        }
    }
    if (!other.empty()) {
        if (other == "x") {
            if (!x_defined) {
                std::cin >> x;
            }
            parsed_infix.push_back(std::to_string(x));
        } else {
            parsed_infix.push_back(other);
        }
        other.clear();
    }

    return parsed_infix;
}

std::vector<std::string> inToPost(const std::vector<std::string>& infix) {
    std::unordered_map<std::string, size_t> precedence {
            {"+", 1},
            {"-", 1},
            {"*", 2},
            {"/", 2},
            {"sin", 3},
            {"cos", 3},
            {"tg", 3},
            {"ctg", 3},
            {"exp", 3}
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