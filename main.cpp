#include "header.h"

int main() {
    std::string expression;

    std::cout << "Enter the expression:" << std::endl;
    std::getline(std::cin, expression);

    std::vector<std::string> postfix_expression = inToPost(parse(expression));

    std::cout << calculate(postfix_expression);
    return 0;
}
