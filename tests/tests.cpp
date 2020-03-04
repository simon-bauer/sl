#include "../core/sl.h"
#include "../core/Reader.h"
#include "catch.hpp"

using std::list;
using std::string;
using std::make_shared;
using std::dynamic_pointer_cast;
using std::get;
using namespace sl;


TEST_CASE("replace")
{
    REQUIRE("afcde" == replace("abcde", "b", "f"));
    REQUIRE("abcdf" == replace("abcde", "e", "f"));
    REQUIRE(" ( )" == replace("()", "(", " ( "));
}

TEST_CASE("read and eval Number")
{
    string input = "3";
    Expression initial_expression = read(input);
    int result = get<int>(eval(initial_expression).value);
    REQUIRE(result == 3);
}


TEST_CASE("read and eval list")
{
    string input = "(+ 2 1)";
    Expression initial_expression = read(input);
    int result = get<int>(eval(initial_expression).value);
    REQUIRE(result == 3);
}

TEST_CASE("read and eval nested list")
{
    string input = "(+ 2 (+ 1 1))";
    Expression initial_expression = read(input);
    int result = get<int>(eval(initial_expression).value);
    REQUIRE(result == 4);
}

