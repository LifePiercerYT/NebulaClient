# Use a '>' instead of a TAB for iPhone editing
.RECIPEPREFIX = >

TARGET      := NebulaClient
SOURCES     := src
INCLUDES    := include

ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment.")
endif

include $(DEVKITPRO)/wut/share/wut.mk

# Compiler Flags
CFLAGS      += -O2 -Wall -fms-extensions
CXXFLAGS    += $(CFLAGS)
LIBS        := -lwups -lwut

.PHONY: all clean

all: $(TARGET).wps

$(TARGET).wps: $(TARGET).rpx
>@echo "Creating Aroma Plugin: $@"
>@cp $(TARGET).rpx $(TARGET).wps

# Compile all .cpp files from the src folder
$(TARGET).rpx:
>@$(CXX) $(CXXFLAGS) -I$(INCLUDES) $(LDFLAGS) $(SOURCES)/*.cpp -o $@ $(LIBS)

clean:
>@echo "Cleaning project..."
>@rm -f *.wps *.rpx *.elf
