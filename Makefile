.RECIPEPREFIX = >

TARGET      := NebulaClient
# This tells the compiler to look in BOTH the root and src/include folders
SOURCES     := . src
INCLUDES    := . include

ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment.")
endif

include $(DEVKITPRO)/wut/share/wut.mk

CFLAGS      += -O2 -Wall -fms-extensions
CXXFLAGS    += $(CFLAGS)
LIBS        := -lwups -lwut

.PHONY: all clean

all: $(TARGET).wps

$(TARGET).wps: $(TARGET).rpx
>@echo "Creating Aroma Plugin: $@"
>@cp $(TARGET).rpx $(TARGET).wps

$(TARGET).rpx:
# This searches for any .cpp file in the root OR src folder
>@$(CXX) $(CXXFLAGS) -I. -Iinclude $(LDFLAGS) *.cpp src/*.cpp -o $@ $(LIBS) 2>/dev/null || $(CXX) $(CXXFLAGS) -I. -Iinclude $(LDFLAGS) *.cpp -o $@ $(LIBS)

clean:
>@echo "Cleaning project..."
>@rm -f *.wps *.rpx *.elf
