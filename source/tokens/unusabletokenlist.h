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

#ifndef UNUSABLETOKENS_H
#define UNUSABLETOKENS_H

#include "../types/tokentypes.h"
#include "tokenlist.h"
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <memory>
#include <vector>

namespace HuwInterpreter {
    namespace Tokens {
        class UnusableTokenList
        {
        private:
            std::vector<Types::TokenType> items;
            std::shared_ptr<TokenList> tokenManager;
        public:
            UnusableTokenList();
            void init();
            bool tokenExists(Types::TokenType tokenType);
            bool fastTokenExists(Types::TokenType tokenType);
            bool exists(std::string value);
            bool exists(char value);
            void add(Types::TokenType tokenType);
        };
    }
}

#endif // UNUSABLETOKENS_H
