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
#include "../../common/types.h"

#include <memory>


namespace Debug
{
class Logger;
} // namespace Debug

using Reg32 = u32;

namespace Core
{

class Bus;

class ARM7TDMI {
public:
    ARM7TDMI(std::shared_ptr<Core::Bus>& bus, std::shared_ptr<Debug::Logger>& logger);

    int cycle();

private:
    enum MODE {
        User       = 0,
        FIQ        = 1,
        Supervisor = 2,
        Abort      = 3,
        IRQ        = 4,
        Undefined  = 5
    };

    std::shared_ptr<Debug::Logger>  _logger;
    std::shared_ptr<Core::Bus>      _bus;

    /*
    * While these variables hold the true
    * value of the CPU regs, they are
    * never accessed directly. Instead,
    * the 'regs' array is used, which
    * contains pointers to the correct
    * internal registers to use.
    */
    Reg32 __regs[16];
    Reg32 __fiq_HighRegs[7];
    Reg32 __svc_SP_LR[2];
    Reg32 __abt_SP_LR[2];
    Reg32 __irq_SP_LR[2];
    Reg32 __und_SP_LR[2];
    Reg32 __CPSR;
    Reg32 __SPSRs[5];

    /*
    * The following is the regs array that will
    * be used to access the underlying registers.
    * The first dimension can be indexed using the
    * CPU mode, while the second dimension can be
    * indexed using the register number you want.
    */
    Reg32* regs[6][16] = {
        {   
            ////// User //////
            &__regs[0], &__regs[1], &__regs[2], &__regs[3], &__regs[4], &__regs[5], &__regs[6], &__regs[7],
            &__regs[8], &__regs[9], &__regs[10], &__regs[11], &__regs[12], &__regs[13], &__regs[14], &__regs[15]
        },
        {   
            ////// FIQ ///////
            &__regs[0], &__regs[1], &__regs[2], &__regs[3], &__regs[4], &__regs[5], &__regs[6], &__regs[7],
            &__fiq_HighRegs[0], &__fiq_HighRegs[1], &__fiq_HighRegs[2], &__fiq_HighRegs[3], &__fiq_HighRegs[4], &__fiq_HighRegs[5], &__fiq_HighRegs[6], &__regs[15]
        },
        {   
            ////// SVC ///////
            &__regs[0], &__regs[1], &__regs[2], &__regs[3], &__regs[4], &__regs[5], &__regs[6], &__regs[7],
            &__regs[8], &__regs[9], &__regs[10], &__regs[11], &__regs[12], &__svc_SP_LR[0], &__svc_SP_LR[1], &__regs[15]
        },
        {   
            ////// ABT ///////
            &__regs[0], &__regs[1], &__regs[2], &__regs[3], &__regs[4], &__regs[5], &__regs[6], &__regs[7],
            &__regs[8], &__regs[9], &__regs[10], &__regs[11], &__regs[12], &__abt_SP_LR[0], &__abt_SP_LR[1], &__regs[15]
        },
        {   
            ////// IRQ ///////
            &__regs[0], &__regs[1], &__regs[2], &__regs[3], &__regs[4], &__regs[5], &__regs[6], &__regs[7],
            &__regs[8], &__regs[9], &__regs[10], &__regs[11], &__regs[12], &__irq_SP_LR[0], &__irq_SP_LR[1], &__regs[15]
        },
        {   
            ///// UNDEF //////
            &__regs[0], &__regs[1], &__regs[2], &__regs[3], &__regs[4], &__regs[5], &__regs[6], &__regs[7],
            &__regs[8], &__regs[9], &__regs[10], &__regs[11], &__regs[12], &__und_SP_LR[0], &__und_SP_LR[1], &__regs[15]
        }
    };

    /*
    * CPSR pointer, only here for consistency.
    */
    Reg32* CPSR = &__CPSR;

    /*
    * These are the SPSR registers. There is
    * one for each mode except User. When
    * the CPU switches modes, the CPSR is
    * stored into the SPSR of the destination
    * mode, to preserve its state. Then it is
    * swapped back into CPSR upon return to User mode.
    */
    Reg32* SPSRs[6] = {
        nullptr,    // No SPSR for User mode
        &__SPSRs[0],
        &__SPSRs[1],
        &__SPSRs[2],
        &__SPSRs[3],
        &__SPSRs[4],
    };

};

} // namespace Core
