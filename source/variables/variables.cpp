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

#include "variables.h"

namespace HuwInterpreter {
    namespace Variables {
        VariableManager::VariableManager(std::shared_ptr<HuwInterpreter::Passable> passable, bool addDefaults)
        {
            this->passable = passable;
            addDefaultVariables(addDefaults);
        }

        VariableManager::~VariableManager()
        {
            variables.clear();
        }

        void VariableManager::addDefaultVariables(bool addDefaults)
        {
            if (addDefaults)
            {
                addVariable(std::make_shared<ConstantVariable>(passable, std::make_shared<DoubleVariable>(passable, "PI", 3.14159265358979)));
                addVariable(std::make_shared<ConstantVariable>(passable, std::make_shared<DoubleVariable>(passable, "e", 2.718281828459045)));
                addVariable(std::make_shared<ConstantVariable>(passable, std::make_shared<DoubleVariable>(passable, "γ", 0.577215664901532)));
                addVariable(std::make_shared<ConstantVariable>(passable, std::make_shared<DoubleVariable>(passable, "Φ", 1.618033988749894)));
                addVariable(std::make_shared<ConstantVariable>(passable, std::make_shared<DoubleVariable>(passable, "φ", 0.618033988749894)));
                addVariable(std::make_shared<ConstantVariable>(passable, std::make_shared<DoubleVariable>(passable, "δs", 2.41421356237309)));
                addVariable(std::make_shared<ConstantVariable>(passable, std::make_shared<DoubleVariable>(passable, "ρ", 1.324717957244746)));
                addVariable(std::make_shared<ConstantVariable>(passable, std::make_shared<DoubleVariable>(passable, "true", 1)));
                addVariable(std::make_shared<ConstantVariable>(passable, std::make_shared<DoubleVariable>(passable, "false", 0)));
            }
        }

        std::shared_ptr<Variable> VariableManager::get(std::string name)
        {
            std::unordered_map<std::string,std::shared_ptr<Variable>>::const_iterator got = variables.find(name);
            if (got == variables.end())
            {
                return nullVariable;
            }
            else
            {
                return got->second;
            }
        }

        std::shared_ptr<Variable> VariableManager::exists(std::string name)
        {
            std::unordered_map<std::string,std::shared_ptr<Variable>>::const_iterator got = variables.find(name);
            if (got == variables.end())
            {
                return nullVariable;
            }
            else
            {
                return got->second;
            }
        }

        std::shared_ptr<Variable> VariableManager::exists(std::shared_ptr<Variable> variable)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            std::shared_ptr<Variable> e = exists(variable->getName());
            if (e != nullptr)
            {
                return e;
            }
            return nullVariable;
        }

        bool VariableManager::addVariable(std::shared_ptr<Variable> variable)
        {
            if (variable != nullptr)
            {
                std::shared_ptr<Variable> e = exists(variable->getName());
                if (e == nullptr)
                {
                    std::string name = variable->getName();
                    variables[name] = variable;
                    return true;
                }
            }
            return false;
        }

        bool VariableManager::addVariable(std::string name, std::shared_ptr<Variable> variable)
        {
            if (variable != nullptr)
            {
                std::shared_ptr<Variable> e = exists(name);
                if (e == nullptr)
                {
                    variable->setName(name);
                    variables[name] = variable;
                    return true;
                }
            }
            return false;
        }

        void VariableManager::fastAddVariable(std::shared_ptr<Variable> variable)
        {
            if (variable != nullptr)
            {
                variables[variable->getName()] = variable;
            }
        }

        void VariableManager::fastAddVariable(std::string name, std::shared_ptr<Variable> variable)
        {
            variables[name] = variable;
        }

        bool VariableManager::removeVariable(std::shared_ptr<Variable> variable)
        {
            if (variable != nullptr)
            {
                std::shared_ptr<Variable> e = exists(variable->getName());
                if (e != nullptr)
                {
                    this->variables.erase(variable->getName());
                    return true;
                }
            }
            return false;
        }

        bool VariableManager::removeVariable(std::string name)
        {
            std::shared_ptr<Variable> e = exists(name);
            if (e != nullptr)
            {
                this->variables.erase(name);
                return true;
            }
            return false;
        }

        bool VariableManager::setVariable(std::string name, std::shared_ptr<Variable> variable)
        {
            std::shared_ptr<Variable> e = exists(name);
            if (e == nullptr)
            {
                return false;
            }
            this->variables[name] = variable;
            return true;
        }
    }
}
