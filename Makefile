MODULE := sort_tests
EXE := $(MODULE).elf

SRC_DIR = src
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = gcc

CPPFLAGS = -Iinclude

MAPFILE := "output.map"

DEBUG := -g
OPTIMIZATION := -flto -O3 -fdata-sections -ffunction-sections -march=native \
-Wl,--gc-sections -Wl,--print-gc-sections -Wl,--cref -Wl,-Map=$(MAPFILE)
WARNINGS := -Wall -Wextra -pedantic -D_FORTIFY_SOURCE=1 -Wformat-overflow=2 \
-Wformat-security -Wformat-truncation=2
OTHER := $(OPTIMIZATION) $(WARNINGS)
CFLAGS := $(DEBUG) $(OTHER)

LDFLAGS =
LDLIBS =

$(EXE): $(OBJ)
	@echo "Building target: $@"
	@echo "Invoking: GCC C Linker"
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $(OBJ) $(LDLIBS)
	@echo "Finished building target: $@"
	@echo " "

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@echo "Building file: $<"
	@echo "Invoking GCC C Compiler"
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c -o"$@" "$<"
	@echo "Finished building> $<"
	@echo " "

.PHONY: clean

clean:
	$(RM) $(EXE) $(OBJ) $(MAPFILE)
