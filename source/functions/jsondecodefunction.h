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

#ifndef JSONDECODEFUNCTION_H
#define JSONDECODEFUNCTION_H

#include "function.h"
#include "variables/hashtablevariable.h"
#include "variables/doublevariable.h"
#include "variables/variabletypefactory.h"

namespace HuwInterpreter {
    namespace Functions {
        class JSONDecodeFunction : public Function
        {
        private:
            std::string::iterator it;
            std::string::iterator end;
            std::string text = "";
            void next();
            std::shared_ptr<Variable> parseJSON(std::string text, std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> parseJSONObject(std::shared_ptr<Tokens::Token> token);
            bool accept(char expected);
            void acceptIndentation();
            std::shared_ptr<Variable> getValue();
        public:
            JSONDecodeFunction(std::shared_ptr<HuwInterpreter::Passable> passable);
            virtual ~JSONDecodeFunction() {}
            std::shared_ptr<Variable> execute(std::shared_ptr<Tokens::Token> token,
                                          std::shared_ptr<Variables::Scope> globalScope,
                                          std::shared_ptr<Variables::Scope> scope,
                                          std::vector<std::shared_ptr<Nodes::Node>> arguments);

        };
    }
}

#endif // JSONDECODEFUNCTION_H
