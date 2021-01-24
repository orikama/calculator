#pragma once

#include <optional>
#include <string>


namespace calc
{

std::optional<double>
evaluate(std::string::const_iterator begin, std::string::const_iterator end);

} // namespace calc
