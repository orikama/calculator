#include <libcalc/calc.hpp>

#include <iostream>
#include <iomanip>
#include <string>


int main()
{
    std::string input;
    std::getline(std::cin, input);

    if (const auto result = calc::evaluate(input)) {
        std::cout << std::fixed << std::setprecision(2) << "Result = " << result.value() << std::endl;
    }
    else {
        std::cout << "Parsing failed\n";
    }

    return 0;
}
