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

#include "doublevariable.h"

namespace HuwInterpreter {
    namespace Variables {
        DoubleVariable::DoubleVariable(std::shared_ptr<HuwInterpreter::Passable> passable)
            : Variable(passable)
        {
            this->value = 0;
        }

        DoubleVariable::DoubleVariable(std::shared_ptr<HuwInterpreter::Passable> passable, double value)
            : Variable(passable)
        {
            this->value = value;
        }

        DoubleVariable::DoubleVariable(std::shared_ptr<HuwInterpreter::Passable> passable, std::string name, double value)
            : Variable(passable, std::move(name))
        {
            this->value = value;
        }

        DoubleVariable::DoubleVariable(std::shared_ptr<HuwInterpreter::Passable> passable, std::shared_ptr<Tokens::Token> token)
            : Variable(passable, token)
        {
            this->value = 0;
        }

        DoubleVariable::DoubleVariable(std::shared_ptr<HuwInterpreter::Passable> passable, double value, std::shared_ptr<Tokens::Token> token)
            : Variable(passable, token)
        {
            this->value = value;
        }

        DoubleVariable::DoubleVariable(std::shared_ptr<HuwInterpreter::Passable> passable, std::string name, double value, std::shared_ptr<Tokens::Token> token)
            : Variable(passable, name, token)
        {
            this->value = value;
        }

        std::shared_ptr<Variable> DoubleVariable::getValue()
        {
            return std::make_shared<DoubleVariable>(passable, value);
        }

        void DoubleVariable::setValue(double value)
        {
            this->value = value;
        }

