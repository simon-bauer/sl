#include <iostream>
#include "../core/sl.h"
#include "../core/Reader.h"

namespace sl
{
    void repl()
    {
        while(1)
        {
            Expression initial_expression = sl::read();
            std::cout << eval(initial_expression) << std::endl;
        }
    }
}

 
int main(int argc, char **argv)
{
    sl::repl(); 
}

