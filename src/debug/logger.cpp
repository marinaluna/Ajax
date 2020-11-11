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
#include <iomanip>
#include <string>


namespace Debug
{

std::string Logger::BLACK_CODE      = "\033[30m";
std::string Logger::RED_CODE        = "\033[31m";
std::string Logger::YELLOW_CODE     = "\033[33m";
std::string Logger::WHITE_CODE      = "\033[37m";
std::string Logger::CYAN_BG_CODE    = "\033[46m";
std::string Logger::RESET_CODE      = "\033[0m";


void Logger::log(std::string str) {
    std::cout << YELLOW_CODE << "LOG: " << RESET_CODE << str << std::endl;
}

void Logger::logErr(std::string err) {
    std::cout << RED_CODE << "ERROR: " << RESET_CODE << err << std::endl;
}

void Logger::logRegs(Reg32* regs[6][16], Reg32* SPSRs[6], Reg32* CPSR) {
    std::cout << YELLOW_CODE << "\tUser\t\tFIQ\t\tSVC\t\tAbort\t\tIRQ\t\tUndef" << std::endl;
    // Print the main regs
    for(int r = 0; r < 16; r++) {
        std::cout << YELLOW_CODE << "r" << std::dec << r << ":\t" << WHITE_CODE;
        
        for(int m = 0; m < 6; m++) {
            /*
            * If the register is a copy of the User
            * mode register, then don't display it
            */
            if(m != 0 && regs[m][r] == regs[0][r]) {
                std::cout << "        \t";
                continue;
            }
            std::cout << std::hex << std::setfill('0') << std::setw(8) << *regs[m][r] << "\t";
        }
        std::cout << std::endl;
    }
    // Print the SPSRs
    std::cout << YELLOW_CODE << "SPSR:\t" << WHITE_CODE;
    for(int m = 0; m < 6; m++) {
        if(m == 0) { // no SPSR for User mode
            std::cout << RED_CODE << "none\t\t" << WHITE_CODE;
            continue;
        }
        std::cout << std::hex << std::setfill('0') << std::setw(8) << *SPSRs[m] << "\t";
    }
    std::cout << std::endl;
    // Print the CPSR
    std::cout << YELLOW_CODE << "CPSR:\t" << WHITE_CODE << std::setfill('0') << std::setw(8) << std::hex << *CPSR << RESET_CODE << std::endl;
}

} // namespace Debug
