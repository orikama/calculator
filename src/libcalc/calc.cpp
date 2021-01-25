#include <libcalc/calc.hpp>

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <list>
#include <numeric>


namespace x3 = boost::spirit::x3;


namespace ast
{

struct Nil{};
struct Unary;
struct Expression;

struct Operand : x3::variant<
                Nil
                , double
                , x3::forward_ast<Unary>
                , x3::forward_ast<Expression>>
{
    using base_type::base_type;
    using base_type::operator=;
};

struct Unary
{
    char operator_;
    Operand operand_;
};

struct Binary
{
    char operator_;
    Operand operand_;
};

struct Expression
{
    Operand first;
    std::list<Binary> rest;
};

} // namespace ast

BOOST_FUSION_ADAPT_STRUCT(ast::Unary, operator_, operand_)
BOOST_FUSION_ADAPT_STRUCT(ast::Binary, operator_, operand_)
BOOST_FUSION_ADAPT_STRUCT(ast::Expression, first, rest)


namespace ast
{

struct eval
{
    double operator()(Nil) const
    {
        BOOST_ASSERT(0);
        return 0;
    }

    double operator()(double d) const
    {
        return d;
    }

    double operator()(double lhs, const Binary &b) const
    {
        double rhs = boost::apply_visitor(*this, b.operand_);
        switch (b.operator_)
        {
            case '+': return lhs + rhs;
            case '-': return lhs - rhs;
            case '*': return lhs * rhs;
            case '/': return lhs / rhs;
        }
        BOOST_ASSERT(0);
        return 0;
    }

    double operator()(const Unary &u) const
    {
        double rhs = boost::apply_visitor(*this, u.operand_);
        switch (u.operator_)
        {
            case '-': return -rhs;
            case '+': return +rhs;
        }
        BOOST_ASSERT(0);
        return 0;
    }

    double operator()(const Expression &e) const
    {
        return std::accumulate(e.rest.begin(), e.rest.end(),
            boost::apply_visitor(*this, e.first), *this
        );
    }
};

} // namespace ast


namespace grammar
{

    template<typename T>
    struct real_policy : x3::real_policies<T>
    {
        template <typename Iterator>
        static bool
        parse_dot(Iterator& first, const Iterator &last)
        {
            if (first == last || (*first != '.' && *first != ',')) {
                return false;
            }
            ++first;
            return true;
        }
    };

    x3::real_parser<double, real_policy<double>> real_;


    const x3::rule<class additive_expression_t,         ast::Expression> additive_expression{"additive_expression"};
    const x3::rule<class multiplicative_expression_t,   ast::Expression> multiplicative_expression{"multiplicative_expression"};
    const x3::rule<class unary_expression_t,            ast::Operand> unary_expression{"unary_expression"};
    const x3::rule<class primary_expression_t,          ast::Operand> primary_expression{"primary_expression"};

    const auto additive_expression_def =
        multiplicative_expression
        >> *(   (x3::char_('+') >> multiplicative_expression)
            |   (x3::char_('-') >> multiplicative_expression)
            )
        ;
    const auto multiplicative_expression_def =
        unary_expression
        >> *(   (x3::char_('*') >> unary_expression)
            |   (x3::char_('/') >> unary_expression)
            )
        ;
    const auto unary_expression_def =
            primary_expression
        |   (x3::char_('-') >> unary_expression)
        |   (x3::char_('+') >> unary_expression)
        ;
    const auto primary_expression_def =
            real_
        |   '(' >> additive_expression >> ')'
        ;

    BOOST_SPIRIT_DEFINE(
        additive_expression, multiplicative_expression, unary_expression, primary_expression
    );

} // namespace grammar


namespace calc
{

std::optional<double>
evaluate(std::string_view expression)
{
    ast::Expression result;
    auto begin = expression.cbegin();
    auto end = expression.cend();

    bool succeeded = x3::phrase_parse(begin, end, grammar::additive_expression, x3::space, result);

    if (succeeded && begin == end) {
        ast::eval calculator;
        return calculator(result);
    }

    return {};
}

} // namespace calc
