CONFIG ?= Debug

.DEFAULT_GOAL := build

.PHONY: help
help: ## Display this help screen
	@grep -E '^[a-z.A-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

.PHONY: clean
clean: ## Clean build files
	rm -fr build

.PHONY: build
build: ## Build using the selected configuration
	cmake -S . -B build -DCMAKE_BUILD_TYPE=$(CONFIG)
	cmake --build build --config $(CONFIG) -j$$(nproc)

.PHONY: rebuild
rebuild: clean build ## Clean and rebuild from scratch

.PHONY: run
run: build ## Build and run the executable
	./build/src/$(CONFIG)/capirepl.exe
