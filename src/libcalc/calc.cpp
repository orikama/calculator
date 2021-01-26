#include <libcalc/calc.hpp>
#include <libcalc/detail/evaluator.hpp>
#include <libcalc/detail/grammar.hpp>

#include <iostream>


namespace x3 = boost::spirit::x3;


namespace calc
{

std::optional<double> evaluate(std::string_view expression)
{
    using iterator_type = std::string_view::const_iterator;
    iterator_type begin = expression.cbegin();
    iterator_type end = expression.cend();

    x3::error_handler<iterator_type> error_handler(begin, end, std::cerr);

    auto const parser =
        x3::with<x3::error_handler_tag>(std::ref(error_handler))
        [
             grammar::additive_expression
        ];

    ast::Expression result_ast;
    bool succeeded = x3::phrase_parse(begin, end, parser, x3::space, result_ast);

    if (succeeded && begin == end) {
        ast::Evaluator calculator;
        return calculator(result_ast);
    }

    return {};
}

} // namespace calc
