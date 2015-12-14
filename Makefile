all: compile

cmake:
	@mkdir -p build
	@cd build && cmake ..

compile: cmake
	@cd build && make

clean:
	@rm -rf build

.PHONY: cmake compile clean
