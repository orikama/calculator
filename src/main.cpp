#include <boost/spirit/home/x3.hpp>

#include <iostream>
#include <string>


namespace x3 = boost::spirit::x3;


namespace calculator
{
    const x3::rule<class expression> expression{"expression"};
    const x3::rule<class term> term{"term"};
    const x3::rule<class factor> factor{"factor"};

    const auto expression_def = term >> *( ('+' >> term) | ('-' >> term) );
    const auto term_def = factor >> *( ('*' >> factor) | ('/' >> factor) );
    const auto factor_def =
        x3::uint_
        | '(' >> expression >> ')'
        | ('-' >> factor)
        | ('+' >> factor)
        ;

    BOOST_SPIRIT_DEFINE(expression, term, factor);

    bool parse(std::string::const_iterator begin, std::string::const_iterator end)
    {
        bool succeeded = x3::phrase_parse(begin, end, expression, x3::space);

        if (succeeded && begin == end) {
            return true;
        }

        return false;
    }
}


int main()
{
    std::string input;
    std::getline(std::cin, input);

    if (calculator::parse(input.begin(), input.end())) {
        std::cout << "Parsing succeeded\n";
    }
    else {
        std::cout << "Parsing failed\n";
    }

    return 0;
}
