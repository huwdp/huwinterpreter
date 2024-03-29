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

#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "../errors/debug.h"
#include "../types/typedetector.h"
#include "tokenlist.h"
#include "token.h"
#include "tokenmanager.h"
#include "unusabletokenlist.h"
#include "tokenlist.h"

#include <set>

namespace HuwInterpreter {
    namespace Tokens {
        class Scanner
        {
        private:
            std::shared_ptr<UnusableTokenList> unusableTokenManager;
            std::shared_ptr<TokenList> tokenManager;
            std::vector<std::shared_ptr<Token>> items;
            bool isAllowedCharacter(char character);
            void AddToken(Types::TokenType tokenType,
                          std::shared_ptr<LineInfo> lineInfo);
            void AddToken(std::string text,
                          Types::TokenType tokenType,
                          std::shared_ptr<LineInfo> lineInfo);
        public:
            Scanner();
            std::vector<std::shared_ptr<Token>> tokenize(std::shared_ptr<TokenManager> fileReader);
        };
    }
}

#endif // SCANNER_H
