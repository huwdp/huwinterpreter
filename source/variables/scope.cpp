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

#include "scope.h"

namespace HuwInterpreter {
    namespace Variables {

        Scope::Scope(std::shared_ptr<VariableManager> variableManager)
        {
            this->variableManager = std::move(variableManager);
        }

        Scope::Scope(std::string functionName, std::shared_ptr<VariableManager> variableManager)
        {
            this->functionName = functionName;
            this->variableManager = std::move(variableManager);
        }

        Scope::Scope(std::shared_ptr<Passable> passable, bool addDefaults)
        {
            variableManager = std::make_shared<VariableManager>(passable, addDefaults);
        }

        Scope::Scope(std::string functionName, std::shared_ptr<Passable> passable, bool addDefaults)
        {
            this->functionName = functionName;
            variableManager = std::make_shared<VariableManager>(passable, addDefaults);
        }

        std::shared_ptr<VariableManager> const& Scope::getVariableManager()
        {
            return variableManager;
        }

        void Scope::setVariableManager(std::shared_ptr<VariableManager> variableManager)
        {
            this->variableManager = variableManager;
        }

        std::shared_ptr<Variable> Scope::getReturnValue()
        {
            return returnValue;
        }

        void Scope::setReturnValue(std::shared_ptr<Variable> value)
        {
            this->returnValue = value;
        }

        std::string Scope::getFunctionName()
        {
            return functionName;
        }

        void Scope::setFunctionName(std::string functionName)
        {
            this->functionName = functionName;
        }
    }
}
