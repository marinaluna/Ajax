//Copyright (C) 2020 Marina Terry

//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at

//  http://www.apache.org/licenses/LICENSE-2.0

//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
#include "strutils.h"
#include <locale>


namespace Utils
{

std::string strToLower(std::string in_str) {
    std::locale loc;
    std::string retval = "";
    for(int c = 0; c < in_str.length(); c++) {
        retval += std::tolower(in_str[c], loc);
    }
    return retval;
}

std::vector<std::string> strSplit(std::string in_str, char del) {
    std::vector<std::string> retvec;
    int pos;
    while((pos = in_str.find(del)) != std::string::npos) {
        retvec.push_back(in_str.substr(0, pos));
        in_str = in_str.substr(pos+1);
    }
    if(in_str != "")
        retvec.push_back(in_str);
    return retvec;
}

std::string getExtension(std::string in_str) {
    return in_str.substr(in_str.find_last_of(".") + 1);
}

} // namespace Utils
