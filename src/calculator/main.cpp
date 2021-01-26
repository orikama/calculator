#include <libcalc/calc.hpp>

#include <iostream>
#include <string>


int main()
{
    std::string input;
    std::getline(std::cin, input);

    if (const auto result = calc::evaluate(input)) {
        std::cout << "Result = " << result.value() << std::endl;
    }
    else {
        std::cout << "Parsing failed\n";
    }

    return 0;
}
