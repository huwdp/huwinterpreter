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

#include "functioncount.h"

namespace HuwInterpreter {
    namespace Functions {
        FunctionCountFunction::FunctionCountFunction(std::shared_ptr<Passable> passable)
            : Function(passable)
        {
            setName("functionCount");
        }

        std::shared_ptr<Variable> FunctionCountFunction::execute(std::shared_ptr<Tokens::Token> token, std::shared_ptr<Scope> globalScope,
                                           std::shared_ptr<Scope> scope,
                                           std::vector<std::shared_ptr<Nodes::Node>> arguments)
        {
            return std::make_shared<DoubleVariable>(passable, 0);
        }
    }
}
