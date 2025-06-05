#CMD
CXX = g++

#OPTIONS
GRAPHLIB ?= vulkan
MODE ?= debug

#LINKER
LIBDIRS = C:/VulkanSDK/1.3.283.0/lib includes/GLFW/lib-mingw-w64
LFLAGS := $(foreach dir,$(LIBDIRS),-L$(dir))
lFLAGS = -lglfw3 -lvulkan-1 -lgdi32 -luser32 -lkernel32

#INCLUDES
IFLAGS = C:/VulkanSDK/1.3.283.0/Include includes/GLFW/include includes/GLM src/$(GRAPHLIB)

#FLAGS
VULKANFLAGS = -DGRAPHIC_LIB_VULKAN
DEBUGFLAGS = -g
RELEASEFLAGS = -DNDEBUG
FLAGS = -std=c++17
CXXFLAGS = 
ifeq ($(MODE),debug)
	CXXFLAGS += $(DEBUGFLAGS)
else ifeq ($(MODE),release)
	CXXFLAGS += $(RELEASEFLAGS)
endif
ifeq ($(GRAPHLIB),vulkan)
	CXXFLAGS += $(VULKANFLAGS)
endif
CXXFLAGS += $(foreach dir,$(IFLAGS),-I$(dir))

#FILES
EXEPATH = bin/x64/
EXE = $(EXEPATH)$(MODE)/$(GRAPHLIB)_app
SRCS := src/main.cpp $(wildcard src/$(GRAPHLIB)/**/*.cpp)
OBJS := $(patsubst src/%.cpp, build/%.o, $(SRCS))

all : $(EXE)

run : $(EXE)
	$(EXE).exe

$(EXE) : $(OBJS)
	$(CXX) $(LFLAGS) -o $(EXE) $(OBJS) $(lFLAGS)

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean:
	rm -f $(OBJS)


