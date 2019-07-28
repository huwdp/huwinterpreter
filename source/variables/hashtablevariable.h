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

#ifndef HASHTABLEVARIABLE_H
#define HASHTABLEVARIABLE_H

#include <iostream>
#include <memory>
#include <unordered_map>
#include <algorithm>

#include "variable.h"
#include "doublevariable.h"

namespace HuwInterpreter {
    namespace Variables {
        class HashTableVariable : public Variable
        {
        private:
            std::unordered_map<std::string, std::shared_ptr<Variable>> map;
        public:
            HashTableVariable(std::shared_ptr<Passable> passable);
            HashTableVariable(std::shared_ptr<Passable> passable, std::string name);
            HashTableVariable(std::shared_ptr<Passable> passable, std::shared_ptr<Tokens::Token> token);
            HashTableVariable(std::shared_ptr<Passable> passable, std::shared_ptr<Tokens::Token> token, std::string name);
            std::shared_ptr<Variable> getValue();
            void setValue(double value);
            void setValue(std::string value);
            void setValue(long long value);
            void setValue(std::shared_ptr<Variable> variable);
            double toDouble();
            long long toInt();
            std::string toString();
            std::string toJSON();
            bool toBool();
            Types::VarType getType();
            double getDoubleValue();
            bool isNumber();
            bool isConst();
            bool isArray();
            bool isRef();
            std::shared_ptr<Variable> pow(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> mul(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> div(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> mod(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> add(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> sub(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> ifUnder(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> ifUnderOrEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> ifOver(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> ifOverOrEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> ifEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> ifNotEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> addEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> subEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> mulEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> divEqual(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> equal(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> increment(std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> decrement(std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> count(std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> get(std::string index, std::shared_ptr<Tokens::Token> token);
            void set(std::string index, std::shared_ptr<Variable> value, std::shared_ptr<Tokens::Token> token);
            void unset(std::string index, std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> clone(std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> bitwiseAnd(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> bitwiseOr(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> bitwiseXOR(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> bitwiseComplement(std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> leftShift(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token);
            std::shared_ptr<Variable> rightShift(std::shared_ptr<Variable> variable, std::shared_ptr<Tokens::Token> token);
        };
    }
}

#endif
