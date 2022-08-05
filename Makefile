build: format
	cmake -S. -Bbuild && cmake --build build

format: src include
	git add .
	git-clang-format
	git add .

.PHONY: build