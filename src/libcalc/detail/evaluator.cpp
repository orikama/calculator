#include <libcalc/detail/evaluator.hpp>

#include <numeric>


namespace calc::ast
{

double Evaluator::operator()(Nil) const
{
    BOOST_ASSERT(0);
    return 0;
}

double Evaluator::operator()(double d) const
{
    return d;
}

double Evaluator::operator()(double left, const Binary &b) const
{
    double right = boost::apply_visitor(*this, b.operand_);
    switch (b.operator_)
    {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return left / right;
    }
    BOOST_ASSERT(0);
    return 0;
}

double Evaluator::operator()(const Unary &u) const
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

double Evaluator::operator()(const Expression &e) const
{
    return std::accumulate(e.rest.begin(), e.rest.end(),
        boost::apply_visitor(*this, e.first), *this
    );
}

} // namespace calc::ast
