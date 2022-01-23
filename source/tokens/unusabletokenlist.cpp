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

#include "unusabletokenlist.h"

namespace HuwInterpreter {
    namespace Tokens {
        UnusableTokenList::UnusableTokenList()
        {
            init();
            tokenManager = std::make_shared<TokenList>();
        }

        void UnusableTokenList::init()
        {
            items.clear();
            items.emplace_back(Types::RIGHTPARENTHESIS);
            items.emplace_back(Types::LEFTPARENTHESIS);
            items.emplace_back(Types::MULTIPLICATION);
            items.emplace_back(Types::DIVISION);
            items.emplace_back(Types::SUBTRACTION);
            items.emplace_back(Types::MOD);
            items.emplace_back(Types::EQUALS);
            items.emplace_back(Types::IFEQUALS);
            items.emplace_back(Types::IFNOTEQUALS);
            items.emplace_back(Types::IFLESSTHAN);
            items.emplace_back(Types::IFLESSTHANOREQUAL);
            items.emplace_back(Types::IFGREATER);
            items.emplace_back(Types::IFGREATERTHANOREQUAL);
            items.emplace_back(Types::LEFTBRACKET);
            items.emplace_back(Types::RIGHTBRACKET);
            items.emplace_back(Types::SEMICOLON);
            items.emplace_back(Types::COMMA);
            items.emplace_back(Types::QUOTE);
            items.emplace_back(Types::NOT);
            items.emplace_back(Types::LEFTPARENTHESIS);
            items.emplace_back(Types::MULTIPLICATION);
            items.emplace_back(Types::DIVISION);
            items.emplace_back(Types::ADDITION);
            items.emplace_back(Types::AND);
            items.emplace_back(Types::OR);
            items.emplace_back(Types::BITWISEAND);
            items.emplace_back(Types::BITWISEOR);
            items.emplace_back(Types::BITWISEXOR);
            items.emplace_back(Types::DOT);
            items.emplace_back(Types::MULTIPLICATIONEQUAL);
            items.emplace_back(Types::DIVISIONEQUAL);
            items.emplace_back(Types::ADDITIONEQUAL);
            items.emplace_back(Types::SUBTRACTIONEQUAL);
            items.emplace_back(Types::INCREMENT);
            items.emplace_back(Types::DECREMENT);
            items.emplace_back(Types::BITWISECOMPLEMENT);
            items.emplace_back(Types::LEFTSHIFT);
            items.emplace_back(Types::LEFTSQUAREBRACKET);
            items.emplace_back(Types::RIGHTSQUAREBRACKET);
        }

        bool UnusableTokenList::fastTokenExists(Types::TokenType tokenType)
        {
            if (tokenType == Types::RIGHTPARENTHESIS) { return true; }
            if (tokenType == Types::LEFTPARENTHESIS) { return true; }
            if (tokenType == Types::MULTIPLICATION) { return true; }
            if (tokenType == Types::DIVISION) { return true; }
            if (tokenType == Types::SUBTRACTION) { return true; }
            if (tokenType == Types::MOD) { return true; }
            if (tokenType == Types::EQUALS) { return true; }
            if (tokenType == Types::IFEQUALS) { return true; }
            if (tokenType == Types::IFNOTEQUALS) { return true; }
            if (tokenType == Types::IFLESSTHAN) { return true; }
            if (tokenType == Types::IFLESSTHANOREQUAL) { return true; }
            if (tokenType == Types::IFGREATER) { return true; }
            if (tokenType == Types::IFGREATERTHANOREQUAL) { return true; }
            if (tokenType == Types::LEFTBRACKET) { return true; }
            if (tokenType == Types::RIGHTBRACKET) { return true; }
            if (tokenType == Types::SEMICOLON) { return true; }
            if (tokenType == Types::COMMA) { return true; }
            if (tokenType == Types::QUOTE) { return true; }
            if (tokenType == Types::NOT) { return true; }
            if (tokenType == Types::LEFTPARENTHESIS) { return true; }
            if (tokenType == Types::MULTIPLICATION) { return true; }
            if (tokenType == Types::DIVISION) { return true; }
            if (tokenType == Types::ADDITION) { return true; }
            if (tokenType == Types::AND) { return true; }
            if (tokenType == Types::OR) { return true; }
            if (tokenType == Types::BITWISEAND) { return true; }
            if (tokenType == Types::BITWISEOR) { return true; }
            if (tokenType == Types::BITWISEXOR) { return true; }
            if (tokenType == Types::DOT) { return true; }
            if (tokenType == Types::MULTIPLICATIONEQUAL) { return true; }
            if (tokenType == Types::DIVISIONEQUAL) { return true; }
            if (tokenType == Types::ADDITIONEQUAL) { return true; }
            if (tokenType == Types::SUBTRACTIONEQUAL) { return true; }
            if (tokenType == Types::INCREMENT) { return true; }
            if (tokenType == Types::DECREMENT) { return true; }
            if (tokenType == Types::BITWISECOMPLEMENT) { return true; }
            if (tokenType == Types::LEFTSHIFT) { return true; }
            if (tokenType == Types::LEFTSQUAREBRACKET) { return true; }
            if (tokenType == Types::RIGHTSQUAREBRACKET) { return true; }
            return tokenExists(tokenType);
        }

