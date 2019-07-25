/*#include "jsondecode.h"

JSONDecode::JSONDecode(std::string text)
{
    this->text = text;
    it = this->text.begin();
    end = this->text.end();
}

std::shared_ptr<Variable> JSONDecodeFunction::parseJSON(std::string text, std::shared_ptr<Tokens::Token> token)
{
    //this->text = text;
    //std::string::iterator it = this->text.begin();
    //std::string::iterator end = this->text.end();
    return parseJSONObject(token);
}

std::shared_ptr<Variable> JSONDecodeFunction::parseJSONObject(std::shared_ptr<Tokens::Token> token)
{
    if (accept('['))
    {
        // List

        std::shared_ptr<Variable> array = std::make_shared<HashTableVariable>(passable);
        acceptIndentation();

        while (it != end && (*it) != '}')
        {
            array->add(getValue(), token);
            acceptIndentation();
        }
        acceptIndentation();
        if (!accept(']'))
        {
            // Error
            return nullVariable;
        }
        return array;
    }

    if (accept('{'))
    {
        // Object
        std::shared_ptr<HashTableVariable> array = std::make_shared<HashTableVariable>(passable);

        while (it != end)
        {
            acceptIndentation();

            std::shared_ptr<Variable> key = getValue();

            acceptIndentation();

            if (!accept(':'))
            {
                // Error
                return nullptr;
            }

            acceptIndentation();

            std::shared_ptr<Variable> value = parseJSONObject(token);

            array->set(key->toString(), value, token);

            it++;
        }
    }
    return getValue();
}

bool JSONDecodeFunction::accept(char expected)
{
    if (it == end)
    {
        return false;
    }
    bool result = (*it) == expected;
    if (result)
    {
        ++it;
    }
    return result;
}

void JSONDecodeFunction::acceptIndentation()
{
    if (it != end)
    {
        while ((*it) == '\t' || (*it) == ' ')
        {
            ++it;
        }
    }
}

std::shared_ptr<Variable> JSONDecodeFunction::getValue()
{
    std::string text;
    if (accept('"'))
    {
        while (it != end && (*it) != '"')
        {
            text.append((*it), 1);
            ++it;
        }
        if (!accept('"'))
        {
            // Error
            return nullVariable;
        }
        return std::make_shared<StringVariable>(passable, text);
    }
    while (it != end && (*it) != '"')
    {
        text.append((*it), 1);
        ++it;
    }
    if (Helpers::TypeDetector::isNumeric(text))
    {
        std::shared_ptr<Variables::VariableTypeFactory> variableTypeFactory = std::make_shared<Variables::VariableTypeFactory>(passable);
        return variableTypeFactory->newVariable(Helpers::TypeDetector::getType(text));
    }
    // Error
    return nullVariable;
}
*/
