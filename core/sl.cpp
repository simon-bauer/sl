#include "sl.h"

namespace sl
{
    using std::cout;
    using std::cin;
    using std::endl;
    using std::string;
    using std::begin;
    using std::end;
    using std::ostream;
    using std::list;
    using std::runtime_error;
    using std::variant; 
    using std::visit;

    ostream& operator<<(ostream& os, const Expression& e)
    {
        visit([&](const auto& t){os << t;}, e.value);
        return os;
    }
    
    
    ostream& operator<<(ostream& os, const List& l)
    {
        os << "( ";
        for (const auto& sub_expression : l)
        {
            os << sub_expression << " "; 
        }
        return os << ")";
    }
    
    
    ostream& operator<<(ostream& os, const Symbol& s)
    {
        return os << s.value;
    }
    

    ostream& operator<<(ostream& os, const Function& f)
    {
        return os << "function";
    }
    
    
    
    Environment default_environment()
    {
        Environment env{
        {
            {Symbol{"+"}, Expression{sum}},
            {Symbol{"-"}, Expression{subtract}} 
        }};
        
        return env;
        
    }
    
        
    
    
    Expression apply(const Function& function, const List& arguments)
    {
        return function(arguments);
    }
    
    Expression eval(Expression& input, const Environment& env)
    {            
        if (is_type<Symbol>(input))
        {
            return env.at(get<Symbol>(input));
        }    
        else if (is_type<List>(input))
        {
            List& list_expression = get<List>(input);
            auto functionExpression = eval(list_expression.front());
            if (!is_type<Function>(functionExpression))
            {
                throw runtime_error("First item in list must be a function.");
            }
            auto function = get<Function>(functionExpression);
            
            list_expression.pop_front();
            List arguments{};
            for (auto subexpression : list_expression)
            {
                arguments.push_back(eval(subexpression));
            }
            return sl::apply(function, arguments);
        }
        else
        {
            return input;
        }
    }
    
    Expression sum(const List& arguments)
    {
        int sum{0};
        for (const auto& arg : arguments) 
        {
            if(!is_type<int>(arg)) 
            {
                throw runtime_error("arguments must be integers");
            }
            sum += get<int>(arg.value);
        }
        Expression result;
        result.value = sum;
        return result;
    }
    
    Expression subtract(const List& arguments)
    {
        if (arguments.size() == 1)
        {
            auto a = arguments.front();
            if (!is_type<int>(a))
            {
                throw runtime_error("arguments must be integers");
            }
            auto result = get<int>(a.value);
            result = -result;
            return Expression{result};
        }
        else
        {
            throw runtime_error("not implemented yet");
        }
            
    }
}

