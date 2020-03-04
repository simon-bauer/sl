#pragma once
 
#include <iostream>
#include <algorithm>
#include <list>
#include <exception>
#include <variant>
#include <unordered_map>
#include <functional>

namespace sl
{        
    struct Expression;
    
    struct Symbol
    {        
        bool operator==(const Symbol& other) const
        {
            return value == other.value;
        }
        
        std::string value;
    };
    
    using List = std::list<Expression>;

    using Function = std::function<Expression(const List&)>;
    
    struct Expression 
    {    
        Expression() = default;
        
        template<typename T>
        Expression(const T& initial_value)
        {
            value = initial_value;
        }
    
        std::variant<
            int, 
            std::string, 
            Symbol,
            Function,
            List
        > value;
    };
    
    template <typename T>
    T& get(Expression& e)
    {
        return std::get<T>(e.value);
    } 
    
    template <typename T>
    bool is_type(const Expression& e)
    {
        return std::holds_alternative<T>(e.value);
    }
        
    std::ostream& operator<<(std::ostream& os, const Expression& e);
    std::ostream& operator<<(std::ostream& os, const List& l);
    std::ostream& operator<<(std::ostream& os, const Symbol& s);
    std::ostream& operator<<(std::ostream& os, const Function& f);
    
    struct SymbolHash
    {
        std::size_t operator()(const Symbol& s) const noexcept
        {
            return std::hash<std::string>{}(s.value);
        }
    };
    
    
    using HashMap = std::unordered_map<Symbol, Expression, SymbolHash>;
    class Environment;
    
    class Environment
    {
    public:
        Environment(const HashMap& initialMap, Environment* outerEnvironment = nullptr)
            : outerEnvironment(outerEnvironment)
        {
            map = initialMap;
        }
        
        Expression at(const Symbol& s) const
        {
            // check if key available in map
            // look otherwise in outerEnvironment
            return map.at(s);
        }
    private:
        HashMap map;
        Environment* outerEnvironment{nullptr};
    };

    Environment default_environment();
    
    Expression apply(const Function& function, const List& arguments);
    Expression eval(Expression& input, const Environment& env = default_environment());
    
    Expression sum(const List& arguments);
    Expression subtract(const List& arguments);
}

