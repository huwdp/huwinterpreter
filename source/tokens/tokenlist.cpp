/*
    HuwInterpreter is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    HuwInterpreter is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with HuwInterpreter.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "tokenlist.h"

namespace HuwInterpreter {
    namespace Tokens {
        TokenList::TokenList()
        {
            init();
        }

        void TokenList::init()
        {
            types.clear();
            types[Types::RIGHTPARENTHESIS] = ")";
            types[Types::LEFTPARENTHESIS] = "(";
            types[Types::MULTIPLICATION] = "*";
            types[Types::DIVISION] = "/";
            types[Types::SUBTRACTION] = "-";
            types[Types::MOD] = "%";
            types[Types::EQUALS] = "=";
            types[Types::IFEQUALS] = "==";
            types[Types::IFNOTEQUALS] = "!=";
            types[Types::IFLESSTHAN] = "<";
            types[Types::IFLESSTHANOREQUAL] = "<=";
            types[Types::IFGREATER] = ">";
            types[Types::IFGREATERTHANOREQUAL] = ">=";
            types[Types::LEFTBRACKET] = "{";
            types[Types::RIGHTBRACKET] = "}";
            types[Types::SEMICOLON] = ";";
            types[Types::COMMA] = ",";
            types[Types::QUOTE] = "\"";
            types[Types::DOT] = ".";
            types[Types::NOT] = "!";
            types[Types::ADDITION] = "+";
            types[Types::BITWISEAND] = "&";
            types[Types::BITWISEOR] = "|";
            types[Types::AND] = "&&";
            types[Types::OR] = "||";
            types[Types::MULTIPLICATIONEQUAL] = "*=";
            types[Types::DIVISIONEQUAL] = "/=";
            types[Types::ADDITIONEQUAL] = "+=";
            types[Types::SUBTRACTIONEQUAL] = "-=";
            types[Types::INCREMENT] = "++";
            types[Types::DECREMENT] = "--";
            types[Types::TABINDENTATION] = "\t";
            types[Types::INDENTATION] = " ";
            types[Types::BITWISEXOR] = "^";
            types[Types::BITWISECOMPLEMENT] = "~";
            types[Types::LEFTSQUAREBRACKET] = "[";
            types[Types::RIGHTSQUAREBRACKET] = "]";
        }

        std::string TokenList::get(Types::TokenType value)
        {
            return types[value];
        }

        Types::TokenType TokenList::get(std::string value)
        {


            for (std::unordered_map<short, std::string>::iterator it = types.begin(); it != types.end(); ++it)
            {
                if (it->second == value)
                {
                    return static_cast<Types::TokenType>(it->first);
                }
            }
            return Types::WORD;
        }

        bool TokenList::fastCompare(std::string value, Types::TokenType token)
        {
            // Optimisation so we skip hashtable lookup.
            if (value == ")" && token == Types::TokenType::RIGHTPARENTHESIS) { return true; }
            if (value == "(" && token == Types::TokenType::LEFTPARENTHESIS) { return true; }
            if (value == "*" && token == Types::TokenType::MULTIPLICATION) { return true; }
            if (value == "/" && token == Types::TokenType::DIVISION) { return true; }
            if (value == "-" && token == Types::TokenType::SUBTRACTION) { return true; }
            if (value == "%" && token == Types::TokenType::MOD) { return true; }
            if (value == "=" && token == Types::TokenType::EQUALS) { return true; }
            if (value == "==" && token == Types::TokenType::IFEQUALS) { return true; }
            if (value == "!=" && token == Types::TokenType::IFNOTEQUALS) { return true; }
            if (value == "<" && token == Types::TokenType::IFLESSTHAN) { return true; }
            if (value == "<=" && token == Types::TokenType::IFLESSTHANOREQUAL) { return true; }
            if (value == ">" && token == Types::TokenType::IFGREATER) { return true; }
            if (value == ">=" && token == Types::TokenType::IFGREATERTHANOREQUAL) { return true; }
            if (value == "{" && token == Types::TokenType::LEFTBRACKET) { return true; }
            if (value == "}" && token == Types::TokenType::RIGHTBRACKET) { return true; }
            if (value == ";" && token == Types::TokenType::SEMICOLON) { return true; }
            if (value == "," && token == Types::TokenType::COMMA) { return true; }
            if (value == "\"" && token == Types::TokenType::QUOTE) { return true; }
            if (value == "." && token == Types::TokenType::DOT) { return true; }
            if (value == "!" && token == Types::TokenType::NOT) { return true; }
            if (value == "+" && token == Types::TokenType::ADDITION) { return true; }
            if (value == "&" && token == Types::TokenType::BITWISEAND) { return true; }
            if (value == "|" && token == Types::TokenType::BITWISEOR) { return true; }
            if (value == "&&" && token == Types::TokenType::AND) { return true; }
            if (value == "||" && token == Types::TokenType::OR) { return true; }
            if (value == "*=" && token == Types::TokenType::MULTIPLICATIONEQUAL) { return true; }
            if (value == "/=" && token == Types::TokenType::DIVISIONEQUAL) { return true; }
            if (value == "+=" && token == Types::TokenType::ADDITIONEQUAL) { return true; }
            if (value == "-=" && token == Types::TokenType::SUBTRACTIONEQUAL) { return true; }
            if (value == "++" && token == Types::TokenType::INCREMENT) { return true; }
            if (value == "--" && token == Types::TokenType::DECREMENT) { return true; }
            if (value == "\t" && token == Types::TokenType::TABINDENTATION) { return true; }
            if (value == " " && token == Types::TokenType::INDENTATION) { return true; }
            if (value == "^" && token == Types::TokenType::BITWISEXOR) { return true; }
            if (value == "~" && token == Types::TokenType::BITWISECOMPLEMENT) { return true; }
            if (value == "[" && token == Types::TokenType::LEFTSQUAREBRACKET) { return true; }
            if (value == "]" && token == Types::TokenType::RIGHTSQUAREBRACKET) { return true; }
            return compare(value, token);
        }

        bool TokenList::fastCompare(char value, Types::TokenType token)
        {
            // Optimisation so we skip hashtable lookup.
            if (value == ')' && token == Types::TokenType::RIGHTPARENTHESIS) { return true; }
            if (value == '(' && token == Types::TokenType::LEFTPARENTHESIS) { return true; }
            if (value == '*' && token == Types::TokenType::MULTIPLICATION) { return true; }
            if (value == '/' && token == Types::TokenType::DIVISION) { return true; }
            if (value == '-' && token == Types::TokenType::SUBTRACTION) { return true; }
            if (value == '%' && token == Types::TokenType::MOD) { return true; }
            if (value == '=' && token == Types::TokenType::EQUALS) { return true; }
            if (value == '<' && token == Types::TokenType::IFLESSTHAN) { return true; }
            if (value == '>' && token == Types::TokenType::IFGREATER) { return true; }
            if (value == '{' && token == Types::TokenType::LEFTBRACKET) { return true; }
            if (value == '}' && token == Types::TokenType::RIGHTBRACKET) { return true; }
            if (value == ';' && token == Types::TokenType::SEMICOLON) { return true; }
            if (value == ',' && token == Types::TokenType::COMMA) { return true; }
            if (value == '\'' && token == Types::TokenType::QUOTE) { return true; }
            if (value == '.' && token == Types::TokenType::DOT) { return true; }
            if (value == '!' && token == Types::TokenType::NOT) { return true; }
            if (value == '+' && token == Types::TokenType::ADDITION) { return true; }
            if (value == '&' && token == Types::TokenType::BITWISEAND) { return true; }
            if (value == '|' && token == Types::TokenType::BITWISEOR) { return true; }
            if (value == '\t' && token == Types::TokenType::TABINDENTATION) { return true; }
            if (value == ' ' && token == Types::TokenType::INDENTATION) { return true; }
            if (value == '^' && token == Types::TokenType::BITWISEXOR) { return true; }
            if (value == '~' && token == Types::TokenType::BITWISECOMPLEMENT) { return true; }
            if (value == '[' && token == Types::TokenType::LEFTSQUAREBRACKET) { return true; }
            if (value == ']' && token == Types::TokenType::RIGHTSQUAREBRACKET) { return true; }
            return compare(value, token);
        }

        bool TokenList::compare(std::string value1, Types::TokenType value)
        {
            std::unordered_map<short, std::string>::const_iterator got = types.find(value);
            if (got != types.end())
            {
                if (got->second == value1)
                {
                    return true;
                }
            }
            return false;
        }

        bool TokenList::compare(char value1, Types::TokenType value)
        {
            std::stringstream ss;
            std::string temp;
            ss << value1;
            ss >> temp;
            return compare(temp, value);
        }

        bool TokenList::exists(Types::TokenType value)
        {
            return types.find(value) != types.end();
        }

        bool TokenList::exists(std::string value)
        {
            return std::find_if(types.begin(), types.end(),
                [value](const std::unordered_map<short, std::string>::value_type& item) { return item.second == value; }) != types.end();
        }

        void TokenList::add(std::string text, Types::TokenType tokenType)
        {
            if (!exists(tokenType))
            {
                types[tokenType] = text;
            }
        }
    }
}
