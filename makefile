csrc = $(shell find csrc -name "*.cpp")
build: clean
	@mkdir build
run: build
	g++ $(csrc) -I include -o build/demo
	./build/demo
clean:
	rm -rf build
.PHONY: build run clean