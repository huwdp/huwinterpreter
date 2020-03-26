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

#include "hashtablevariable.h"

namespace HuwInterpreter {
    namespace Variables {



        HashTableVariable::HashTableVariable(std::shared_ptr<HuwInterpreter::Passable> passable)
            : Variable(passable)
        {

        }

        HashTableVariable::HashTableVariable(std::shared_ptr<HuwInterpreter::Passable> passable, std::string name)
            : Variable(passable, std::move(name))
        {

        }

        HashTableVariable::HashTableVariable(std::shared_ptr<HuwInterpreter::Passable> passable, std::shared_ptr<Tokens::Token> token)
            : Variable(passable, token)
        {

        }

        HashTableVariable::HashTableVariable(std::shared_ptr<HuwInterpreter::Passable> passable, std::shared_ptr<Tokens::Token> token, std::string name)
            : Variable(passable, std::move(name), token)
        {

        }

        std::shared_ptr<Variable> HashTableVariable::getValue()
        {
            std::shared_ptr<HashTableVariable> map = std::make_shared<HashTableVariable>(passable);
            for (std::map<std::string, std::shared_ptr<Variable>>::iterator it = this->map.begin(); it != this->map.end(); ++it)
            {
                map->set((*it).first, (*it).second->clone(token), token);
            }
            return std::move(map);
        }

