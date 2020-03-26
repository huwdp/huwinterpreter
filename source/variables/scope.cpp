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


        /*std::shared_ptr<Functions::Function> Scope::get(std::string name)
        {
            std::unordered_map<std::string,std::shared_ptr<Functions::Function>>::const_iterator got = functions.find(name);
            if (got == functions.end())
            {
                std::shared_ptr<Functions::Function> nullFunction;
                return nullFunction;
            }
            else
            {
                return (got->second);
            }
        }

        bool Scope::addFunction(std::shared_ptr<Functions::Function> function)
        {
            std::shared_ptr<Functions::Function> e = get(function->getName());
            if (e == nullptr)
            {
                std::string name = function->getName();
                functions[name] = function;
                return true;
            }
            return false;
        }

        bool Scope::addFunction(std::string name)
        {
            std::shared_ptr<Functions::Function> e = get(name);
            if (e == nullptr)
            {
                std::shared_ptr<EmptyFunction> empty = std::make_shared<EmptyFunction>(passable);
                functions[name] = empty;
                return true;
            }
            return false;
        }

        bool Scope::addFunction(std::string name, std::shared_ptr<Functions::Function> function)
        {
            std::shared_ptr<Functions::Function> e = get(function->getName());
            if (e == nullptr)
            {
                function->setName(name);
                functions[name] = function;
                return true;
            }
            return false;
        }

        bool Scope::setFunction(std::string name, std::shared_ptr<Functions::Function> function)
        {
            std::shared_ptr<Functions::Function> e = get(function->getName());
            if (e != nullptr)
            {
                function->setName(name);
                functions[name] = function;
                return true;
            }
            return false;
        }

        bool Scope::functionExists(std::string name)
        {
            std::unordered_map<std::string,std::shared_ptr<Functions::Function>>::const_iterator got = functions.find(name);
            if (got == functions.end())
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        bool FunctionManager::functionExists(std::shared_ptr<Functions::Function> function)
        {
            std::shared_ptr<Functions::Function> e = get(function->getName());
            if (e != nullptr)
            {
                return true;
            }
            return false;
        }

        bool Scope::removeFunction(std::shared_ptr<Functions::Function> function)
        {
            std::shared_ptr<Functions::Function> e = get(function->getName());
            if (e != nullptr)
            {
                this->functions.erase(function->getName());
                return true;
            }
            return false;
        }

        bool Scope::removeFunction(std::string name)
        {
            std::shared_ptr<Functions::Function> e = get(name);
            if (e != nullptr)
            {
                this->functions.erase(name);
                return true;
            }
            return false;
        }*/
    }
}
