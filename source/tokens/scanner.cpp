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

#include "scanner.h"

#include <string>
#include <vector>
#include <iostream>
#include "../errors/debug.h"

namespace HuwInterpreter {
    namespace Tokens {

        Scanner::Scanner()
        {
            unusableTokenManager = std::make_shared<UnusableTokenList>();
            tokenManager = std::make_shared<TokenList>();
            items = std::vector<std::shared_ptr<Token>>();
        }

        bool Scanner::isAllowedCharacter(char character)
        {
            if (Helpers::TypeDetector::isNumeric(character))
            {
                return false;
            }
            return !unusableTokenManager->exists(character);
        }

        void Scanner::AddToken(Types::TokenType tokenType, std::shared_ptr<LineInfo> lineInfo)
        {
            items.emplace_back(std::make_shared<Token>(tokenManager->get(tokenType), tokenType, lineInfo));
        }

        void Scanner::AddToken(std::string text, Types::TokenType tokenType, std::shared_ptr<LineInfo> lineInfo)
        {
            items.emplace_back(std::make_shared<Token>(text , tokenType, lineInfo));
        }

        std::vector<std::shared_ptr<Token>> Scanner::tokenize(std::shared_ptr<TokenManager> fileReader)
        {
            items.clear();
            std::string temp = "";
            if (fileReader->isEmpty())
            {
                return items;
            }
            std::shared_ptr<LineInfo> lineInfo = std::make_shared<LineInfo>("", fileReader->getCurrent()->getLineNumber(),0);
            while (!fileReader->isEnd())
            {
                lineInfo = std::make_shared<LineInfo>("", fileReader->getCurrent()->getLineNumber(),0);

                if (fileReader->getCurrent()->getContent() == ' ')
                {
                    if (!temp.empty())
                    {
                        items.emplace_back(std::make_shared<Token>(temp, lineInfo));
                        temp = "";
                    }
                }
                else if (fileReader->getCurrent()->getContent() == ' ' || fileReader->getCurrent()->getContent() == '\t')
                {
                    // Do nothing here as recording indentation is kinda pointless.
                }
                else if (tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::INDENTATION))
                {}
                else if (tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::TABINDENTATION))
                {}
                else if (Helpers::TypeDetector::isNumeric(fileReader->getCurrent()->getContent()))
                {
                    temp.push_back(fileReader->getCurrent()->getContent());
                }
                else if (tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::DOT))
                {
                    temp.push_back(fileReader->getCurrent()->getContent());
                }
                else if (isAllowedCharacter(fileReader->getCurrent()->getContent()))
                {
                    temp.push_back(fileReader->getCurrent()->getContent());
                }
                else
                {
                    if (!temp.empty())
                    {
                        items.emplace_back(std::make_shared<Token>(temp, lineInfo));
                        temp = "";
                    }
                    else if (tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::QUOTE))
                    {
                        fileReader->next();

                        while (!fileReader->isEnd() && !tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::QUOTE))
                        {
                            if (fileReader->isEnd())
                            {
                                return items;
                            }

                            lineInfo = std::make_shared<LineInfo>("", fileReader->getCurrent()->getLineNumber(),0);
                            if (fileReader->getCurrent()->getContent() == '\\')
                            {
                                if (!fileReader->isEnd())
                                {
                                    char currentChar = fileReader->getNext()->getContent();

                                    if (tokenManager->fastCompare(currentChar, Types::QUOTE))
                                    {
                                        temp.push_back(fileReader->getCurrent()->getContent());
                                        fileReader->next();
                                    }
                                    else if (currentChar == 'n')    // Parse newline
                                    {
                                        temp.push_back('\n');
                                        fileReader->next();
                                    }
                                    else if (currentChar == 'r')    // Parse other newline
                                    {
                                        temp.push_back('\r');
                                        fileReader->next();
                                    }
                                    else
                                    {
                                        temp.push_back(fileReader->getCurrent()->getContent());
                                        fileReader->next();
                                    }
                                }
                                else
                                {
                                    temp.push_back(fileReader->getCurrent()->getContent());
                                    fileReader->next();
                                }
                            }
                            else
                            {
                                temp.push_back(fileReader->getCurrent()->getContent());
                                fileReader->next();
                            }
                        }

