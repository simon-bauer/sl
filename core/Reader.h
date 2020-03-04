#pragma once
 
#include <iostream>
#include <memory>
#include <list>
#include "sl.h"

namespace sl
{
    std::ostream& operator<<(std::ostream& os, std::list<std::string> v);

    std::list<std::string> split(const std::string& wholeString, char delimiter); 
    std::string replace(const std::string text, const std::string& to_find, const std::string& to_replace);
    std::list<std::string> tokenize(const std::string& wholeString);

    Expression read_from_tokens(std::list<std::string>& tokens);
    Expression read();
    Expression read(std::string input);
}

