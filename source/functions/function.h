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

#ifndef FUNCTION_H
#define FUNCTION_H
#include <string>
#include <vector>
#include <memory>

#include "variables/variable.h"
#include "nodes/node.h"
#include "errors/errors.h"
#include "errors/error.h"
#include "io/fileline.h"
#include "../common/passable.h"
#include "common/nameableobject.h"
#include "variables/scope.h"

namespace HuwInterpreter {

    namespace Variables {
        class Scope;
    }
    namespace Nodes {
        class Node;
    }

    namespace Functions {


        class Function : public NameableObject
        {
        protected:

            std::shared_ptr<HuwInterpreter::Passable> passable;
        public:
            std::shared_ptr<Variable> nullVariable;
            Function(std::shared_ptr<HuwInterpreter::Passable> passable);

            virtual std::shared_ptr<Variable> execute(std::shared_ptr<Tokens::Token> token,
                                                  std::shared_ptr<Variables::Scope> globalScope,
                                                  std::shared_ptr<Variables::Scope> scope,
                                                  std::vector<std::shared_ptr<Nodes::Node>> arguments) = 0;
            virtual std::string toString(std::vector<std::shared_ptr<Nodes::Node>> arguments);
        };
    }
}

static size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data)
{
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

#endif // FUNCTION_H
