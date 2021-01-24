#include <libcalc/calc.hpp>

#include <iostream>


int main()
{
    std::string input;
    std::getline(std::cin, input);

    if (const auto result = calc::evaluate(input.begin(), input.end())) {
        std::cout << "Evaluation succeeded\n"
            << "\tResult=" << result.value() << std::endl;
    }
    else {
        std::cout << "Parsing failed\n";
    }

    return 0;
}
