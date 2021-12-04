#include "header.h"
#include <stack>
#include <unordered_map>
#include <sstream>

bool is_operation(const std::string& token) {
    if (token == "+" || token == "-" || token == "*" ||
        token == "/") {
        return true;
    }
    return false;
}

bool is_function(const std::string& token) {
    if (token == "sin" || token == "cos" || token == "tg" ||
        token == "ctg" || token == "exp") {
        return true;
    }
    return false;
}

bool is_number(const std::string& token) {
    std::istringstream iss(token);
    double number;
    iss >> number;
    return iss.eof() && !iss.fail();
}

std::vector<std::string> parse(const std::string& expr) {
    std::vector<std::string> parsed_infix;
    std::stack<char> brackets;
    std::string other;
    char prev = ' ';
    std::string prev_operand;

    for (const char c : expr) {
        if (c == ' ') {
            continue;
        }

        if (is_operation(std::string(1, c)) || c == ')' || c == '(') {
            if (c == '(') {
                brackets.push(c);
                prev_operand.clear();
            } else if (c == ')') {
                if (brackets.empty() || brackets.top() != '(') {
                    std::cerr << "[ERROR] : wrong brackets sequence" << std::endl;
                    exit(-1);
                }
                brackets.pop();
            }

            if (!other.empty()) {
                if (other != "x") {
                    if (!is_function(other) && !is_number(other)) {
                        std::cerr << "[ERROR] : wrong operands" << std::endl;
                        exit(-1);
                    } else if (!is_function(other) && stold(other) == 0. && !parsed_infix.empty() &&
                               parsed_infix.back() == "/") {
                        std::cerr << "[ERROR] : division by zero" << std::endl;
                        exit(-1);
                    } else if (is_function(other) && c != '(') {
                        std::cerr << "[ERROR] : wrong function initialization" << std::endl;
                        exit(-1);
                    }
                }

                parsed_infix.push_back(other);
                prev_operand = other;
                other.clear();
            } else if ((prev != ' ' && prev != ')' && prev != '(' && c != '(') ||
                       (prev == ' ' && c != '+' && c != '-' && c != '(' && c != ')') ||
                       (prev == ')' && c == '(')) {
                std::cerr << "[ERROR] : not enough arguments or operands" << std::endl;
                exit(-1);
            } else if (is_function(prev_operand) || (prev_operand.empty() && (c == '-' || c == '+'))) {
                parsed_infix.emplace_back("0");
            }
            parsed_infix.emplace_back(1, c);
            prev = c;
        } else {
            other += c;
        }
    }

    if (!brackets.empty()) {
        std::cerr << "[ERROR] : wrong brackets sequence" << std::endl;
        exit(-1);
    }
    if (!other.empty()) {
        if (other != "x") {
            if (!is_function(other) && !is_number(other)) {
                std::cerr << "[ERROR] : wrong operands" << std::endl;
                exit(-1);
            } else if (!is_function(other) && stold(other) == 0. && !parsed_infix.empty() &&
                       parsed_infix.back() == "/") {
                std::cerr << "[ERROR] : division by zero" << std::endl;
                exit(-1);
            } else if (is_function(other)) {
                std::cerr << "[ERROR] : wrong function initialization" << std::endl;
                exit(-1);
            }
        }
        parsed_infix.push_back(other);
        other.clear();
    } else if (prev != ')' && prev != '(') {
        std::cerr << "[ERROR] : not enough arguments" << std::endl;
        exit(-1);
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
        } else if (is_operation(s) || is_function(s) || s == "(" || s == ")" ) {
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

    if (std::find(postfix.begin(), postfix.end(), "x") != postfix.end()) {
        long double x;

        std::cout << "Enter x: ";
        std::cin >> x;
        std::cout << std::endl;

        for (auto it = postfix.begin(); it != postfix.end(); it++) {
            if (*it == "x") {
                *it = std::to_string(x);
            }
        }
    }
    return postfix;
}