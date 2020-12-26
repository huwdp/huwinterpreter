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

#include "addvarnode.h"

namespace HuwInterpreter {
    namespace Nodes {
        AddVarNode::AddVarNode(std::shared_ptr<HuwInterpreter::Passable> passable, std::shared_ptr<Tokens::Token> token, std::string name, std::shared_ptr<Nodes::Node> value)
            : Node("AddVarNode", passable, token)
        {
            ErrorReporting::Debug::print(getName());
            this->name = name;
            this->value = value;
        }

        NodeType AddVarNode::getType()
        {
            return ADDVARNODETYPE;
        }

        std::shared_ptr<Variables::Variable> AddVarNode::execute(std::shared_ptr<Variables::Scope> globalScope, std::shared_ptr<Variables::Scope> scope)
        {
            ErrorReporting::Debug::print(getName());
            if (passable->getErrorManager()->count() > 0)
            {
                return nullVariable;
            }
            if (scope->getReturnValue() != nullptr)
            {
                return scope->getReturnValue();
            }
            std::shared_ptr<Variables::Variable> v = value->execute(globalScope, scope);
            if (passable->getErrorManager()->count() > 0)
            {
                return nullVariable;
            }
            if (scope->getReturnValue() != nullptr)
            {
                return scope->getReturnValue();
            }

            std::shared_ptr<Variables::Variable> variable = scope->getVariableManager()->get(name);

            if (variable != nullptr)
            {
                if (v != nullptr)
                {
                    scope->getVariableManager()->setVariable(name, v->clone(token));
                    return nullVariable;
                }
                scope->getVariableManager()->setVariable(name, nullVariable);
                return nullVariable;
            }

            if (v != nullptr)
            {
                if (!scope->getVariableManager()->addVariable(name, v->clone(token)))
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->variableNotDeclared(token, name));
                }
                return nullVariable;
            }
            passable->getErrorManager()->add(passable->getErrorFactory()->invalidExpression(RUNTIME_ERROR, token, internalName));
            return nullVariable;
        }

        std::string AddVarNode::toString()
        {
            std::string output;
            if (value != nullptr)
            {
                output.append("let ").append(name).append("=").append(value->toString());
            }
            return output;
        }
    }
}
