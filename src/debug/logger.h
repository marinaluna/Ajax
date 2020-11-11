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
#include "../common/types.h"

#include <string>


using Reg32 = u32;

namespace Debug
{

class Logger {
private:
    static std::string BLACK_CODE;
    static std::string RED_CODE;
    static std::string YELLOW_CODE;
    static std::string WHITE_CODE;
    static std::string CYAN_BG_CODE;
    static std::string RESET_CODE;

public:
    void log(std::string str);
    void logErr(std::string err);
    void logRegs(Reg32* regs[6][16], Reg32* SPSRs[6], Reg32* CPSR);
};

} // namespace Debug
