NAME=emulator
BUILD_DIR=build

all: compile

.PHONY: cmake
cmake:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. -DCMAKE_BUILD_TYPE=Debug

.PHONY: cmake-release
cmake-release:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. -DCMAKE_BUILD_TYPE=Release

.PHONY: compile
compile: cmake
	@cd $(BUILD_DIR) && make

.PHONY: release
release: cmake-release
	@cd $(BUILD_DIR) && make

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)
