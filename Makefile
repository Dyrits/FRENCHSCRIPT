clean:
	rm -rf build

build: clean
	cmake -S . -B build
	cmake --build build/

run:
	cmake --build build/
	./build/frs $(file)

compile:
	cmake --build build/
	./build/frs $(file)

docker-build:
	docker build -t frs ./

docker-run: docker-build
	docker run -it frs

