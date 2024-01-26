# Ricochet

Welcome to Ricochet, a pinball game built in C++17.

## Getting Started

#### Prerequisites
Ensure you have the following installed on your machine:
- C++ compiler (≥ C++17)
- CMake (≥ 3.20)
- vcpkg

#### Build process (Linux)
1. Clone the repository:
	
	```bash
	git clone https://github.com/RMZeroFour/Ricochet.git
	cd Ricochet
	```

2. Build the project with CMake and vcpkg:

	```bash
	cmake -S . -B build --toolchain "<path-to-vcpkg>/scripts/buildsystems/vcpkg.cmake"
	cmake --build build
	```

3. (Optionally) Run unit tests with CTest:
	```bash
	ctest --test-dir build
	```

4. Run the game:

	```bash
	cd build/bin/
	./Ricochet
	```

## Made with

- [CMake](https://cmake.org/) for the buildsystem.
- [vcpkg](https://vcpkg.io/) for package management.
- [SDL2](https://www.libsdl.org/) for _game stuff_.
- [GoogleTest](https://google.github.io/googletest/) for unit testing and mocking.

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE.md) for details.