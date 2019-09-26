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

#include "unusabletokens.h"

namespace HuwInterpreter {
    namespace Tokens {
        UnusableTokens::UnusableTokens()
        {
            init();
            tokens = std::make_shared<Tokens>();
        }

        void UnusableTokens::init()
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

        bool UnusableTokens::tokenExists(Types::TokenType tokenType)
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

        bool UnusableTokens::exists(std::string value)
        {
            return tokenExists(tokens->get(value));
        }

        bool UnusableTokens::exists(char value)
        {
            std::stringstream ss;
            std::string temp;
            ss << value;
            ss >> temp;
            return exists(temp);
        }

        void UnusableTokens::add(Types::TokenType tokenType)
        {
            if (!exists(tokenType))
            {
                items.emplace_back(tokenType);
            }
        }
    }
}
