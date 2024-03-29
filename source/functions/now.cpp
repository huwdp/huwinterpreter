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

#ifdef __EMSCRIPTEN__
#elif _WIN32
#else

#include "now.h"

namespace HuwInterpreter {
    namespace Functions {
        Now::Now(std::shared_ptr<HuwInterpreter::Passable> passable)
            : Function(passable)
        {
            setName("now");
        }

        std::shared_ptr<Variable> Now::execute(std::shared_ptr<Tokens::Token> token, std::shared_ptr<Variables::Scope> globalScope,
                                           std::shared_ptr<Variables::Scope> scope,
                                           std::vector<std::shared_ptr<Nodes::Node>> arguments)
        {
            if (arguments.size() == 0)
            {
                time_t t = std::time(nullptr);
                double now = static_cast<double> (t);
                return std::make_shared<DoubleVariable>(passable, now);
            }
            passable->getErrorManager()->add(passable->getErrorFactory()->requiresArguments(token, name, "", 0));
            return nullVariable;
        }
    }
}
#endif
