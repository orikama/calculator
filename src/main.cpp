#include <boost/spirit/home/x3.hpp>

#include <iostream>
#include <optional>
#include <string>


namespace x3 = boost::spirit::x3;


template<typename Iterator>
std::optional<double> adder(Iterator begin, const Iterator end)
{
    double sum = 0.0;

    auto assign = [&sum](auto &ctx) { sum = x3::_attr(ctx); };
    auto add = [&sum](auto &ctx) { sum += x3::_attr(ctx); };

    bool succedeed = x3::phrase_parse(
        begin, end,
        x3::double_[assign] >> *(',' >>  x3::double_[add]),
        x3::ascii::space
    );

    if (succedeed && begin == end) {
        return sum;
    }

    return {};
}


int main()
{
    std::string input;
    std::getline(std::cin, input);

    if (const auto sum = adder(input.cbegin(), input.cend())) {
        std::cout << "Parsing succeeded\n"
            << "\tSum=" << sum.value() << '\n';
    }
    else {
        std::cout << "Parsing failed\n";
    }

    return 0;
}
