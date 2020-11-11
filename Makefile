BINARY := build/ajax
SRCS := $(shell find . -iname "*.cpp")
OBJS := $(addprefix build/,$(SRCS:.cpp=.o))

NEEDED_LIBS := 

CXX := g++ -flto
LD := $(CXX) $(addprefix libs/,$(NEEDED_LIBS))
override CXXFLAGS += -std=c++11
override LDFLAGS += $(CXXFLAGS)

all:$(BINARY)

$(BINARY):$(OBJS) $(addprefix libs/,$(NEEDED_LIBS))
	$(LD) $(LDFLAGS) -o $@ $^

build/%.o:%.cpp
	$(CXX) -O2 -c $(CXXFLAGS) $< -o $@

run:$(BINARY)
	@$(BINARY) roms/gba_bios.bin roms/armwrestler.gba
	
clean:
	rm -rf build/*
	mkdir -p build/src/
	mkdir -p build/src/core
	mkdir -p build/src/core/memory
	mkdir -p build/src/core/cpu
	mkdir -p build/src/utils
	mkdir -p build/src/debug
