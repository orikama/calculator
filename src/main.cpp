#include <boost/spirit/include/qi.hpp>

#include <iostream>
#include <string>


namespace qi = boost::spirit::qi;


template<typename Iterator>
bool parse_numbers(Iterator begin, const Iterator end)
{
    bool succedeed = qi::phrase_parse(
        begin, end,
        qi::double_ >> *(',' >> qi::double_),
        qi::ascii::space
    );

    if (begin != end) {
        return false;
    }

    return succedeed;
}


int main()
{
    std::string input;
    std::getline(std::cin, input);

    if (parse_numbers(input.begin(), input.end())) {
        std::cout << "Parsing succeeded\n";
    }
    else {
        std::cout << "Parsing failed\n";
    }

    return 0;
}
