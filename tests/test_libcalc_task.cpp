#include <libcalc/calc.hpp>

#include <boost/test/unit_test.hpp>

#include <utility>


BOOST_AUTO_TEST_SUITE( libcalc )

BOOST_AUTO_TEST_CASE( libcalc_evaluate_tasks )
{
    const auto task_expressions = {
        std::make_pair(1, "-1 + 5 - 3"),
        std::make_pair(8, "-10 + (8 * 2.5) - (3 / 1,5)"),
        std::make_pair(11, "1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)")
    };

    for (auto &[expected_result, expression]: task_expressions) {
        const auto result = calc::evaluate(expression);
        BOOST_CHECK(result.has_value());
        BOOST_CHECK_EQUAL(expected_result, result.value());
    }

    const auto invalid_task_expression = "1.1 + 2.1 + abc";
    const auto invalid_result = calc::evaluate(invalid_task_expression);
    BOOST_CHECK_EQUAL(false, invalid_result.has_value());
}

BOOST_AUTO_TEST_CASE( libcalc_evaluate_LOOOOOOOOOOOOOOOOL )
{
    const std::initializer_list<std::pair<double, const char*>> expressions = {
        std::make_pair(13578619, "13578619"),
        std::make_pair(13578619.765, "13578619.765"),
        std::make_pair(13578619.765, "13578619,765"),

        std::make_pair(-1, "-1"),
        std::make_pair(1, "+1"),
        std::make_pair(1, "+(1)"),
        std::make_pair(-1, "-(1)"),
        std::make_pair(-1, "+(-1)"),
        std::make_pair(-1, "-(+1)"),
        std::make_pair(1, "+(+1)"),
        std::make_pair(1, "-(-1)"),

        std::make_pair(1+2+3+4, "1+2+3+4"),
        std::make_pair(1-2-3-4, "1-2-3-4"),
        std::make_pair(1*2*3*4, "1*2*3*4"),
        std::make_pair(1./2/3/4, "1/2/3/4"),

        std::make_pair(1+2*3+4, "1+2*3+4"),
        std::make_pair((1+2)*(3+4), "(1+2)*(3+4)"),
        std::make_pair(1./2-3./4, "1/2-3/4"),
        std::make_pair(1./(2-3)/4, "1/(2-3)/4"),

        std::make_pair( ( ((1+2) * 3 - (2+5 - ( 1/0.3 + (0.4*0.3)))) ) / 2., "( ((1+2) * 3 - (2+5 - ( 1/0.3 + (0.4*0.3)))) ) / 2"),
    };

    for (auto &[expected_result, expression]: expressions) {
        const auto result = calc::evaluate(expression);
        BOOST_CHECK(result.has_value());
        BOOST_CHECK_EQUAL(expected_result, result.value());
    }
}

BOOST_AUTO_TEST_SUITE_END()