        void HashTableVariable::setValue(double value)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->couldNotConvert(token, name, "setValue", Types::VarType::ARRAY, ""));
        }

        void HashTableVariable::setValue(std::string value)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->couldNotConvert(token, name, "setValue", Types::VarType::ARRAY, ""));
        }

        void HashTableVariable::setValue(long long value)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->couldNotConvert(token, name, "setValue", Types::VarType::ARRAY, ""));
        }

        void HashTableVariable::setValue(std::shared_ptr<Variable> variable)
        {
            if (variable != nullptr && variable->isArray())
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->couldNotConvert(token, name, "setValue", Types::VarType::ARRAY, ""));
            }
        }

        double HashTableVariable::toDouble()
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->couldNotConvert(token, name, "toDouble", getType(), "Cannot convert array to number."));
            return 0.0;
        }

        long long HashTableVariable::toInt()
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->couldNotConvert(token, name, "toDouble", getType(), "Cannot convert array to number."));
            return 0;
        }

        std::string HashTableVariable::toString()
        {
            std::string output = "[\n";
            for (std::map<std::string, std::shared_ptr<Variable>>::iterator it = map.begin(); it != map.end(); ++it)
            {
                output.append("\tKey: \"" + (*it).first + "\", Value: \"" + (*it).second->toString()+"\"\n");
            }
            output.append("]");
            return output;
        }

        std::string HashTableVariable::toJSON()
        {
            std::string output;
            std::map<std::string, std::shared_ptr<Variable>>::iterator it = map.begin();

            bool isHashTable = false;
            if (it == map.end())
            {
                isHashTable = true;
            }

            // Below could be optimised
            for (; it != map.end(); it++)
            {
                if (!Helpers::TypeDetector::isNumeric((*it).first))
                {
                    isHashTable = true;
                }
            }

            it = map.begin();
            if (isHashTable)
            {
                output.append("{");
                while (it != map.end())
                {
                    output.append("\"" + (*it).first + "\":" + (*it).second->toJSON());
                    it++;
                    if (it != map.end())
                    {
                        output.append(",") ;
                    }
                }
                output.append("}");
                return output;
            }

            // Below could be optimised also
            std::vector<std::tuple<std::string, std::shared_ptr<Variable>>> list;
            for (std::map<std::string, std::shared_ptr<Variable>>::iterator it = map.begin(); it != map.end() ; ++it)
            {
                list.push_back(std::make_tuple((*it).first, (*it).second));
            }
            std::sort(list.begin(), list.end()); //Sort string, first tuple value
            std::vector<std::tuple<std::string, std::shared_ptr<Variable>>>::iterator it2 = list.begin();
            output.append("[");
            while (it2 != list.end())
            {
                output.append(std::get<1>((*it2))->toJSON());
                it2++;
                if (it2 != list.end())
                {
                    output.append(",") ;
                }
            }
            output.append("]");
            return output;
        }

        bool HashTableVariable::toBool()
        {
            return false;
        }

        Types::VarType HashTableVariable::getType()
        {
            return Types::ARRAY;
        }

        double HashTableVariable::getDoubleValue()
        {
            return 0.0;
        }

        bool HashTableVariable::isNumber()
        {
            return false;
        }

        bool HashTableVariable::isConst()
        {
            return false;
        }

        bool HashTableVariable::isArray()
        {
            return true;
        }

        bool HashTableVariable::isRef()
        {
            return false;
        }

        std::shared_ptr<Variable> HashTableVariable::pow(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "pow", ""));
            return nullVariable;
        }

        std::shared_ptr<Variable> HashTableVariable::mul(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "multiply", ""));
            return nullVariable;
        }

        std::shared_ptr<Variable> HashTableVariable::div(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "divide", ""));
            return nullVariable;
        }

        std::shared_ptr<Variable> HashTableVariable::mod(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "mod", ""));
            return nullVariable;
        }

        std::shared_ptr<Variable> HashTableVariable::add(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            map[std::to_string(map.size()+1)] = variable;
            return nullVariable;
        }

        std::shared_ptr<Variable> HashTableVariable::sub(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "subtract", ""));
            return nullVariable;
        }

        std::shared_ptr<Variable> HashTableVariable::ifUnder(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifUnder", name, getType()));
                return nullVariable;
            }
            passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifUnder", name, getType(), variable->getType()));
            return nullVariable;
        }

        std::shared_ptr<Variable> HashTableVariable::ifUnderOrEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifUnderOrEqual", name, getType()));
                return nullVariable;
            }
            passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifUnderOrEqual", name, getType(), variable->getType()));
            return nullVariable;
        }

        std::shared_ptr<Variable> HashTableVariable::ifOver(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifOver", name, getType()));
                return nullVariable;
            }
            passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifOver", name, getType(), variable->getType()));
            return nullVariable;
        }

        std::shared_ptr<Variable> HashTableVariable::ifOverOrEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifOverOrEqual", name, getType()));
                return nullVariable;
            }
            passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifOverOrEqual", name, getType(), variable->getType()));
            return nullVariable;
        }

        std::shared_ptr<Variable> HashTableVariable::ifEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifEqual", name, getType()));
                return nullVariable;
            }
            passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifEqual", name, getType(), variable->getType()));
            return nullVariable;
        }

        std::shared_ptr<Variable> HashTableVariable::ifNotEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token,"ifNotEqual", name, getType()));
                return nullVariable;
            }
            passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token,"ifNotEqual", name, getType(), variable->getType()));
            return nullVariable;
        }

        std::shared_ptr<Variable> HashTableVariable::addEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "addEqual", ""));
            return nullVariable;
        }

        std::shared_ptr<Variable> HashTableVariable::subEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "subEqual", ""));
            return nullVariable;
        }

        std::shared_ptr<Variable> HashTableVariable::mulEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "mulEqual", ""));
            return nullVariable;
        }

        std::shared_ptr<Variable> HashTableVariable::divEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "divEqual", ""));
            return nullVariable;
        }

        std::shared_ptr<Variable> HashTableVariable::equal(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            return std::make_shared<DoubleVariable>(passable, toString() == variable->toString());
        }

        std::shared_ptr<Variable> HashTableVariable::count(std::shared_ptr<Tokens::Token> token)
        {
            return std::make_shared<DoubleVariable>(passable, (long long)this->map.size());
        }

        std::shared_ptr<Variable> HashTableVariable::increment(std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "decrement", ""));
            return nullVariable;
        }

        std::shared_ptr<Variable> HashTableVariable::decrement(std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "increment", ""));
            return nullVariable;
        }

        void HashTableVariable::set(std::string index, std::shared_ptr<Variable> value, std::shared_ptr<Tokens::Token> token)
        {
            map[index] = value;
        }

        std::shared_ptr<Variable> HashTableVariable::get(std::string index, std::shared_ptr<Tokens::Token> token)
        {
            return map[index];
        }

        void HashTableVariable::unset(std::string index, std::shared_ptr<Tokens::Token> token)
        {
            map.erase(index);
        }

        std::shared_ptr<Variable> HashTableVariable::clone(std::shared_ptr<Tokens::Token> token)
        {
            return this->getValue();
        }

        std::shared_ptr<Variable> HashTableVariable::bitwiseAnd(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "bitwiseAnd", "Cannot bitwsieAND array type"));
            return nullVariable;
        }

        std::shared_ptr<Variable> HashTableVariable::bitwiseOr(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "bitwiseOr", "Cannot bitwiseOR array type"));
            return nullVariable;
        }

        std::shared_ptr<Variable> HashTableVariable::bitwiseXOR(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "bitwiseXOR", "Cannot bitwsieXOR array type"));
            return nullVariable;
        }

        std::shared_ptr<Variable> HashTableVariable::bitwiseComplement(std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "bitwiseXOR", "Cannot bitwiseComplement array type"));
            return nullVariable;
        }

        std::shared_ptr<Variable> HashTableVariable::leftShift(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "leftShift", "Cannot leftShift array type"));
            return nullVariable;
        }

        std::shared_ptr<Variable> HashTableVariable::rightShift(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "rightShift", "Cannot rightShift array type"));
            return nullVariable;
        }

        bool compare(std::pair<std::string, std::shared_ptr<Variable>>& d1, std::pair<std::string, std::shared_ptr<Variable>>& d2)
        {
            if (d1.second == nullptr)
            {
                return false;
            }
            if (d2.second == nullptr)
            {
                return false;
            }
            std::shared_ptr<Variable> outcome = d1.second->ifUnder(d2.second, nullptr);
            if (outcome == nullptr)
            {
                return false;
            }
            return outcome->toBool();
        }

        std::vector<std::pair<std::string, std::shared_ptr<Variable>>> HashTableVariable::toVector()
        {
            std::vector<std::pair<std::string, std::shared_ptr<Variable>>> list;


            for (std::map<std::string, std::shared_ptr<Variable>>::iterator it = map.begin(); it != map.end(); ++it)
            {
                list.push_back((*it));
            }
            return list;
        }

        std::shared_ptr<Variable> HashTableVariable::sort()
        {
            std::vector<std::pair<std::string, std::shared_ptr<Variable>>> list = toVector();

            // Assume keys are in correct order and do an insertion sort
            for (std::vector<std::pair<std::string, std::shared_ptr<Variable>>>::iterator it = list.begin(); it != list.end()-1; ++it)
            {
                auto jt = it;
                while (jt != list.begin())
                {
                    auto item1 = jt->second;
                    ++jt;
                    auto item2 = jt->second;
                    jt--;
                    auto result = item1->ifOver(item2,nullptr);
                    if (result != nullptr && result->toBool())
                    {
                        jt->second = item2;
                        jt++;
                        jt->second = item1;
                        jt--;
                    }
                    --jt;
                }
                if (jt == list.begin())
                {
                    auto item1 = jt->second;
                    ++jt;
                    auto item2 = jt->second;
                    jt--;
                    auto result = item1->ifOver(item2,nullptr);
                    if (result != nullptr && result->toBool())
                    {
                        jt->second = item2;
                        jt++;
                        jt->second = item1;
                        jt--;
                    }
                }
            }

            std::shared_ptr<Variable> newMap = std::make_shared<HashTableVariable>(passable);
            for (std::vector<std::pair<std::string, std::shared_ptr<Variable>>>::iterator it = list.begin(); it != list.end(); ++it)
            {
                newMap->set(it->first, it->second, nullptr);
            }
            return newMap;
        }
    }
}
