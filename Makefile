SRC := $(wildcard src/*.cpp src/screens/*.cpp)
BUILD_DIR := build
OUT := $(BUILD_DIR)/housematch
SERVER_OUT := $(BUILD_DIR)/housematch_server

.PHONY: dev build server server-build clean

build:
	mkdir -p $(BUILD_DIR)
	skm clang++ $(SRC) -Iinclude -std=c++17 -o $(OUT)

dev: build
	./$(OUT); mv -f myeasylog.log $(BUILD_DIR)/ 2>/dev/null || true

server-build:
	mkdir -p $(BUILD_DIR)
	skm clang++ server/server.cpp -std=c++17 -o $(SERVER_OUT)

server: server-build
	./$(SERVER_OUT); mv -f myeasylog.log $(BUILD_DIR)/ 2>/dev/null || true

clean:
	rm -rf $(BUILD_DIR)