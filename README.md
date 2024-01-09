# Ricochet

Welcome to Ricochet, a pinball game built in C++17.

Uses CMake for the buildsystem, Conan for package management, and SDL2 for _game stuff_.

## Getting Started

#### Prerequisites
Ensure you have the following installed on your machine:
- C++ compiler (≥ C++17)
- CMake (≥ 3.19)
- Conan (≥ 2.0)

#### Build process (Linux)
1. Clone the repository:
    
    ```bash
    git clone https://github.com/RMZeroFour/Ricochet.git
    cd Ricochet
    ```

2. Install dependencies with Conan:
    
    ```bash
    conan install . -b missing
    ```

3. Configure CMake and build the project:

    ```bash
    cmake --preset conan-release
    cmake --build --preset conan-release
    ```

4. Run the game:

    ```bash
    cd build/bin/Release/
    ./Ricochet
    ```

## Made with

- [CMake](https://cmake.org/)
- [Conan](https://conan.io/)
- [SDL2](https://www.libsdl.org/)

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE.md) for details.