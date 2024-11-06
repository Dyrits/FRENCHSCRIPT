clean:
	rm -rf build

build: clean
	cmake -S . -B build
	cmake --build build/

run:
	cmake --build build/
	./build/frs

compile:
	cmake --build build/
	./build/frs ./main.frs

