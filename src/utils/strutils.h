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
#pragma once
#include <string>
#include <vector>

namespace Utils
{

std::string strToLower(std::string in_str);
std::vector<std::string> strSplit(std::string in_str, char del);
std::string getExtension(std::string in_str);

} // namespace Utils
