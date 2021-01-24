#include <libcalc/calc.hpp>

#include <boost/spirit/home/x3.hpp>


namespace x3 = boost::spirit::x3;


namespace
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

    const auto zero = [](auto &ctx){ x3::_val(ctx) = 0; };
    const auto mov = [](auto &ctx){ x3::_val(ctx) = x3::_attr(ctx); };
    const auto add = [](auto &ctx){ x3::_val(ctx) += x3::_attr(ctx); };
    const auto sub = [](auto &ctx){ x3::_val(ctx) -= x3::_attr(ctx); };
    const auto mul = [](auto &ctx){ x3::_val(ctx) *= x3::_attr(ctx); };
    const auto div = [](auto &ctx){ x3::_val(ctx) /= x3::_attr(ctx); };
    const auto neg = [](auto &ctx){ x3::_val(ctx) = -x3::_attr(ctx); };

    const x3::rule<class ariphmetic_expression, double> ariphmetic_expression{"ariphmetic_expression"};
    const x3::rule<class multiplicative,        double> multiplicative{"multiplicative"};
    const x3::rule<class additive,              double> additive{"additive"};
    const x3::rule<class unary,                 double> unary{"unary"};
    const x3::rule<class primary,               double> primary{"primary"};

    const auto ariphmetic_expression_def =
        x3::eps[zero]
        >> additive[mov]
        ;
    const auto additive_def =
        multiplicative[mov]
        >> *( (x3::char_('+') >> multiplicative[add])
            | (x3::char_('-') >> multiplicative[sub])
            )
        ;
    const auto multiplicative_def =
        unary[mov]
        >> *( (x3::char_('*') >> unary[mul])
            | (x3::char_('/') >> unary[div])
            )
        ;
    const auto unary_def =
            primary[mov]
        |   (x3::char_('-') >> primary[neg])
        |   (x3::char_('+') >> primary[mov])
        ;
    const auto primary_def =
            real_[mov]
        |   x3::char_('(') >> additive[mov] >> x3::char_(')')
        ;

    BOOST_SPIRIT_DEFINE(ariphmetic_expression, multiplicative, additive, unary, primary);
} // namespace


namespace calc
{

std::optional<double>
evaluate(std::string_view expression)
{
    double result;
    auto begin = expression.cbegin();
    auto end = expression.cend();

    bool succeeded = x3::phrase_parse(begin, end, ariphmetic_expression, x3::space, result);

    if (succeeded && begin == end) {
        return result;
    }

    return {};
}

} // namespace calc
