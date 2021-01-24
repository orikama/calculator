#include <boost/spirit/home/x3.hpp>

#include <iostream>
#include <string>


namespace x3 = boost::spirit::x3;


template<typename Iterator>
bool parse_numbers(Iterator begin, const Iterator end)
{
    bool succedeed = x3::phrase_parse(
        begin, end,
        x3::double_ >> *(',' >> x3::double_),
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
