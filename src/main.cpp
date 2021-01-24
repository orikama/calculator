#include <boost/spirit/home/x3.hpp>

#include <iostream>
#include <string>


namespace x3 = boost::spirit::x3;


template<typename Iterator>
bool parse_numbers(Iterator begin, const Iterator end)
{
    auto print_int_attr = [](auto &ctx) { std::cout << "\tInt attr: " << x3::_attr(ctx) << std::endl; };
    auto print_double_attr = [](auto &ctx) { std::cout << "\tDouble attr: " << x3::_attr(ctx) << std::endl; };

    x3::real_parser<double, x3::strict_real_policies<double>> strict_double;
    auto number = strict_double[print_double_attr] | x3::int_[print_int_attr];

    bool succedeed = x3::phrase_parse(
        begin, end,
        number >> *(',' >> number),
        x3::ascii::space
    );

    if (succedeed && begin == end) {
        return true;
    }

    return false;
}


int main()
{
    std::string input;
    std::getline(std::cin, input);

    if (parse_numbers(input.cbegin(), input.cend())) {
        std::cout << "Parsing succeeded\n";
    }
    else {
        std::cout << "Parsing failed\n";
    }

    return 0;
}
