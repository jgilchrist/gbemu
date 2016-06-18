NAME=emulator
BUILD_DIR=build

all: compile run

.PHONY: cmake
cmake:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. -DCMAKE_BUILD_TYPE=Debug

.PHONY: compile
compile: cmake
	@cd $(BUILD_DIR) && make

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)

.PHONY: run
run:
	@./$(BUILD_DIR)/$(NAME)
