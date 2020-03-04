#include "Reader.h"
#include <sstream>

namespace sl
{
    using std::cout;
    using std::cin;
    using std::string;
    using std::shared_ptr;
    using std::ostream;
    using std::istringstream;
    using std::stringstream;
    using std::getline;
    using std::list;
    using std::make_shared;
    using std::runtime_error;
    using std::variant; 
    
    ostream& operator<<(ostream& os, list<string> v)
    {
        for (const auto& e : v)
        {
            os << "[" << e << "] ";
        }
        return os;
    }
    
    
    list<string> split(const string& wholeString, char delimiter)
    {
        list<string> tokens;
        string token;
        istringstream tokenStream(wholeString);
        while (getline(tokenStream, token, delimiter))
        {
            if (!token.empty())
            {
                tokens.push_back(token);
            }
        }
        return tokens;
    }
    
    
    string replace(const string text, const string& to_find, const string& to_replace)
    {
        stringstream new_text;
        string::size_type current_search_position{0};
        string::size_type current_found_position{0};
        while((current_found_position = text.find(to_find, current_search_position))
            != string::npos)
        {
            new_text << text.substr(current_search_position, current_found_position - current_search_position);
            new_text << to_replace;
            current_search_position = current_found_position + 1;
        }
        
        if (current_search_position == 0)
        {
            new_text << text;
        }
        else if (current_search_position < text.size())
        {
            new_text << text.substr(current_search_position);
        }
        
        return new_text.str();
    }
    
    
    list<string> tokenize(const string& wholeString)
    {
        string bracesReplaced = replace(wholeString, "(", " ( ");
        bracesReplaced = replace(bracesReplaced, ")", " ) ");
        return split(bracesReplaced, ' ');
    }
    
    
    Expression read_from_tokens(list<string>& tokens)
    {       
        if (tokens.empty())
        {
            throw runtime_error("empty token list");
        }
        string token = tokens.front();
        tokens.pop_front();
        
        if (token == "(")
        {
            Expression expression_list{list<Expression>()};
            while (tokens.front() != ")")
            {
                get<List>(expression_list).push_back(read_from_tokens(tokens));
            } 
            tokens.pop_front(); // pop ")"
            return expression_list; 
        }
        else if (token == "+" || token == "-")
        {
            return Expression{Symbol{token}};
        }
        else
        {
            return Expression{std::stoi(token)};
        }
    }
    
    Expression read()
    {
        cout << "sl> ";
        string input;
        getline(cin, input);
        return read(input);
    }
    
    Expression read(string input)
    {
        auto tokens = tokenize(input);
        return read_from_tokens(tokens);
    }
    
}

