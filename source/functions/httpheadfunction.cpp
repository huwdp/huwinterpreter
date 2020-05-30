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

#ifdef EMSCRIPTEN
#else
#include "httpheadfunction.h"

namespace HuwInterpreter {
    namespace Functions {
        HttpHeadFunction::HttpHeadFunction(std::shared_ptr<HuwInterpreter::Passable> passable)
            : Function(passable)
        {
            setName("httpHead");
        }

        std::shared_ptr<Variable> HttpHeadFunction::execute(std::shared_ptr<Tokens::Token> token, std::shared_ptr<Variables::Scope> globalScope,
                                             std::shared_ptr<Variables::Scope> scope,
                                             std::vector<std::shared_ptr<Nodes::Node>> arguments)
        {
            if (arguments.size() > 0 && arguments.size() <= 2)
            {
                std::shared_ptr<Nodes::Node> uriNode = arguments.at(0);
                std::shared_ptr<Nodes::Node> postArgumentsNode = nullptr;
                std::shared_ptr<Variable> postArguments = nullptr;

                if (arguments.size() == 2)
                {
                    postArgumentsNode = arguments.at(1);
                    if (postArgumentsNode == nullptr)
                    {
                        return nullVariable;
                    }
                    postArguments = postArgumentsNode->execute(globalScope, scope);
                }

                if (uriNode == nullptr)
                {
                    return nullVariable;
                }

                std::shared_ptr<Variable> uri = uriNode->execute(globalScope, scope);


                if (uri == nullptr)
                {
                    return nullVariable;
                }

                CURL *curl = curl_easy_init();
                if (curl)
                {
                    curl_easy_setopt(curl, CURLOPT_URL, uri->toString().c_str());
                    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1);
                    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 10);
                    curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1);

                    std::string response_string;
                    std::string header_string;
                    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
                    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
                    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

                    curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);

                    if (postArguments != nullptr)
                    {
                        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postArguments->toString().c_str());
                    }

                    char* url;
                    long response_code;
                    double elapsed;
                    //curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
                    //curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
                    //curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

                    auto res = curl_easy_perform(curl);

                    //if (res != CURLE_OK)
                    //{
                    //    std::string error(curl_easy_strerror(res));
                    //    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                    //    passable->getErrorManager()->add("curl_easy_perform failed: " + error);
                    //    return nullVariable;
                    //}

                    curl_easy_cleanup(curl);

                    curl = nullptr;

                    std::shared_ptr<Variable> output = std::make_shared<HashTableVariable>(passable);
                    std::shared_ptr<DoubleVariable> responseCodeVar = std::make_shared<DoubleVariable>(passable, response_code);
                    std::shared_ptr<DoubleVariable> elapsedVar = std::make_shared<DoubleVariable>(passable, elapsed);
                    std::shared_ptr<StringVariable> responseStringVar = std::make_shared<StringVariable>(passable, response_string);
                    std::shared_ptr<StringVariable> headerStringVar = std::make_shared<StringVariable>(passable, header_string);
                    output->set("response_code", std::move(responseCodeVar), nullptr);
                    output->set("elapsed", std::move(elapsedVar), nullptr);
                    output->set("response_string", std::move(responseStringVar), nullptr);
                    output->set("header_string", std::move(headerStringVar), nullptr);

                    curl_global_cleanup();
                    return output;
                }
                curl_global_cleanup();
            }
            return nullVariable;
        }
    }
}
#endif
