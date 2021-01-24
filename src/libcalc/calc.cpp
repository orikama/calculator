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

    const x3::rule<class expression, double> expression{"expression"};
    const x3::rule<class term, double> term{"term"};
    const x3::rule<class factor, double> factor{"factor"};

    const auto zero = [](auto &ctx){ x3::_val(ctx) = 0; };
    const auto mov = [](auto &ctx){ x3::_val(ctx) = x3::_attr(ctx); };
    const auto add = [](auto &ctx){ x3::_val(ctx) += x3::_attr(ctx); };
    const auto sub = [](auto &ctx){ x3::_val(ctx) -= x3::_attr(ctx); };
    const auto mul = [](auto &ctx){ x3::_val(ctx) *= x3::_attr(ctx); };
    const auto div = [](auto &ctx){ x3::_val(ctx) /= x3::_attr(ctx); };
    const auto neg = [](auto &ctx){ x3::_val(ctx) = -x3::_attr(ctx); };

    const auto expression_def =
        x3::eps[zero]
        >> term[mov]
        >> *( ('+' >> term[add])
            | ('-' >> term[sub])
        );
    const auto term_def =
        factor[mov]
        >> *( ('*' >> factor[mul])
            | ('/' >> factor[div])
        );
    const auto factor_def =
        real_[mov]
        | '(' >> expression[mov] >> ')'
        | ('-' >> factor[neg])
        | ('+' >> factor[mov])
        ;

    BOOST_SPIRIT_DEFINE(expression, term, factor);
} // namespace


namespace calc
{

std::optional<double>
evaluate(std::string::const_iterator begin, std::string::const_iterator end)
{
    double result;
    bool succeeded = x3::phrase_parse(begin, end, expression, x3::space, result);

    if (succeeded && begin == end) {
        return result;
    }

    return {};
}

} // namespace calc
