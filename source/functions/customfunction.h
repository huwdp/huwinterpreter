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

#ifndef CUSTOMFUNCTION_H
#define CUSTOMFUNCTION_H

#include "function.h"

namespace HuwInterpreter {
    namespace Functions {
        class CustomFunction : public Function
        {
        private:
            std::vector<std::string> arguments;
            std::shared_ptr<Nodes::Node> block;
            std::shared_ptr<Tokens::Token> token;
        public:
            CustomFunction(std::shared_ptr<HuwInterpreter::Passable> passable,
                           std::shared_ptr<Tokens::Token> token,
                           std::string name,
                           std::vector<std::string> arguments,
                           std::shared_ptr<Nodes::Node> block);
            virtual ~CustomFunction() {}
            std::shared_ptr<Variable> execute(std::shared_ptr<Tokens::Token> token,
                                          std::shared_ptr<Variables::Scope> globalScope,
                                          std::shared_ptr<Variables::Scope> scope,
                                          std::vector<std::shared_ptr<Nodes::Node>> arguments);
            std::string toString(std::vector<std::shared_ptr<Nodes::Node>> arguments);
        };
    }
}

#endif // CUSTOMFUNCTION_H
