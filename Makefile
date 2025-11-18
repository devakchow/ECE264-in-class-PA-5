CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRCS = student.c bmp.c tree.c
OBJS = $(SRCS:.c=.o)
EXEC = practicum

INPUT_DIR = inputs
EXPECTED_DIR = expected
OUTPUT_DIR = outputs

INPUTS := $(wildcard $(INPUT_DIR)/*)

OUTPUTS := $(patsubst $(INPUT_DIR)/%, $(OUTPUT_DIR)/%, $(INPUTS))

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

test: prep_outputs $(OUTPUTS) diff

prep_outputs:
	mkdir -p $(OUTPUT_DIR)

$(OUTPUT_DIR)/%: $(INPUT_DIR)/%
	./$(EXEC) $< $@

diff:
	@echo "Running diff on all tests..."
	@for f in $(INPUTS); do \
		base=$$(basename $$f); \
		echo "Checking $$base..."; \
		diff -q $(OUTPUT_DIR)/$$base $(EXPECTED_DIR)/$$base || \
			(echo "❌ Test failed: $$base" && exit 1); \
	done
	@echo "🎉 All tests passed!"

clean:
	rm -f $(EXEC) $(OBJS)
	rm -rf $(OUTPUT_DIR)

.PHONY: all test clean diff prep_outputs
