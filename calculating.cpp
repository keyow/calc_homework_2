#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include <cmath>

long double calculate(std::vector<std::string>& postfix_expr) {
    std::stack<long double> stk;

    for (const std::string& s : postfix_expr) {
        if (s == "sin") {
            auto number = stk.top();
            stk.pop();
            stk.push(sin(number));
        } else if (s == "cos") {
            auto number = stk.top();
            stk.pop();
            stk.push(cos(number));
        } else if (s == "tg") {
            auto number = stk.top();
            stk.pop();
            stk.push(tan(number));
        } else if (s == "ctg") {
            auto number = stk.top();
            stk.pop();
            stk.push(1 / tan(number));
        } else if (s == "exp") {
            auto number = stk.top();
            stk.pop();
            stk.push(exp(number));
        } else if (s == "+" || s == "-" || s == "*" || s == "/") {
            auto second_number = stk.top();
            stk.pop();
            auto first_number = stk.top();
            stk.pop();

            if (s == "+") {
                stk.push(first_number + second_number);
            } else if (s == "-") {
                stk.push(first_number - second_number);
            } else if (s == "*") {
                stk.push(first_number * second_number);
            } else {
                stk.push(first_number / second_number);
            }
        } else {
            stk.push(std::stold(s));
        }
    }

    return stk.top();
}
