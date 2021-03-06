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
#include "arm7tdmi.h"
#include "../memory/bus.h"
#include "../../debug/logger.h"

#include <memory>


namespace Core
{

ARM7TDMI::ARM7TDMI(std::shared_ptr<Core::Bus>& bus, std::shared_ptr<Debug::Logger>& logger)
:   _bus    (bus),
    _logger (logger) {

    _logger->log("Created ARM7TDMI!");
    _logger->logRegs(regs, SPSRs, CPSR);
}



} // namespace Core
