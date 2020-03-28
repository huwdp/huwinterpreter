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

#include "huwinterpreter.h"

namespace  HuwInterpreter {

    Interpreter::Interpreter()
    {
        std::shared_ptr<NodeFactoryFactory> nodeFactoryFactory = std::make_shared<NodeFactoryFactory>();
        nodeFactory = nodeFactoryFactory->build(HUWCODE);
        scanner = std::make_shared<Scanner>();
    }

    void Interpreter::executeFile(std::string fileLocation)
    {
        std::ifstream file (fileLocation.c_str());
        bool exists = static_cast<bool>(file);
        if (!exists)
        {
            std::string errorMessage = "Could not find file \"";
            errorMessage.append(fileLocation);
            errorMessage.append("\"");
            return;
        }
        execute(parseFile(fileLocation));
    }

    void Interpreter::execute(std::vector<std::shared_ptr<Token>> tokens)
    {
        std::unique_ptr<Parser> parser = std::make_unique<Parser>(tokens, nodeFactory, false);
        parser->execute();
        printErrors(parser->getPassable());
        printStackTrace(parser->getPassable()->getStackTraceManager());
    }

    void Interpreter::benchmark(std::vector<std::shared_ptr<Token>> tokens)
    {
        auto start = std::chrono::high_resolution_clock::now();
        std::unique_ptr<Parser> parser = std::make_unique<Parser>(tokens, nodeFactory, false);
        parser->execute();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end-start;
        printErrors(parser->getPassable());
        printStackTrace(parser->getPassable()->getStackTraceManager());
        std::cout << "Benchmrk result: " << diff.count() << " seconds." << std::endl;
    }

    void Interpreter::printErrors(std::shared_ptr<HuwInterpreter::Passable> passable)
    {
        std::vector<std::shared_ptr<Error>> errors = passable->getErrorManager()->get();
        for (std::vector<std::shared_ptr<Error>>::iterator it = errors.begin(); it != errors.end(); ++it)
        {
            std::cout << (*it)->getMessage() << std::endl;
        }
    }

    void Interpreter::printStackTrace(std::shared_ptr<StackTraceManager> stackTraceManager)
    {
        // Stack is actually in reverse due to an optimisation.
        // Functions are only added onto the the stack if they error.
        // Reverse stack here
        std::stack<std::shared_ptr<StackTrace>> stack;
        while (!stackTraceManager->isEmpty())
        {
            stack.push(stackTraceManager->top());
            stackTraceManager->pop();
        }
        // Print stack
        while (!stack.empty())
        {
            std::cout << stack.top()->toString() << std::endl;
            stack.pop();
        }
    }

    std::string Interpreter::toString(std::vector<std::shared_ptr<Token>> tokens)
    {
        std::unique_ptr<Parser> parser = std::make_unique<Parser>(tokens, nodeFactory, true);
        return parser->toString();
    }

    std::vector<std::shared_ptr<Token>> Interpreter::parseFile(std::string fileLocation)
    {
        std::vector<std::shared_ptr<Token>> tokens;
        std::ifstream file (fileLocation.c_str());
        bool exists = static_cast<bool>(file);
        if (!exists)
        {
            std::string errorMessage = "Could not find file \"";
            errorMessage.append(fileLocation);
            errorMessage.append("\"");
            return tokens;
        }
        std::shared_ptr<FileTokenManager> fileTokenManager = std::make_shared<FileTokenManager>(fileLocation);
        return scanner->tokenize(fileTokenManager);
    }

    std::vector<std::shared_ptr<Token>> Interpreter::parseText(std::string text)
    {
        std::shared_ptr<TokenManager> textTokenManager = std::make_shared<TextTokenManager>(text);
        return scanner->tokenize(textTokenManager);
    }
}
