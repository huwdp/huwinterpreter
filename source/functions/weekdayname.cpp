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

#include "weekdayname.h"
#include <iomanip>

namespace HuwInterpreter {
    namespace Functions {
        WeekdayName::WeekdayName(std::shared_ptr<HuwInterpreter::Passable> passable)
            : Function(passable)
        {
            setName("weekdayName");
        }

        std::shared_ptr<Variable> WeekdayName::execute(std::shared_ptr<Tokens::Token> token, std::shared_ptr<Variables::Scope> globalScope,
                                                   std::shared_ptr<Variables::Scope> scope,
                                                   std::vector<std::shared_ptr<Nodes::Node>> arguments)
        {
            if (arguments.size() == 1)
            {
                std::shared_ptr<Nodes::Node> node = arguments.at(0);
                if (node == nullptr)
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->invalidArgument(token, RUNTIME_ERROR, name));
                    return nullVariable;
                }
                std::shared_ptr<Variable> var = node->execute(globalScope, scope);
                if (var == nullptr)
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->invalidArgument(token, RUNTIME_ERROR, name));
                    return nullVariable;
                }
                try
                {
                    double d = var->toDouble();
                    int value = static_cast<int>(d);
                    std::time_t t = value;
                    std::tm tm = *std::localtime(&t);
                    std::stringstream ss;
                    ss << std::put_time(&tm, "%A");
                    return std::make_shared<StringVariable>(passable, "", ss.str());
                }
                catch (const std::invalid_argument& ex)
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->invalidArgument(token, FUNCTION_ERROR, name, ex.what()));
                }
                catch (const std::out_of_range& ex)
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->outOfRange(token, name, ex.what()));
                }
                catch (const std::exception& ex)
                {
                    passable->getErrorManager()->add(passable->getErrorFactory()->otherFunctionError(token, name, ex.what()));
                }
                return nullVariable;
            }
            passable->getErrorManager()->add(passable->getErrorFactory()->requiresArguments(token, name, "", 1));
            return nullVariable;
        }
    }
}
#endif
