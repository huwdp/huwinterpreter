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

DoubleVariable::DoubleVariable(std::shared_ptr<Passable> passable)
    : Variable(passable)
{
    this->value = 0;
}

DoubleVariable::DoubleVariable(std::shared_ptr<Passable> passable, double value)
    : Variable(passable, "")
{
    this->value = value;
}

DoubleVariable::DoubleVariable(std::shared_ptr<Passable> passable, std::string name, double value)
    : Variable(passable, name)
{
    this->value = value;
}

DoubleVariable::DoubleVariable(std::shared_ptr<Passable> passable, std::shared_ptr<Token> token)
    : Variable(passable, token)
{
    this->value = 0;
}

DoubleVariable::DoubleVariable(std::shared_ptr<Passable> passable, double value, std::shared_ptr<Token> token)
    : Variable(passable, "", token)
{
    this->value = value;
}

DoubleVariable::DoubleVariable(std::shared_ptr<Passable> passable, std::string name, double value, std::shared_ptr<Token> token)
    : Variable(passable, name, token)
{
    this->value = value;
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
        passable->errors->add(passable->errorFactory->couldNotConvertStringToNumber(token, name, "setValue", e.what()));
    }
}

void DoubleVariable::setValue(long long value)
{
    try
    {
        this->value = (double)value;
    }
    catch (const std::exception& e)
    {
        passable->errors->add(passable->errorFactory->couldNotConvertStringToNumber(token, name, "setValue", e.what()));
    }
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
    Precision precision;
    if (precision.getType(value) == INTEGER)
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

bool DoubleVariable::toBool()
{
    if (value != double(0))
    {
        return true;
    }
    return false;
}

VarType DoubleVariable::getType()
{
    return DOUBLE;
}

double DoubleVariable::getValue()
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

std::shared_ptr<Variable> DoubleVariable::pow(std::shared_ptr<Variable> variable, std::shared_ptr<Token> token)
{
    if (variable == nullptr)
    {
        return null;
    }
    std::shared_ptr<Variable> temp(new NumberVariable(passable, std::pow(this->toDouble(),variable->toDouble())));
    return std::move(temp);
}

std::shared_ptr<Variable> DoubleVariable::mul(std::shared_ptr<Variable> variable, std::shared_ptr<Token> token)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(passable, this->toDouble() * variable->toDouble()));
}

std::shared_ptr<Variable> DoubleVariable::div(std::shared_ptr<Variable> variable, std::shared_ptr<Token> token)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(passable, this->toDouble() / variable->toDouble()));
}

std::shared_ptr<Variable> DoubleVariable::mod(std::shared_ptr<Variable> variable, std::shared_ptr<Token> token)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::make_shared<NumberVariable>(passable, fmod(this->toDouble(), variable->toDouble()));
}

std::shared_ptr<Variable> DoubleVariable::add(std::shared_ptr<Variable> variable, std::shared_ptr<Token> token)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::make_shared<NumberVariable>(passable, this->toDouble() + variable->toDouble());
}

std::shared_ptr<Variable> DoubleVariable::sub(std::shared_ptr<Variable> variable, std::shared_ptr<Token> token)
{
    if (variable == nullptr)
    {
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(passable, this->toDouble() - variable->toDouble()));
}

std::shared_ptr<Variable> DoubleVariable::ifUnder(std::shared_ptr<Variable> variable, std::shared_ptr<Token> token)
{
    if (variable == nullptr)
    {
        passable->errors->add(passable->errorFactory->failedToCompare(token, "ifUnder", name, getType()));
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(passable, this->toDouble() < variable->toDouble()));
}

std::shared_ptr<Variable> DoubleVariable::ifUnderOrEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Token> token)
{
    if (variable == nullptr)
    {
        passable->errors->add(passable->errorFactory->failedToCompare(token, "ifUnderOrEqual", name, getType()));
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(passable, this->toDouble() <= variable->toDouble()));
}

std::shared_ptr<Variable> DoubleVariable::ifOver(std::shared_ptr<Variable> variable, std::shared_ptr<Token> token)
{
    if (variable == nullptr)
    {
        passable->errors->add(passable->errorFactory->failedToCompare(token, "ifOver", name, getType()));
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(passable, this->toDouble() > variable->toDouble()));
}

