# Change as needed.
CC65_DIR := cc65

CC := $(CC65_DIR)/bin/cc65
CA := $(CC65_DIR)/bin/ca65
LD := $(CC65_DIR)/bin/ld65

TARGET_PLATFORM := nes
SRC_DIR := src

TARGETS += quarto.nes

# Change as needed.
EMULATOR ?= mesen/mesen

EXAMPLES := $(TARGETS:.nes=)
C_SOURCES := $(wildcard $(SRC_DIR)/*.c)
ASSEMBLY_SOURCES := $(C_SOURCES:.c=.s)
OBJECTS := $(C_SOURCES:.c=.o)
CRT0_OBJ := lib/crt0.o
CRT0_SRC := lib/crt0.s

.PHONY: all

# Disable builtin rules (for .c, .o) by providing an empty .SUFFIXES rule
# Yes. GNU make is a rat's nest
.SUFFIXES:

# Make sure intermediate files are *NOT* deleted
# Yes. GNU make is a rat's nest
.PRECIOUS: %.s %.o

all: $(CC) $(TARGETS)

# submodule build
$(CC):
	cd $(CC65_DIR) && $(MAKE)

$(EXAMPLES): %: %.nes
	$(EMULATOR) $<

clean:
	@rm -fv $(TARGETS)
	@rm -fv $(OBJECTS)
	@rm -fv $(ASSEMBLY_SOURCES)
	@rm -fv $(CRT0_OBJ)

$(SRC_DIR)/%.s: $(SRC_DIR)/%.c
	$(CC) -g -Oi $< --target $(TARGET_PLATFORM) -I. -I$(CC65_DIR)/include/ --add-source -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.s
	$(CA) $< -g -o $@

$(CRT0_OBJ): $(CRT0_SRC) lib/neslib.s lib/famitone2.s
	$(CA) $< -g -I$(CC65_DIR)/asminc -o $@

%.nes: $(OBJECTS) $(CRT0_OBJ)
	$(LD) --dbgfile $(@F:.nes=.dbg) -C quarto.cfg -o $@ $^ $(TARGET_PLATFORM).lib


