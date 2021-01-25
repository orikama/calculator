#pragma once

#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <list>


namespace calc::ast
{

struct Nil{};
struct Unary;
struct Expression;

struct Operand : boost::spirit::x3::variant<
    Nil
    , double
    , boost::spirit::x3::forward_ast<Unary>
    , boost::spirit::x3::forward_ast<Expression>>
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

} // namespace calc::ast

BOOST_FUSION_ADAPT_STRUCT(calc::ast::Unary, operator_, operand_)
BOOST_FUSION_ADAPT_STRUCT(calc::ast::Binary, operator_, operand_)
BOOST_FUSION_ADAPT_STRUCT(calc::ast::Expression, first, rest)