                        items.emplace_back(std::make_shared<Token>(temp, Types::TEXT, lineInfo));
                        temp = "";

                        // Move to next it
                        if (!fileReader->isEnd())
                        {
                            fileReader->next();
                        }
                    }

                    if (fileReader->getCurrent() == nullptr)
                    {
                        break;
                    }

                    if (tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::LEFTPARENTHESIS))
                    {
                        AddToken(Types::LEFTPARENTHESIS, lineInfo);
                    }
                    else if (tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::RIGHTPARENTHESIS))
                    {
                        AddToken(Types::RIGHTPARENTHESIS, lineInfo);
                    }
                    else if (tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::SEMICOLON))
                    {
                        AddToken(Types::SEMICOLON, lineInfo);
                    }
                    else if (tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::MULTIPLICATION))
                    {
                        if (tokenManager->fastCompare(fileReader->peak()->getContent(), Types::EQUALS))
                        {
                            fileReader->next();
                            AddToken(Types::MULTIPLICATIONEQUAL, lineInfo);
                        }
                        else
                        {
                            AddToken(Types::MULTIPLICATION, lineInfo);
                        }
                    }
                    else if (tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::DIVISION))
                    {
                        if (!fileReader->isEnd())
                        {
                            if (tokenManager->fastCompare(fileReader->peak()->getContent(), Types::MULTIPLICATION))
                            {
                                fileReader->next();
                                while (!fileReader->isEnd() && fileReader->getCurrent()->getContent() != '\n')
                                {
                                    if (fileReader->isEnd())
                                    {
                                        return items;
                                    }
                                    fileReader->getNext();
                                    if (fileReader->isEnd())
                                    {
                                        return items;
                                    }
                                    if (fileReader->getCurrent()->getContent() == '*')
                                    {
                                        if (!fileReader->isEnd() && fileReader->getNext()->getContent() == '/')
                                        {
                                            break;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                if (tokenManager->fastCompare(fileReader->peak()->getContent(), Types::EQUALS))
                                {
                                    fileReader->next();
                                    AddToken(Types::DIVISIONEQUAL, lineInfo);
                                }
                                else
                                {
                                    AddToken(Types::DIVISION, lineInfo);
                                }
                            }
                        }
                    }
                    else if (tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::MOD))
                    {
                        AddToken(Types::MOD, lineInfo);
                    }
                    else if (tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::ADDITION))
                    {
                        if (tokenManager->fastCompare(fileReader->peak()->getContent(), Types::EQUALS))
                        {
                            fileReader->next();
                            AddToken(Types::ADDITIONEQUAL, lineInfo);
                        }
                        else if (tokenManager->fastCompare(fileReader->peak()->getContent(), Types::ADDITION))
                        {
                            fileReader->next();
                            AddToken(Types::INCREMENT, lineInfo);
                        }
                        else
                        {
                            AddToken(Types::ADDITION, lineInfo);
                        }
                    }
                    else if (tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::SUBTRACTION))
                    {
                        if (tokenManager->fastCompare(fileReader->peak()->getContent(), Types::EQUALS))
                        {
                            fileReader->next();
                            AddToken(Types::SUBTRACTIONEQUAL, lineInfo);
                        }
                        else if (tokenManager->fastCompare(fileReader->peak()->getContent(), Types::SUBTRACTION))
                        {
                            fileReader->next();
                            AddToken(Types::DECREMENT, lineInfo);
                        }
                        else
                        {
                            AddToken(Types::SUBTRACTION, lineInfo);
                        }
                    }
                    else if (tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::EQUALS))
                    {
                        if (!fileReader->isEnd())
                        {
                            if (tokenManager->fastCompare(fileReader->getNext()->getContent(), Types::EQUALS))
                            {
                                AddToken(Types::IFEQUALS, lineInfo);
                            }
                            else
                            {
                                fileReader->prev();
                                AddToken(Types::EQUALS, lineInfo);
                            }
                        }
                        else
                        {
                            AddToken(Types::EQUALS, lineInfo);
                        }
                    }
                    else if (tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::BITWISEAND))
                    {
                        if (!fileReader->isEnd())
                        {
                            if (tokenManager->fastCompare(fileReader->getNext()->getContent(), Types::BITWISEAND))
                            {
                                AddToken(Types::AND, lineInfo);
                            }
                            else
                            {
                                AddToken(Types::BITWISEAND, lineInfo);
                                fileReader->prev();
                            }
                        }
                    }
                    else if (tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::BITWISEOR))
                    {
                        if (!fileReader->isEnd())
                        {
                            if (tokenManager->fastCompare(fileReader->getNext()->getContent(), Types::BITWISEOR))
                            {
                                AddToken(Types::OR, lineInfo);
                            }
                            else
                            {
                                AddToken(Types::BITWISEOR, lineInfo);
                                fileReader->prev();
                            }
                        }
                    }
                    else if (tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::BITWISEXOR))
                    {
                        AddToken(Types::BITWISEXOR, lineInfo);
                    }
                    else if (tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::NOT))
                    {
                        if (!fileReader->isEnd())
                        {
                            if (tokenManager->fastCompare(fileReader->peak()->getContent(), Types::EQUALS))
                            {
                                fileReader->next();
                                AddToken(Types::IFNOTEQUALS, lineInfo);
                            }
                            else
                            {
                                AddToken(Types::NOT, lineInfo);
                            }
                        }
                        else
                        {
                            AddToken(Types::NOT, lineInfo);
                        }
                    }
                    else if (tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::IFLESSTHAN))
                    {
                        if (!fileReader->isEnd())
                        {
                            if (tokenManager->fastCompare(fileReader->peak()->getContent(), Types::EQUALS))
                            {
                                fileReader->next();
                                AddToken(Types::IFLESSTHANOREQUAL, lineInfo);
                            }
                            else if (tokenManager->fastCompare(fileReader->peak()->getContent(), Types::IFLESSTHAN))
                            {
                                fileReader->next();
                                AddToken(Types::LEFTSHIFT, lineInfo);
                            }
                            else
                            {
                                AddToken(Types::IFLESSTHAN, lineInfo);

                            }
                        }
                        else
                        {
                            items.emplace_back(std::make_shared<Token>("<", Types::IFLESSTHAN, lineInfo));
                        }
                    }
                    else if (tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::IFGREATER))
                    {
                        if (!fileReader->isEnd())
                        {
                            if (tokenManager->fastCompare(fileReader->peak()->getContent(), Types::EQUALS))
                            {
                                fileReader->next();
                                AddToken(Types::IFGREATERTHANOREQUAL, lineInfo);
                            }
                            else if (tokenManager->fastCompare(fileReader->peak()->getContent(), Types::IFGREATER))
                            {
                                fileReader->next();
                                AddToken(Types::RIGHTSHIFT, lineInfo);
                            }
                            else
                            {
                                AddToken(Types::IFGREATER, lineInfo);
                            }
                        }
                        else
                        {
                            AddToken(Types::IFGREATER, lineInfo);
                        }
                    }
                    else if (tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::BITWISECOMPLEMENT))
                    {
                        AddToken(Types::BITWISECOMPLEMENT, lineInfo);
                    }
                    else if (tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::SEMICOLON))
                    {
                        AddToken(Types::SEMICOLON, lineInfo);
                    }
                    else if (tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::RIGHTBRACKET))
                    {
                        AddToken(Types::RIGHTBRACKET, lineInfo);
                    }
                    else if (tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::LEFTBRACKET))
                    {
                        AddToken(Types::LEFTBRACKET, lineInfo);
                    }
                    else if (tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::COMMA))
                    {
                        AddToken(Types::COMMA, lineInfo);
                    }
                    else if (tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::LEFTSQUAREBRACKET))
                    {
                        AddToken(Types::LEFTSQUAREBRACKET, lineInfo);
                    }
                    else if (tokenManager->fastCompare(fileReader->getCurrent()->getContent(), Types::RIGHTSQUAREBRACKET))
                    {
                        AddToken(Types::RIGHTSQUAREBRACKET, lineInfo);
                    }
                }
                fileReader->next();
            }
            return items;
        }
    }
}
