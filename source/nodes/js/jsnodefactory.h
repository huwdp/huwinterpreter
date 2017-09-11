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


#ifndef JSNODEFACTORY_H
#define JSNODEFACTORY_H

#include "../nodefactory.h"

#include "../node.h"
#include  "jsequalnode.h"

#include  "jsifequalnode.h"
#include  "jsifnotequalnode.h"
#include  "jsifundernode.h"
#include  "jsifunderorequalnode.h"
#include  "jsifovernode.h"
#include  "jsifoverorequalnode.h"
#include "jsifnode.h"

#include "jswhilenode.h"

#include  "jsifandnode.h"
#include  "jsifornode.h"
#include  "jsbitwiseandnode.h"
#include  "jsbitwiseornode.h"

#include  "jsgetvarnode.h"
#include  "jssetvarnode.h"
#include  "jsaddconstnode.h"
#include  "jsaddvarnode.h"
#include  "jsgetfuncnode.h"
#include  "jsnumbernode.h"
#include  "jstextnode.h"
#include  "jsrunnode.h"

#include  "jsaddnode.h"
#include  "jssubnode.h"
#include  "jsmulnode.h"
#include  "jsdivnode.h"
#include  "jsmodnode.h"
#include  "jsunaryminusnode.h"
#include  "jsunarynotnode.h"

#include  "jssetreturnnode.h"

#include  "jsbracketnode.h"

#include  "jsincrementnode.h"
#include  "jsdecrementnode.h"

#include "jssemicolonnode.h"

class JSNodeFactory : public NodeFactory
{
public:
    JSNodeFactory();
    std::shared_ptr<Node> CreateAddConstNode(std::shared_ptr<Token> token, std::string name, std::shared_ptr<Node> value, std::shared_ptr<Node> next);
    std::shared_ptr<Node> CreateAddNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right);
    std::shared_ptr<Node> CreateAddVarNode(std::shared_ptr<Token> token, std::string name, std::shared_ptr<Node> value, std::shared_ptr<Node> next);
    std::shared_ptr<Node> CreateBitwiseAndNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right);
    std::shared_ptr<Node> CreateBitwiseOrNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right);
    std::shared_ptr<Node> CreateBracketNode(std::shared_ptr<Token> token, std::shared_ptr<Node> node);
    std::shared_ptr<Node> CreateDecrementNode(std::shared_ptr<Token> token, std::shared_ptr<Node> node);
    std::shared_ptr<Node> CreateDivNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right);
    std::shared_ptr<Node> CreateEqualNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right, std::shared_ptr<Node> next, std::shared_ptr<Scope> scope);
    std::shared_ptr<Node> CreateGetFuncNode(std::shared_ptr<Token> token, std::string name, std::shared_ptr<Functions> functions, std::vector<std::shared_ptr<Node>> arguments);
    std::shared_ptr<Node> CreateGetVarNode(std::shared_ptr<Token> token, std::string name);
    std::shared_ptr<Node> CreateIfAndNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right);
    std::shared_ptr<Node> CreateIfEqualNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right);
    std::shared_ptr<Node> CreateIfNode(std::shared_ptr<Token> token, std::shared_ptr<Node> condition, std::shared_ptr<Node> body, std::shared_ptr<Node> elseNode);
    std::shared_ptr<Node> CreateIfNotEqualNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right);
    std::shared_ptr<Node> CreateIfOrNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right);
    std::shared_ptr<Node> CreateIfOverNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right);
    std::shared_ptr<Node> CreateIfOverOrEqualNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right);
    std::shared_ptr<Node> CreateIfUnderNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right);
    std::shared_ptr<Node> CreateIfUnderOrEqualNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right);
    std::shared_ptr<Node> CreateIncrementNode(std::shared_ptr<Token> token, std::shared_ptr<Node> node);
    std::shared_ptr<Node> CreateModNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right);
    std::shared_ptr<Node> CreateMulNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right);
    std::shared_ptr<Node> CreateNumberNode(std::shared_ptr<Token> token, std::string value);
    std::shared_ptr<Node> CreateRunNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right);
    std::shared_ptr<Node> CreateSemicolonNode(std::shared_ptr<Node> node);
    std::shared_ptr<Node> CreateSetReturnNode(std::shared_ptr<Node> node);
    std::shared_ptr<Node> CreateSetVarNode(std::shared_ptr<Token> token, std::string name, std::shared_ptr<Node> value, std::shared_ptr<Node> next);
    std::shared_ptr<Node> CreateSubNode(std::shared_ptr<Token> token, std::shared_ptr<Node> left, std::shared_ptr<Node> right);
    std::shared_ptr<Node> CreateTextNode(std::shared_ptr<Token> token, std::string value);
    std::shared_ptr<Node> CreateUnaryMinusNode(std::shared_ptr<Token> token, std::shared_ptr<Node> node);
    std::shared_ptr<Node> CreateUnaryNotNode(std::shared_ptr<Token> token, std::shared_ptr<Node> node);
    std::shared_ptr<Node> CreateWhileNode(std::shared_ptr<Token> token, std::shared_ptr<Node> condition, std::shared_ptr<Node> body, std::shared_ptr<Node> next);
};

#endif // JSNODEFACTORY_H