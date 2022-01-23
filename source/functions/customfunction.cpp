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

#include "customfunction.h"

namespace HuwInterpreter {
    namespace Functions {
        CustomFunction::CustomFunction(std::shared_ptr<HuwInterpreter::Passable> passable,
                                       std::shared_ptr<Tokens::Token> token,
                                       std::string name, std::vector<std::string> arguments,
                                       std::shared_ptr<Nodes::Node> block)
            : Function(passable)
        {
            setName(name);
            this->arguments = arguments;
            this->block = block;
            this->token = token;
        }

        std::shared_ptr<Variable> CustomFunction::execute(std::shared_ptr<Tokens::Token> token, std::shared_ptr<Variables::Scope> globalScope,
                                                      std::shared_ptr<Variables::Scope> scope,
                                                      std::vector<std::shared_ptr<Nodes::Node>> arguments)
        {


            if (this->arguments.size() != arguments.size())
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->unmatchedSpecifiedNumberOfArguments(token, name));
                return nullVariable;
            }

            // New scope
            std::shared_ptr<Variables::Scope> newScope = std::make_unique<Scope>(name, passable, false);

            std::vector<std::shared_ptr<Nodes::Node>>::iterator variableIt = arguments.begin();
            for (std::vector<std::string>::iterator argumentIt = this->arguments.begin(); argumentIt != this->arguments.end(); ++argumentIt)
            {
                std::shared_ptr<Variable> argument = (*variableIt)->execute(globalScope, scope);
                if (argument != nullptr)
                {
                    if (argument->isRef())
                    {
                        newScope->getVariableManager()->fastAddVariable((*argumentIt), argument);
                    }
                    else
                    {
                        newScope->getVariableManager()->fastAddVariable((*argumentIt), argument->clone(token));
                    }
                }
                ++variableIt;
            }

            if (passable->getErrorManager()->count() > 0)
            {
                passable->getStackTraceManager()->push(std::make_shared<ErrorReporting::StackTrace>(scope->getFunctionName(), token->getLineInfo()));
                return nullVariable;
            }

            if (block != nullptr)
            {
                if (passable->getErrorManager()->count() > 0)
                {
                    passable->getStackTraceManager()->push(std::make_shared<ErrorReporting::StackTrace>(scope->getFunctionName(), token->getLineInfo()));
                    return nullVariable;
                }

                block->execute(globalScope, newScope);

                if (passable->getErrorManager()->count() > 0)
                {
                    passable->getStackTraceManager()->push(std::make_shared<ErrorReporting::StackTrace>(scope->getFunctionName(), token->getLineInfo()));
                }

                return newScope->getReturnValue();
            }
            return nullVariable;
        }

        std::string CustomFunction::toString(std::vector<std::shared_ptr<Nodes::Node>> arguments)
        {
            std::string output;

            output.append("function");
            output.append(" ");
            output.append(name);
            output.append("(");
            for (std::vector<std::string>::iterator it = this->arguments.begin(); it != this->arguments.end(); ++it)
            {
                output.append((*it));
                ++it;
                if (it != this->arguments.end())
                {
                    output.append(",");
                }
                --it;
            }
            output.append(")");
            output.append("{");
            output.append(block->toString());
            output.append("}");
            return output;
        }
    }
}

