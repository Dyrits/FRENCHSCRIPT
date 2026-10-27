# Frenchscript

A work-in-progress programming language with French keywords, and its own compiler written in C++.

**Status:** work in progress (exploratory project)

## About The Project

An exploratory project: creating a programming language (Frenchscript) whose keywords are French - `sortir`, `retourner`, `entier`, `si`, `sinon_si`, `sinon`, `tant_que`, `alors` - together with its compiler. `main.frs` holds a sample program.

### Built With

- C++20
- CMake
- Docker (optional)

## Getting Started

### Prerequisites

- CMake 3.20+ and a C++20 compiler, or Docker

### Build and run

```sh
make build            # configure and build into build/
make run file=main.frs
```

The compiler binary is `build/frs`; pass it a `.frs` source file:

```sh
./build/frs main.frs
```

### With Docker

```sh
make docker-run       # builds the image and runs it interactively
```

## License

No license file is present in this repository.

## Contact

Dyrits - https://github.com/Dyrits
