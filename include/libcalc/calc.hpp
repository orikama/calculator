#pragma once

#include <optional>
#include <string_view>


namespace calc
{

std::optional<double> evaluate(std::string_view expression);

} // namespace calc
