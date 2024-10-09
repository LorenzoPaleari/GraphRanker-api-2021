# Variables
CC = gcc
TARGET = executable
SRC = $(wildcard *.c)

# Default CFLAGS
CFLAGS = -Wall -Werror -O2 -g3 -std=c11

# Detect the operating system
UNAME_S := $(shell uname -s)

# Adjust CFLAGS based on the operating system
ifeq ($(UNAME_S), Darwin)
    # macOS specific flags
    CFLAGS +=
else
    # Other OS specific flags
    CFLAGS += -static -s
endif

# Temporary folder for test outputs
TEMP_DIR = ./temp

# Rules
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)
	rm -rf $(TARGET).dSYM
	rm -rf $(TEMP_DIR)

clean_tmp:
	rm -rf $(TEMP_DIR)

# Create temp directory if it doesn't exist
$(TEMP_DIR):
	mkdir -p $(TEMP_DIR)

# Test rules for open and private test cases
test_open: $(TARGET) clean_tmp $(TEMP_DIR)
	@for i in {1..6}; do \
		if [ -f ./open/input/input_$$i.txt ] && [ -f ./open/output/output_$$i.txt ]; then \
			echo "Testing open case $$i..."; \
			./$(TARGET) < ./open/input/input_$$i.txt > $(TEMP_DIR)/output_$$i.txt; \
			if diff $(TEMP_DIR)/output_$$i.txt ./open/output/output_$$i.txt >/dev/null; then \
				echo "Test $$i passed"; \
			else \
				echo "Test $$i failed"; \
			fi; \
		fi; \
	done

test_private: $(TARGET) clean_tmp $(TEMP_DIR)
	@for i in {1..6}; do \
		if [ -f ./private/input/input_$$i.txt ] && [ -f ./private/output/output_$$i.txt ]; then \
			echo "Testing private case $$i..."; \
			./$(TARGET) < ./private/input/input_$$i.txt > $(TEMP_DIR)/output_$$i.txt; \
			if diff $(TEMP_DIR)/output_$$i.txt ./private/output/output_$$i.txt >/dev/null; then \
				echo "Test $$i passed"; \
			else \
				echo "Test $$i failed"; \
			fi; \
		fi; \
	done

# Test everything (open and private cases)
test_all: test_open test_private

# Valgrind
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET) < ./open/input/input_1.txt

# Callgrind
callgrind: $(TARGET)
	valgrind --tool=callgrind --callgrind-out-file=callgrind_$(shell date +%Y%m%d_%H%M%S) ./$(TARGET) < ./private/input/input_5.txt

.PHONY: all clean test_open test_private test_all valgrind callgrind
