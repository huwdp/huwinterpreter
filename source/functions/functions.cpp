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

#include "functions.h"

namespace HuwInterpreter {
namespace Functions {
    FunctionManager::FunctionManager(std::shared_ptr<HuwInterpreter::Passable> passable)
    {
        this->passable = passable;
    }

    void FunctionManager::init()
    {
        functions["print"] = std::make_shared<Print>(passable);
        functions["command"] = std::make_shared<Command>(passable);
        functions["fileRead"] = std::make_shared<FileRead>(passable);
        functions["fileWrite"] = std::make_shared<FileWrite>(passable);
        functions["fileExists"] = std::make_shared<FileExists>(passable);
        functions["dir"] = std::make_shared<DirFunction>(passable);
        functions["month"] = std::make_shared<Month>(passable);
        functions["monthName"] = std::make_shared<MonthName>(passable);
        functions["not"] = std::make_shared<Not>(passable);
        functions["now"] = std::make_shared<Now>(passable);
        functions["print"] = std::make_shared<Print>(passable);
        functions["scan"] = std::make_shared<Scan>(passable);
        functions["weekday"] = std::make_shared<Weekday>(passable);
        functions["weekdayName"] = std::make_shared<WeekdayName>(passable);
        functions["year"] = std::make_shared<Year>(passable);
        functions["currentTime"] = std::make_shared<CurrentTimeFunction>(passable);
        functions["abs"] = std::make_shared<Abs>(passable);
        functions["acos"] = std::make_shared<Acos>(passable);
        functions["asin"] = std::make_shared<Asin>(passable);
        functions["atan"] = std::make_shared<Atan>(passable);
        functions["atan2"] = std::make_shared<Atan2>(passable);
        functions["ceil"] = std::make_shared<Ceil>(passable);
        functions["cos"] = std::make_shared<Cos>(passable);
        functions["exp"] = std::make_shared<Exp>(passable);
        functions["sin"] = std::make_shared<Sin>(passable);
        functions["sqrt"] = std::make_shared<Sqrt>(passable);
        functions["tan"] = std::make_shared<Tan>(passable);
        functions["pow"] = std::make_shared<Pow>(passable);
        functions["min"] = std::make_shared<Min>(passable);
        functions["max"] = std::make_shared<Max>(passable);
        functions["floor"] = std::make_shared<Floor>(passable);
        functions["log"] = std::make_shared<Log>(passable);
        functions["round"] = std::make_shared<Round>(passable);
        functions["lround"] = std::make_shared<LRound>(passable);
        functions["inStr"] = std::make_shared<InStr>(passable);
        functions["inStrRev"] = std::make_shared<InStrRev>(passable);
        functions["toLower"] = std::make_shared<ToLower>(passable);
        functions["left"] = std::make_shared<Left>(passable);
        functions["len"] = std::make_shared<Len>(passable);
        functions["lTrim"] = std::make_shared<LTrim>(passable);
        functions["mid"] = std::make_shared<Mid>(passable);
        functions["right"] = std::make_shared<Right>(passable);
        functions["rTrim"] = std::make_shared<RTrim>(passable);
        functions["space"] = std::make_shared<Space>(passable);
        functions["strCmp"] = std::make_shared<StrComp>(passable);
        functions["strRev"] = std::make_shared<StrReverse>(passable);
        functions["trim"] = std::make_shared<Trim>(passable);
        functions["toUpper"] = std::make_shared<ToUpper>(passable);
        functions["random"] = std::make_shared<Random>(passable);
        functions["asc"] = std::make_shared<Asc>(passable);
        functions["cha"] = std::make_shared<Cha>(passable);
        functions["str"] = std::make_shared<Str>(passable);
        functions["array"] = std::make_shared<Array>(passable);
        functions["count"] = std::make_shared<Count>(passable);
        functions["isIntType"] = std::make_shared<IsIntType>(passable);
        functions["isDoubleType"] = std::make_shared<IsDoubleType>(passable);
        functions["isStringType"] = std::make_shared<IsStringType>(passable);
        functions["isArrayType"] = std::make_shared<IsArrayType>(passable);
        functions["isNumberType"] = std::make_shared<IsNumberType>(passable);
        functions["isInt"] = std::make_shared<IsInt>(passable);
        functions["isDouble"] = std::make_shared<IsDouble>(passable);
        functions["isNumber"] = std::make_shared<IsNumber>(passable);
        functions["toInt"] = std::make_shared<ToNumber>(passable);
        functions["toDouble"] = std::make_shared<ToDouble>(passable);
        functions["toString"] = std::make_shared<ToString>(passable);
        functions["regexSearch"] = std::make_shared<RegexSearch>(passable);
        functions["regexReplace"] = std::make_shared<RegexReplace>(passable);
        functions["regexMatch"] = std::make_shared<RegexMatch>(passable);
        functions["ref"] = std::make_shared<RefFunction>(passable);
        functions["unref"] = std::make_shared<UnrefFunction>(passable);
        functions["clock"] = std::make_shared<ClockFunction>(passable);
        functions["timeFormat"] = std::make_shared<TimeFormatFunction>(passable);
        functions["httpGet"] = std::make_shared<HttpGetFunction>(passable);
        functions["httpPost"] = std::make_shared<HttpPostFunction>(passable);
        functions["httpPut"] = std::make_shared<HttpPutFunction>(passable);
        functions["httpDelete"] = std::make_shared<HttpDeleteFunction>(passable);
        functions["httpHead"] = std::make_shared<HttpHeadFunction>(passable);
        functions["sleep"] = std::make_shared<SleepFunction>(passable);
        functions["jsonEncode"] = std::make_shared<JSONEncodeFunction>(passable);
        functions["jsonDecode"] = std::make_shared<JSONDecodeFunction>(passable);
        functions["sort"] = std::make_shared<Sort>(passable);
    }

    std::shared_ptr<Functions::Function> FunctionManager::get(std::string name)
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

    bool FunctionManager::addFunction(std::shared_ptr<Functions::Function> function)
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

    bool FunctionManager::addFunction(std::string name)
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

    bool FunctionManager::addFunction(std::string name, std::shared_ptr<Functions::Function> function)
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

    bool FunctionManager::setFunction(std::string name, std::shared_ptr<Functions::Function> function)
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

    bool FunctionManager::exists(std::string name)
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

    bool FunctionManager::exists(std::shared_ptr<Functions::Function> function)
    {
        std::shared_ptr<Functions::Function> e = get(function->getName());
        if (e != nullptr)
        {
            return true;
        }
        return false;
    }

    bool FunctionManager::removeFunction(std::shared_ptr<Functions::Function> function)
    {
        std::shared_ptr<Functions::Function> e = get(function->getName());
        if (e != nullptr)
        {
            this->functions.erase(function->getName());
            return true;
        }
        return false;
    }

    bool FunctionManager::removeFunction(std::string name)
    {
        std::shared_ptr<Functions::Function> e = get(name);
        if (e != nullptr)
        {
            this->functions.erase(name);
            return true;
        }
        return false;
    }

    std::string FunctionManager::toString()
    {
        std::string output;
        for (std::unordered_map<std::string, std::shared_ptr<Functions::Function>>::iterator it = functions.begin(); it != functions.end(); ++it)
        {
            std::vector<std::shared_ptr<Nodes::Node>> emptyVector;
            output.append((*it).second->toString(emptyVector));
        }
        return output;
    }
}
}