std::shared_ptr<Variable> DoubleVariable::ifOverOrEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Token> token)
{
    if (variable == nullptr)
    {
        passable->errors->add(passable->errorFactory->failedToCompare(token, "ifOverOrEqual", name, getType()));
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(passable, this->toDouble() >= variable->toDouble()));
}

std::shared_ptr<Variable> DoubleVariable::ifEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Token> token)
{
    if (variable == nullptr)
    {
        passable->errors->add(passable->errorFactory->failedToCompare(token, "ifEqual", name, getType()));
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(passable, this->toDouble() == variable->toDouble()));
}

std::shared_ptr<Variable> DoubleVariable::ifNotEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Token> token)
{
    if (variable == nullptr)
    {
        passable->errors->add(passable->errorFactory->failedToCompare(token, "ifNotEqual", name, getType()));
        return null;
    }
    return std::move(std::make_shared<NumberVariable>(passable, this->toDouble() != variable->toDouble()));
}

std::shared_ptr<Variable> DoubleVariable::increment(std::shared_ptr<Token> token)
{
    this->value++;
    return std::move(std::make_shared<NumberVariable>(passable, this->toDouble()));
}

std::shared_ptr<Variable> DoubleVariable::count(std::shared_ptr<Token> token)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(token, name, getType(), "count", "Double is not an array"));
    return null;
}

std::shared_ptr<Variable> DoubleVariable::decrement(std::shared_ptr<Token> token)
{
    this->value--;
    return std::move(std::make_shared<NumberVariable>(passable, this->toDouble()));
}

void DoubleVariable::set(std::string index, std::shared_ptr<Variable> value, std::shared_ptr<Token> token)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(token, name, getType(), "set", "Double is not an array"));
}

std::shared_ptr<Variable> DoubleVariable::get(std::string value, std::shared_ptr<Token> token)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(token, name, getType(), "get", "Double is not an array"));
    return null;
}

void DoubleVariable::unset(std::string index, std::shared_ptr<Token> token)
{
    passable->errors->add(passable->errorFactory->cannotCallFunction(token, name, getType(), "unset", "Double is not an array"));
}

std::shared_ptr<Variable> DoubleVariable::copy(std::shared_ptr<Token> token)
{
    return std::move(std::make_shared<DoubleVariable>(passable, value));
}

std::shared_ptr<Variable> DoubleVariable::bitwiseAnd(std::shared_ptr<Variable> variable, std::shared_ptr<Token> token)
{
    if (variable == nullptr)
    {
        return null;
    }
    long long value = (long long)this->value & variable->toInt();
    return std::move(std::make_shared<NumberVariable>(passable, value));
}

std::shared_ptr<Variable> DoubleVariable::bitwiseOr(std::shared_ptr<Variable> variable, std::shared_ptr<Token> token)
{
    if (variable == nullptr)
    {
        return null;
    }
    long long value = (long long)((long long)this->value | variable->toInt());
    return std::move(std::make_shared<NumberVariable>(passable, value));
}

std::shared_ptr<Variable> DoubleVariable::bitwiseXOR(std::shared_ptr<Variable> variable, std::shared_ptr<Token> token)
{
    if (variable == nullptr)
    {
        return null;
    }
    long long value = (long long)((long long)this->value ^ variable->toInt());
    return std::move(std::make_shared<NumberVariable>(passable, value));
}

std::shared_ptr<Variable> DoubleVariable::bitwiseComplement(std::shared_ptr<Token> token)
{
    return std::make_shared<NumberVariable>(passable, ~toInt());
}

std::shared_ptr<Variable> DoubleVariable::leftShift(std::shared_ptr<Variable> variable, std::shared_ptr<Token> token)
{
    if (variable == null)
    {
        return null;
    }
    return std::make_shared<NumberVariable>(passable, toInt() << variable->toInt());
}

std::shared_ptr<Variable> DoubleVariable::rightShift(std::shared_ptr<Variable> variable, std::shared_ptr<Token> token)
{
    if (variable == null)
    {
        return null;
    }
    return std::make_shared<NumberVariable>(passable, toInt() >> variable->toInt());
}
