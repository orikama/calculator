#pragma once

#include <libcalc/detail/ast.hpp>
#include <libcalc/detail/error_handler.hpp>

#include <boost/spirit/home/x3.hpp>


namespace calc::grammar
{

namespace x3 = boost::spirit::x3;


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


struct additive_expression_t : error_handler {};

const x3::rule<additive_expression_t,               ast::Expression> additive_expression{"additive_expression"};
const x3::rule<struct multiplicative_expression_t,  ast::Expression> multiplicative_expression{"multiplicative_expression"};
const x3::rule<struct unary_expression_t,           ast::Operand> unary_expression{"unary_expression"};
const x3::rule<struct primary_expression_t,         ast::Operand> primary_expression{"primary_expression"};

const auto additive_expression_def =
    multiplicative_expression
    >> *(   (x3::char_('+') > multiplicative_expression)
        |   (x3::char_('-') > multiplicative_expression)
        )
    ;
const auto multiplicative_expression_def =
    unary_expression
    >> *(   (x3::char_('*') > unary_expression)
        |   (x3::char_('/') > unary_expression)
        )
    ;
const auto unary_expression_def =
        primary_expression
    |   (x3::char_('-') > unary_expression)
    |   (x3::char_('+') > unary_expression)
    ;
const auto primary_expression_def =
        real_
    |   '(' > additive_expression > ')'
    ;

BOOST_SPIRIT_DEFINE(
    additive_expression, multiplicative_expression, unary_expression, primary_expression
);

} // namespace calc::grammar
