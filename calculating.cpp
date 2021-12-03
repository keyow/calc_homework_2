#include <vector>
#include <string>
#include <stack>
#include <iostream>

long double calculate(std::vector<std::string>& postfix_expr) {
    std::stack<long double> stk;

    for (const std::string& s : postfix_expr) {
        if (s == "+" || s == "-" || s == "*" || s == "/") {
            auto second = stk.top();
            stk.pop();
            auto first = stk.top();
            stk.pop();

            if (s == "+") {
                stk.push(first + second);
            } else if (s == "-") {
                stk.push(first - second);
            } else if (s == "*") {
                stk.push(first * second);
            } else {
                stk.push(first / second);
            }
        } else {
            stk.push(std::stold(s));
        }
    }

    return stk.top();
}
