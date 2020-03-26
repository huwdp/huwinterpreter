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

#include "jsondecodefunction.h"

namespace HuwInterpreter {
    namespace Functions {
        JSONDecodeFunction::JSONDecodeFunction(std::shared_ptr<HuwInterpreter::Passable> passable)
            : Function(passable)
        {
            setName("jsonDecode");
        }

        std::shared_ptr<Variable> JSONDecodeFunction::execute(std::shared_ptr<Tokens::Token> token, std::shared_ptr<Variables::Scope> globalScope,
                                            std::shared_ptr<Variables::Scope> scope,
                                            std::vector<std::shared_ptr<Nodes::Node>> arguments)
        {
            std::shared_ptr<Nodes::Node> node = arguments.at(0);
            if (node == nullptr)
            {
                // Error
                return nullVariable;
            }

            std::shared_ptr<Variable> var = node->execute(globalScope, scope);

            if (var == nullptr)
            {
                // Error
                return nullVariable;
            }

            return parseJSON(var->toString(), token);
        }

        void JSONDecodeFunction::next()
        {
            if (it != end)
            {
                ++it;
            }
        }

        std::shared_ptr<Variable> JSONDecodeFunction::parseJSON(std::string text, std::shared_ptr<Tokens::Token> token)
        {
            this->text = text;
            it = this->text.begin();
            end = this->text.end();
            return parseJSONObject(token);
        }

        std::shared_ptr<Variable> JSONDecodeFunction::parseJSONObject(std::shared_ptr<Tokens::Token> token)
        {
            if (accept('['))
            {
                // List

                std::shared_ptr<Variable> array = std::make_shared<HashTableVariable>(passable);
                acceptIndentation();

                if (accept(']'))
                {
                    return array;
                }

                while (it != end && (*it) != '}' && (*it) != ']')
                {
                    array->add(getValue(), token);
                    acceptIndentation();

                    if (accept(']'))
                    {
                        return array;
                    }

                    next();
                }
                acceptIndentation();
                if (!accept(']'))
                {
                    // Error
                    return nullVariable;
                }
                return array;
            }

            if (accept('{'))
            {
                // Object
                std::shared_ptr<Variable> array = std::make_shared<HashTableVariable>(passable);

                acceptIndentation();

                if (accept('}'))
                {
                    return array;
                }

                while (it != end)
                {
                    acceptIndentation();

                    std::shared_ptr<Variable> key = getValue();

                    acceptIndentation();

                    if (accept('}'))
                    {
                        // Error
                        return nullptr;
                    }

                    if (!accept(':'))
                    {
                        // Error
                        return nullptr;
                    }

                    acceptIndentation();

                    std::shared_ptr<Variable> value = parseJSONObject(token);

                    array->set(key->toString(), value, token);

                    if (it == end)
                    {
                        return array;
                    }

                    if (accept('}'))
                    {
                        return array;
                    }

                    next();
                }
                return array;
            }
            return getValue();
        }

        bool JSONDecodeFunction::accept(char expected)
        {
            if (it == end)
            {
                return false;
            }
            bool result = (*it) == expected;
            if (result)
            {
                next();
            }
            return result;
        }

        void JSONDecodeFunction::acceptIndentation()
        {
            if (it != end)
            {
                while ((*it) == '\t' || (*it) == ' ')
                {
                    next();
                }
            }
        }

        std::shared_ptr<Variable> JSONDecodeFunction::getValue()
        {
            std::string text;
            if (accept('"'))
            {
                while (it != end && (*it) != '"')
                {
                    char character = (*it);
                    text.append(1, character);
                    next();
                }
                if (!accept('"'))
                {
                    // Error
                    return nullVariable;
                }
                return std::make_shared<StringVariable>(passable, text);
            }
            while (it != end && ((*it) != '}' && (*it) != ']' && (*it) != ':' && (*it) != ','))
            {
                char character = (*it);
                text.append(1, character);
                next();
            }
            if (Helpers::TypeDetector::isNumeric(text))
            {
                std::shared_ptr<Variables::VariableTypeFactory> variableTypeFactory = std::make_shared<Variables::VariableTypeFactory>(passable);
                std::shared_ptr<Variable> var = variableTypeFactory->newVariable(Helpers::TypeDetector::getType(text));
                var->setValue(text);
                return var;
            }
            // Error
            return nullVariable;
        }
    }
}
