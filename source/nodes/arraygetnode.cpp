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

#include "arraygetnode.h"

namespace HuwInterpreter {
    namespace Nodes {
        ArrayGetNode::ArrayGetNode(std::shared_ptr<HuwInterpreter::Passable> passable, std::shared_ptr<Tokens::Token> token, std::shared_ptr<Nodes::Node> left, std::shared_ptr<Nodes::Node> right)
            : Node("ArrayGetNode", passable, token)
        {
            ErrorReporting::Debug::print(getName());
            this->left = left;
            this->right = right;
        }

        NodeType ArrayGetNode::getType()
        {
            return ARRAYGETNODE;
        }

        std::shared_ptr<Variables::Variable> ArrayGetNode::execute(std::shared_ptr<Variables::Scope> globalScope, std::shared_ptr<Variables::Scope> scope)
        {
            ErrorReporting::Debug::print(getName());
            if (left == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->invalidExpression(RUNTIME_ERROR, token, internalName));
                return nullVariable;
            }

            if (right == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->invalidExpression(RUNTIME_ERROR, token, internalName));
                return nullVariable;
            }

            std::shared_ptr<Variable> array = left->execute(globalScope, scope);
            std::shared_ptr<Variable> index = right->execute(globalScope, scope);

            if (array == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->invalidExpression(RUNTIME_ERROR, token, internalName));
                return nullVariable;
            }

            if (index == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->invalidIndex(token, internalName));
                return nullVariable;
            }

            if (array->getType() == ARRAY || array->getType() == STRING)
            {
                std::string indexStr = index->toString();
                if (array->boundExists(indexStr, token))
                {
                    return array->get(indexStr, token);
                }
                passable->getErrorManager()->add(passable->getErrorFactory()->outOfBounds(token, array->getName()));
                return nullVariable;
            }

            passable->getErrorManager()->add(passable->getErrorFactory()->isNotAnArray(token, array->getName()));
            return nullVariable;
        }

        std::string ArrayGetNode::toString()
        {
            if (left != nullptr && right != nullptr)
            {
                std::string temp = left->toString() + "[" + right->toString() + "]";
                return temp;
            }
            return "";
        }
    }
}
