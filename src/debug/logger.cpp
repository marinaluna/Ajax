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
#include "logger.h"

#include <iostream>
#include <string>


namespace Debug
{

std::string Logger::RED_CODE     = "\033[31m";
std::string Logger::YELLOW_CODE  = "\033[33m";
std::string Logger::RESET_CODE   = "\033[0m";

void Logger::log(std::string str) {
    std::cout << YELLOW_CODE << "LOG: " << RESET_CODE << str << std::endl;
}

void Logger::logErr(std::string err) {
    std::cout << RED_CODE << "ERROR: " << RESET_CODE << err << std::endl;
}

} // namespace Debug
