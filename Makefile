ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
    EXE_EXT := .exe
    RUN_PATH := build/src/$(CONFIG)/capirepl$(EXE_EXT)
    NUM_CORES := $(NUMBER_OF_PROCESSORS)
else
    DETECTED_OS := $(shell uname -s)
    EXE_EXT :=
    RUN_PATH := build/src/capirepl$(EXE_EXT)
    
    ifeq ($(DETECTED_OS),Darwin)
        NUM_CORES := $(shell sysctl -n hw.ncpu)
    else
        NUM_CORES := $(shell nproc)
    endif
endif

CONFIG ?= Debug

# Auto-correct lowercase input variants
ifeq ($(CONFIG),debug)
    CONFIG := Debug
endif
ifeq ($(CONFIG),release)
    CONFIG := Release
endif

.DEFAULT_GOAL := build

.PHONY: help
help: ## Display this help screen
	@grep -E '^[a-z.A-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

.PHONY: clean
clean: ## Clean build files
	cmake -E rm -rf build

.PHONY: build
build: ## Build using the selected configuration
	cmake -S . -B build -DCMAKE_BUILD_TYPE=$(CONFIG)
	cmake --build build --config $(CONFIG) -j$(NUM_CORES)

.PHONY: rebuild
rebuild: clean build ## Clean and rebuild from scratch

.PHONY: run
run: build ## Build and run the executable cross-platform
	$(RUN_PATH)