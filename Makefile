.RECIPEPREFIX = >

TARGET      := NebulaClient
SOURCES     := .
# CHANGED: Look in root (.) for headers
INCLUDES    := .

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
>@$(CXX) $(CXXFLAGS) -I$(INCLUDES) $(LDFLAGS) *.cpp -o $@ $(LIBS)

clean:
>@echo "Cleaning project..."
>@rm -f *.wps *.rpx *.elf
