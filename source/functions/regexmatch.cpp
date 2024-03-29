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

#ifdef _WIN32
#else
#include "regexmatch.h"

namespace HuwInterpreter {
    namespace Functions {
        RegexMatch::RegexMatch(std::shared_ptr<HuwInterpreter::Passable> passable)
            : Function(passable)
        {
            setName("regexMatch");
        }

        std::shared_ptr<Variable> RegexMatch::execute(std::shared_ptr<Tokens::Token> token, std::shared_ptr<Variables::Scope> globalScope,
                                      std::shared_ptr<Variables::Scope> scope,
                                      std::vector<std::shared_ptr<Nodes::Node>> arguments)
        {
            if (arguments.size() == 2)
            {
                std::shared_ptr<Nodes::Node> node1 = arguments.at(0);
                std::shared_ptr<Nodes::Node> node2 = arguments.at(1);
                if (node1 == nullptr || node2 == nullptr)
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->invalidArgument(token, RUNTIME_ERROR, name));
                    return nullVariable;
                }
                std::shared_ptr<Variable> var1 = node1->execute(globalScope, scope);
                std::shared_ptr<Variable> var2 = node2->execute(globalScope, scope);

                if (var1 == nullptr || var2 == nullptr)
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->invalidArgument(token, RUNTIME_ERROR, name));
                    return nullVariable;
                }
                std::string str = var1->toString();
                std::string str2 = var2->toString();
                std::shared_ptr<HashTableVariable> result = std::make_shared<HashTableVariable>(passable);
                std::regex pieces_regex(str2);
                std::smatch pieces_match;
                if (std::regex_match(str, pieces_match, pieces_regex))
                {
                    for (size_t i = 0; i < pieces_match.size(); ++i)
                    {
                        std::ssub_match sub_match = pieces_match[i];
                        std::string piece = sub_match.str();
                        result->set(std::to_string(i), std::make_shared<StringVariable>(passable, piece), token);
                    }
                }
                return std::move(result);
            }
            passable->getErrorManager()->add(passable->getErrorFactory()->requiresArguments(token, name, "", 2));
            return nullVariable;
        }
    }
}
#endif
