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

#ifndef HUWINTERPRETER_H
#define HUWINTERPRETER_H

#include <iostream>
#include <string>
#include <memory>
#include "parser/parser.h"
#include "tokens/token.h"
#include "tokens/scanner.h"
#include "io/io.h"
#include "errors/errors.h"
#include "tokens/texttokenmanager.h"
#include "nodes/nodefactory.h"
#include "nodes/huwcodenodefactory.h"
#include "nodes/nodefactoryfactory.h"

#include "tokens/filetokenmanager.h"

using namespace HuwInterpreter::Tokens;
using namespace HuwInterpreter::Nodes;

namespace  HuwInterpreter {

    class Interpreter
    {
    private:
        std::shared_ptr<NodeFactory> nodeFactory;
        std::shared_ptr<Nodes::Node> null;
        std::shared_ptr<Scanner> scanner;
        std::vector<std::shared_ptr<Token>> tokens;
        std::unique_ptr<Parser> parser;
    public:
        Interpreter();
        void executeFile(std::string fileLocation);
        void execute(std::vector<std::shared_ptr<Token>> tokens);
        void benchmark(std::vector<std::shared_ptr<Token>> tokens);
        std::string toString(std::vector<std::shared_ptr<Token>> tokens);
        void printErrors(std::shared_ptr<HuwInterpreter::Passable> passable);
        void printStackTrace(std::shared_ptr<StackTraceManager> stackTraceManager);
        std::vector<std::shared_ptr<Token>> parseFile(std::string fileLocation);
        std::vector<std::shared_ptr<Token> > parseText(std::string text);
    };
}

#endif // HUWINTERPRETER_H
