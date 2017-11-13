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

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "tokens/token.h"
#include "tokens/tokens.h"
#include <iostream>
#include <sstream>
#include <memory>

#include "errors/errors.h"
#include "errors/error.h"
#include "nodes/node.h"

#include "nodes/nodefactory.h"

#include "nodes/ifnode.h"
#include "nodes/whilenode.h"


#include "nodes/equalnode.h"

#include "nodes/ifequalnode.h"
#include "nodes/ifnotequalnode.h"
#include "nodes/ifundernode.h"
#include "nodes/ifunderorequalnode.h"
#include "nodes/ifovernode.h"
#include "nodes/ifoverorequalnode.h"

#include "nodes/ifandnode.h"
#include "nodes/ifornode.h"
#include "nodes/bitwiseandnode.h"
#include "nodes/bitwiseornode.h"

#include "nodes/getvarnode.h"
#include "nodes/setvarnode.h"
#include "nodes/addconstnode.h"
#include "nodes/addvarnode.h"
#include "nodes/getfuncnode.h"
#include "nodes/numbernode.h"
#include "nodes/textnode.h"
#include "nodes/runnode.h"

#include "nodes/addnode.h"
#include "nodes/subnode.h"
#include "nodes/mulnode.h"
#include "nodes/divnode.h"
#include "nodes/modnode.h"
#include "nodes/unaryminusnode.h"
#include "nodes/unarynotnode.h"

#include "nodes/setreturnnode.h"

#include "nodes/bracketnode.h"

#include "nodes/incrementnode.h"
#include "nodes/decrementnode.h"

//#include "variables/variables.h"
#include "variables/scope.h"
#include "functions/customfunction.h"

class Parser
{
private:
    std::shared_ptr<NodeFactory> nodeFactory;
    std::vector<std::shared_ptr<Token>> tokens;
    std::vector<std::shared_ptr<Token>>::iterator it;
    std::shared_ptr<Token> currentToken;
    std::shared_ptr<Functions> functions;
    std::shared_ptr<Functions> customFunctions;
    bool compilation;
    std::shared_ptr<Node> null;
    std::shared_ptr<NodeFactory> codeFactory;
    std::shared_ptr<Passable> passable;

    void setCompilation(bool compilation);
    void nextToken();
    void prevToken();
    std::shared_ptr<Token> peakToken();
    void error(const std::string msg);
    void acceptIndentation();
    void acceptSemicolon();
    bool accept(std::string s);
    bool accept(TokenType tokenType);
    bool expect(std::string s);
    bool expect(TokenType tokenType);
    std::string syntaxError(std::string content);
    bool expectSemicolon();
    void errorMessage(std::string errorMsg, std::shared_ptr<Token> currentToken);
    std::shared_ptr<Node> parseValue();
    std::shared_ptr<Node> parseFactor();
    std::shared_ptr<Node> parseTerm();
    std::shared_ptr<Node> parseExpression();
    std::shared_ptr<Node> parseCondition();
    std::shared_ptr<Node> parseBoolean();
    std::shared_ptr<Node> parseCompound();
    std::shared_ptr<Node> parseBracket();
    std::shared_ptr<Node> parseAssingment();
    std::shared_ptr<Node> parseFunction();
    std::shared_ptr<Node> parseDecloration();
    std::shared_ptr<Node> parseElseStatement();
    std::shared_ptr<Node> parseStatement();
    std::shared_ptr<Node> parseBlock();
public:
    Parser(std::vector<std::shared_ptr<Token>> tokens,
           std::shared_ptr<NodeFactory> nodeFactory);
    bool getCompilation();
    std::shared_ptr<Node> parse();
    std::string toString();
    bool execute();
};

#endif // PARSER_H