        bool UnusableTokenList::tokenExists(Types::TokenType tokenType)
        {
            for (std::vector<Types::TokenType>::iterator it = items.begin(); it != items.end(); ++it)
            {
                if ((*it) == tokenType)
                {
                    return true;
                }
            }
            return false;
        }

        bool UnusableTokenList::exists(std::string value)
        {
            // Optimisation so we skip hashtable lookup.
            if (value == ")") { return true; }
            if (value == "(") { return true; }
            if (value == "*") { return true; }
            if (value == "/") { return true; }
            if (value == "-") { return true; }
            if (value == "%") { return true; }
            if (value == "=") { return true; }
            if (value == "==") { return true; }
            if (value == "!=") { return true; }
            if (value == "<") { return true; }
            if (value == "<=") { return true; }
            if (value == ">") { return true; }
            if (value == ">=") { return true; }
            if (value == "{") { return true; }
            if (value == "}") { return true; }
            if (value == ";") { return true; }
            if (value == ",") { return true; }
            if (value == "\"") { return true; }
            if (value == ".") { return true; }
            if (value == "!") { return true; }
            if (value == "+") { return true; }
            if (value == "&") { return true; }
            if (value == "|") { return true; }
            if (value == "&&") { return true; }
            if (value == "||") { return true; }
            if (value == "*=") { return true; }
            if (value == "/=") { return true; }
            if (value == "+=") { return true; }
            if (value == "-=") { return true; }
            if (value == "++") { return true; }
            if (value == "--") { return true; }
            if (value == "\t") { return true; }
            if (value == " ") { return true; }
            if (value == "^") { return true; }
            if (value == "~") { return true; }
            if (value == "[") { return true; }
            if (value == "]") { return true; }
            return tokenExists(tokenManager->get(value));
        }

        bool UnusableTokenList::exists(char value)
        {
            // Optimisation so we skip hashtable lookup.
            if (value == ')') { return true; }
            if (value == '(') { return true; }
            if (value == '*') { return true; }
            if (value == '/') { return true; }
            if (value == '-') { return true; }
            if (value == '%') { return true; }
            if (value == '=') { return true; }
            if (value == '<') { return true; }
            if (value == '>') { return true; }
            if (value == '{') { return true; }
            if (value == '}') { return true; }
            if (value == ';') { return true; }
            if (value == ',') { return true; }
            if (value == '\'') { return true; }
            if (value == '.') { return true; }
            if (value == '!') { return true; }
            if (value == '+') { return true; }
            if (value == '&') { return true; }
            if (value == '|') { return true; }
            if (value == ' ') { return true; }
            if (value == '^') { return true; }
            if (value == '~') { return true; }
            if (value == '[') { return true; }
            if (value == ']') { return true; }
            std::stringstream ss;
            std::string temp;
            ss << value;
            ss >> temp;
            return exists(temp);
        }

        void UnusableTokenList::add(Types::TokenType tokenType)
        {
            if (!exists(tokenType))
            {
                items.emplace_back(tokenType);
            }
        }
    }
}
