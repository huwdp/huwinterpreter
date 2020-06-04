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

#include "importnode.h"

#include "parser/parser.h"
#include "tokens/filetokenmanager.h"
#include "tokens/scanner.h"
#include "nodes/huwcodenodefactory.h"

namespace HuwInterpreter {
    namespace Nodes {
        ImportNode::ImportNode(std::shared_ptr<HuwInterpreter::Passable> passable,
                               std::shared_ptr<Tokens::Token> token, std::string name,
                               std::shared_ptr<Functions::FunctionManager> functionManager,
                               std::vector<std::shared_ptr<Nodes::Node>> arguments)
            : Node("Import", passable, token)
        {
            ErrorReporting::Debug::print(getName());
            this->arguments = arguments;
            this->functionManager = functionManager;
        }

        NodeType ImportNode::getType()
        {
            return IMPORTNODE;
        }

        std::shared_ptr<Variables::Variable> ImportNode::execute(std::shared_ptr<Variables::Scope> globalScope, std::shared_ptr<Variables::Scope> scope)
        {
            if (arguments.size() != 1)
            {
                return nullVariable;
            }
            std::shared_ptr<Nodes::Node> node = arguments.at(0);
            if (node == nullptr)
            {
                return nullVariable;
            }
            std::shared_ptr<Variables::Variable> var = node->execute(globalScope, scope);
            if (var == nullptr)
            {
                return nullVariable;
            }

            std::string fileLocation = var->toString();
            bool textMode = false; // This will need to change to format text correctly.

            std::ifstream file(fileLocation.c_str());

            if (!file.is_open())
            {
                passable->getErrorManager()->add(passable->getErrorFactory()->cannotReadFile(token, internalName, fileLocation.c_str()));
            	return nullVariable;
            }

            std::shared_ptr<FileTokenManager> fileTokenManager = std::make_shared<FileTokenManager>(fileLocation);
            std::shared_ptr<NodeFactory> nodeFactory = std::make_shared<HuwCodeNodeFactory>();
            std::shared_ptr<Scanner> scanner = std::make_shared<Scanner>();
            std::vector<std::shared_ptr<Token>> tokens = scanner->tokenize(fileTokenManager);

            std::shared_ptr<Parser> parser = std::make_shared<Parser>(tokens, nodeFactory, textMode, functionManager);
            std::shared_ptr<Nodes::Node> importNode = parser->parse();

            if (importNode != nullptr)
            {
                return importNode->execute(globalScope, scope);
            }
            return nullVariable;
        }

        std::string ImportNode::toString()
        {
            std::string output;

            return output;
        }
    }
}
