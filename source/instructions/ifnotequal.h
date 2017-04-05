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

#ifndef IFNOTEQUAL_H
#define IFNOTEQUAL_H
#include <string.h>
#include <stdio.h>
#include <string>
#include "instruction.h"
#include "../variables/variable.h"


class Variable;

class IfNotEqual : public Instruction
{
private:
    std::shared_ptr<Variable> a;
    std::shared_ptr<Variable> b;
public:
    IfNotEqual(std::shared_ptr<Variable> a, std::shared_ptr<Variable> b)
    {
        this->a = a;
        this->b = b;
    }

    std::shared_ptr<Variable> execute()
    {
        if (a != nullptr && b != nullptr)
        {
            a->ifNotEqual(b);
        }
        else
        {
            cout << "Error: Could not find variable" << endl;
        }
        std::shared_ptr<FileLine> null;
        return null;
    }
};
#endif
