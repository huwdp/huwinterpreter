#ifndef UNARYNOTNODE_H
#define UNARYNOTNODE_H

#include "node.h"

class UnaryNotNode : public Node
{
private:
    std::shared_ptr<Node> node;
public:
    UnaryNotNode(std::shared_ptr<Token> token, std::shared_ptr<Node> node);
    std::shared_ptr<Variable> execute(std::shared_ptr<Scope> scope);
};

#endif // UNARYNOTNODE_H
