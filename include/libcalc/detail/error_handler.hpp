#pragma once

#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>
#include <boost/spirit/home/x3/auxiliary.hpp> // error_handler_result


namespace calc::grammar
{

struct error_handler
{
    template <typename Iterator, typename Exception, typename Context>
    boost::spirit::x3::error_handler_result
    on_error(Iterator& first, Iterator const& last, Exception const& x, Context const& context)
    {
        auto &error_handler = boost::spirit::x3::get<boost::spirit::x3::error_handler_tag>(context).get();
        std::string message = "Error! Expecting: " + x.which() + " here:";
        error_handler(x.where(), message);

        return boost::spirit::x3::error_handler_result::fail;
    }
};

} // namespace calc::grammar
