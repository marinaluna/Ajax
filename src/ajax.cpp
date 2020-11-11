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
#include <iostream>
#include <fstream>
#include <string>
#include <locale>

#include "core/gba.h"
#include "utils/strutils.h"
#include "common/types.h"
#include "debug/logger.h"


void printUsage(const char* path_to_exec) {
    std::cout << "Usage: " << path_to_exec << " bios_path rom_path [--skip-bios=bool] [--scale=int]" << std::endl;
}

int main(int argc, char** argv) {
    if(argc < 3) {
        printUsage(argv[0]);
        return -1;
    }
    std::string biosPath = std::string(argv[1]);
    std::string romPath = std::string(argv[2]);

    /*
    ************ Opens the BIOS file ************
    */
    if(Utils::getExtension(biosPath) != "bin") {
        std::cout << "BIOS must be a .bin file!" << std::endl;
        return -1;
    }

    u8* bios;
    std::ifstream biosStream (biosPath, std::ios::binary | std::ios::ate);
    int bios_size;
    if(biosStream.good()) {
        bios_size = biosStream.tellg();
        bios = (u8*) malloc(bios_size);
        biosStream.seekg(0, std::ios_base::beg);
        biosStream.read(reinterpret_cast<char*>( bios ), bios_size);
        biosStream.close();
    } else {
        std::cout << "Error while opening BIOS!" << std::endl;
        return -1;
    }

    /*
    ************ Opens the ROM file ************
    */
    std::string rom_ext = Utils::getExtension(romPath);
    if(rom_ext != "gba") {
        std::cout << "Unable to open rom with extension ." << rom_ext << "!" << std::endl;
        return -1;
    }

    u8* rom;
    std::ifstream romStream (romPath, std::ios::binary | std::ios::ate);
    int rom_size;
    if(romStream.good()) {
        rom_size = romStream.tellg();
        rom = (u8*) malloc(rom_size);
        romStream.seekg(0, std::ios_base::beg);
        romStream.read(reinterpret_cast<char*>( rom ), rom_size);
        romStream.close();
    } else {
        std::cout << "Error while opening ROM!" << std::endl;
        return -1;
    }

    /*
    ************ Parses the options ************
    */
    Core::GBA::Options options;
    if(argc > 2) { // we have options!
        for(int i = 3; i < argc; i++) {
            std::string fullarg = std::string(argv[i]);

            std::vector<std::string> split_args = Utils::strSplit(fullarg, '=');
            if(split_args.size() != 2) { // Args must be in format arg=arg_par
                printUsage(argv[0]);
                return -1;
            }

            ////////////SKIP BIOS///////////////
            //// Usage: --skip-bios=bool ///////
            ////////////////////////////////////
            if(split_args[0] == "--skip-bios") {
                if(Utils::strToLower(split_args[1]) == "true") {
                    options.skip_bios = true;
                    std::cout << "Skipping BIOS!" << std::endl;
                }
                else if(Utils::strToLower(split_args[1]) == "false") {
                    options.skip_bios = false;
                    std::cout << "Not skipping BIOS!" << std::endl;
                }
                else {
                    printUsage(argv[0]);
                    return -1;
                }
            }
            ////////////SCALE///////////////////
            //// Usage: --scale=int ////////////
            ////////////////////////////////////
            else if(split_args[0] == "--scale") {
                options.scale = atoi(split_args[1].c_str());
                if(options.scale == 0 || options.scale > 4)
                    options.scale = 1;
                std::cout << "Set scale to " << options.scale << "!" << std::endl;
            }
        }
    }

    std::shared_ptr<Debug::Logger> logger = std::shared_ptr<Debug::Logger>( new Debug::Logger() );

    Core::GBA* gba = new Core::GBA(bios, rom, options, logger);

    return 0;
}
