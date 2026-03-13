csrc = $(shell find csrc -name "*.cpp")
run: 
	@g++ $(csrc)  -Wall -g -I include -o build/demo
	@./build/demo
clean:
	rm -rf build/*
.PHONY: build run clean