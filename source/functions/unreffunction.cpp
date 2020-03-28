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

#include "unreffunction.h"

namespace HuwInterpreter {
    namespace Functions {
        UnrefFunction::UnrefFunction(std::shared_ptr<HuwInterpreter::Passable> passable)
            : Function(passable)
        {
            setName("unRef");
        }

        std::shared_ptr<Variable> UnrefFunction::execute(std::shared_ptr<Tokens::Token> token, std::shared_ptr<Variables::Scope> globalScope,
                                             std::shared_ptr<Variables::Scope> scope,
                                             std::vector<std::shared_ptr<Nodes::Node>> arguments)
        {
            if (arguments.size() == 1)
            {
                std::shared_ptr<Nodes::Node> node = arguments.at(0);
                if (node != nullptr)
                {
                    std::shared_ptr<Variables::Variable> var = node->execute(globalScope, scope);
                    if (var->isRef())
                    {
                        return var->getValue();
                    }
                    return var;
                }
                passable->getErrorManager()->add(passable->getErrorFactory()->invalidExpression(RUNTIME_ERROR, token, this->getName()));
                return nullVariable;
            }
            passable->getErrorManager()->add(passable->getErrorFactory()->requiresArguments(token, name, "", 1));
            return nullVariable;
        }
    }
}
