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

#include "filetokenmanager.h"

namespace HuwInterpreter {
    namespace Tokens {
        FileTokenManager::FileTokenManager(std::string input)
        {
            std::ifstream file (input.c_str());
            std::string line;
            long long lineNumber = 0;
            if (file.is_open())
            {
                while(std::getline(file, line))
                {
                    ++lineNumber;
                    for (std::string::iterator it = line.begin(); it != line.end(); ++it)
                    {
                        std::shared_ptr<IO::FileLine> fileLine = std::make_shared<IO::FileLine>((*it), lineNumber);
                        lines.emplace_back(std::move(fileLine));
                    }
                }

                if (lines.size() > 0)
                {
                    it = lines.begin();
                }
                else
                {
                    it = lines.end();
                }
                file.close();
            }
        }

        std::shared_ptr<IO::FileLine> FileTokenManager::getCurrent()
        {
            if (it != lines.end())
            {
                return (*it);
            }
            return nullToken;
        }

        std::shared_ptr<IO::FileLine> FileTokenManager::getNext()
        {
            if (it != lines.end())
            {
                ++it;
            }
            if (it != lines.end())
            {
                return (*it);
            }
            return nullToken;
        }

        std::shared_ptr<IO::FileLine> FileTokenManager::getPrev()
        {
            if (it != lines.begin() && it != lines.end())
            {
                --it;
                return (*it);
            }
            return nullToken;
        }

        void FileTokenManager::next()
        {
            if (it != lines.end())
            {
                ++it;
            }
        }

        void FileTokenManager::prev()
        {
            if (it != lines.begin() && it != lines.end())
            {
                --it;
            }
        }

        std::shared_ptr<IO::FileLine> FileTokenManager::peak()
        {
            if (it != lines.end())
            {
                ++it;
                if (it == lines.end())
                {
                    return nullToken;
                }
                std::shared_ptr<IO::FileLine> line = (*it);
                --it;
                return line;
            }
            std::shared_ptr<IO::FileLine> null;
            return nullToken;
        }

        bool FileTokenManager::isEnd()
        {
            if (it != lines.end())
            {
                return false;
            }
            return true;
        }

        bool FileTokenManager::isEmpty()
        {
            if (lines.size() == 0)
            {
              return true;
            }
            return false;
        }
    }
}
