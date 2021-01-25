#include <libcalc/calc.hpp>
#include <libcalc/detail/evaluator.hpp>
#include <libcalc/detail/grammar.hpp>


namespace x3 = boost::spirit::x3;


namespace calc
{

std::optional<double> evaluate(std::string_view expression)
{
    auto begin = expression.cbegin();
    auto end = expression.cend();

    ast::Expression result_ast;
    bool succeeded = x3::phrase_parse(begin, end, grammar::additive_expression, x3::space, result_ast);

    if (succeeded && begin == end) {
        ast::Evaluator calculator;
        return calculator(result_ast);
    }

    return {};
}

} // namespace calc
