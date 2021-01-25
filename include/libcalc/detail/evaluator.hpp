#pragma once

#include <libcalc/detail/ast.hpp>


namespace calc::ast
{

struct Evaluator
{
    double operator()(Nil) const;
    double operator()(double d) const;
    double operator()(double left, const Binary &b) const;
    double operator()(const Unary &u) const;
    double operator()(const Expression &e) const;
};

} // namespace calc::ast