        void DoubleVariable::setValue(std::string value)
        {
            try
            {
                this->value = stod(value);
            }
            catch (const std::exception& e)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->couldNotConvertStringToNumber(token, name, "setValue", e.what()));
            }
        }

        void DoubleVariable::setValue(long long value)
        {
            try
            {
                this->value = static_cast<double>(value);
            }
            catch (const std::exception& e)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->couldNotConvertStringToNumber(token, name, "setValue", e.what()));
            }
        }

        void DoubleVariable::setValue(std::shared_ptr<Variable> variable)
        {
            return;
        }

        long long DoubleVariable::toInt()
        {
            return (long long)value;
        }

        double DoubleVariable::toDouble()
        {
            return value;
        }

        std::string DoubleVariable::toString()
        {
            Helpers::Precision precision;
            if (precision.getType(value) == Types::VarType::INTEGER)
            {
                return std::to_string(toInt());
            }
            std::stringstream ss;
            ss.precision(numberPrecision);
            ss << value;
            std::string output = ss.str();



            if (output.length() > 8)
            {
                return output.substr(0, 8);
            }
            return output;
        }

        std::string DoubleVariable::toJSON()
        {
            return toString();
        }

        bool DoubleVariable::toBool()
        {
            if (value != double(0))
            {
                return true;
            }
            return false;
        }

        Types::VarType DoubleVariable::getType()
        {
            return Types::DOUBLE;
        }

        double DoubleVariable::getDoubleValue()
        {
            return value;
        }

        bool DoubleVariable::isNumber()
        {
            return true;
        }

        bool DoubleVariable::isConst()
        {
            return false;
        }

        bool DoubleVariable::isArray()
        {
            return false;
        }

        bool DoubleVariable::isRef()
        {
            return false;
        }

        std::shared_ptr<Variable> DoubleVariable::pow(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            std::shared_ptr<Variable> temp(new DoubleVariable(passable, std::pow(this->toDouble(),variable->toDouble())));
            return temp;
        }

        std::shared_ptr<Variable> DoubleVariable::mul(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            return std::make_shared<DoubleVariable>(passable, this->toDouble() * variable->toDouble());
        }

        std::shared_ptr<Variable> DoubleVariable::div(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            return std::make_shared<DoubleVariable>(passable, this->toDouble() / variable->toDouble());
        }

        std::shared_ptr<Variable> DoubleVariable::mod(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            return std::make_shared<DoubleVariable>(passable, fmod(this->toDouble(), variable->toDouble()));
        }

        std::shared_ptr<Variable> DoubleVariable::add(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            return std::make_shared<DoubleVariable>(passable, this->toDouble() + variable->toDouble());
        }

        std::shared_ptr<Variable> DoubleVariable::sub(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            return std::make_shared<DoubleVariable>(passable, this->toDouble() - variable->toDouble());
        }

        std::shared_ptr<Variable> DoubleVariable::ifUnder(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifUnder", name, getType()));
                return nullVariable;
            }
            return std::make_shared<DoubleVariable>(passable, this->toDouble() < variable->toDouble());
        }

        std::shared_ptr<Variable> DoubleVariable::ifUnderOrEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifUnderOrEqual", name, getType()));
                return nullVariable;
            }
            return std::make_shared<DoubleVariable>(passable, this->toDouble() <= variable->toDouble());
        }

        std::shared_ptr<Variable> DoubleVariable::ifOver(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifOver", name, getType()));
                return nullVariable;
            }
            return std::make_shared<DoubleVariable>(passable, this->toDouble() > variable->toDouble());
        }

        std::shared_ptr<Variable> DoubleVariable::ifOverOrEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifOverOrEqual", name, getType()));
                return nullVariable;
            }
            return std::make_shared<DoubleVariable>(passable, this->toDouble() >= variable->toDouble());
        }

        std::shared_ptr<Variable> DoubleVariable::ifEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifEqual", name, getType()));
                return nullVariable;
            }
            return std::make_shared<DoubleVariable>(passable, this->toDouble() == variable->toDouble());
        }

        std::shared_ptr<Variable> DoubleVariable::ifNotEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->failedToCompare(token, "ifNotEqual", name, getType()));
                return nullVariable;
            }
            return std::make_shared<DoubleVariable>(passable, this->toDouble() != variable->toDouble());
        }

        std::shared_ptr<Variable> DoubleVariable::increment(std::shared_ptr<Tokens::Token> token)
        {
            this->value++;
            return std::make_shared<DoubleVariable>(passable, this->toDouble());
        }

        std::shared_ptr<Variable> DoubleVariable::count(std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "count", "Double is not an array"));
            return nullVariable;
        }

        std::shared_ptr<Variable> DoubleVariable::decrement(std::shared_ptr<Tokens::Token> token)
        {
            this->value--;
            return std::make_shared<DoubleVariable>(passable, this->toDouble());
        }

        void DoubleVariable::set(std::string index, std::shared_ptr<Variable> value, std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "set", "Double is not an array"));
        }

        std::shared_ptr<Variable> DoubleVariable::get(std::string value, std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "get", "Double is not an array"));
            return nullVariable;
        }

        bool DoubleVariable::boundExists(std::string index, std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "unset", "Double is not an array"));
            return false;
        }

        void DoubleVariable::unset(std::string index, std::shared_ptr<Tokens::Token> token)
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->cannotCallFunction(token, name, getType(), "unset", "Double is not an array"));
        }

        std::shared_ptr<Variable> DoubleVariable::clone(std::shared_ptr<Tokens::Token> token)
        {
            return this->getValue();
        }

        std::shared_ptr<Variable> DoubleVariable::bitwiseAnd(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            long long value = (long long)this->value & variable->toInt();
            return std::make_shared<DoubleVariable>(passable, value);
        }

        std::shared_ptr<Variable> DoubleVariable::bitwiseOr(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            long long value = static_cast<long long>(this->value) | variable->toInt();
            return std::make_shared<DoubleVariable>(passable, value);
        }

        std::shared_ptr<Variable> DoubleVariable::bitwiseXOR(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            long long value = static_cast<long long>(this->value) ^ variable->toInt();
            return std::make_shared<DoubleVariable>(passable, value);
        }

        std::shared_ptr<Variable> DoubleVariable::bitwiseComplement(std::shared_ptr<Tokens::Token> token)
        {
            return std::make_shared<DoubleVariable>(passable, ~toInt());
        }

        std::shared_ptr<Variable> DoubleVariable::leftShift(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            return std::make_shared<DoubleVariable>(passable, toInt() << variable->toInt());
        }

        std::shared_ptr<Variable> DoubleVariable::rightShift(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token)
        {
            if (variable == nullptr)
            {
                return nullVariable;
            }
            return std::make_shared<DoubleVariable>(passable, toInt() >> variable->toInt());
        }

        std::shared_ptr<Variable> DoubleVariable::sort()
        {
            passable->getErrorManager()->add(passable->getErrorFactory()->isNotAnArray(token, name));
            return nullVariable;
        }

        std::shared_ptr<Variable> DoubleVariable::size()
        {
            // Throw error
            return nullVariable;
        }
    }
}
