NAME=emulator
BUILD_DIR=build

all: compile run

cmake:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake ..

compile: cmake
	@cd $(BUILD_DIR) && make

clean:
	@rm -rf $(BUILD_DIR)

run:
	./$(BUILD_DIR)/$(NAME)


.PHONY: cmake compile clean
