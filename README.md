# NTT C++ Core Library

A lightweight C++ core library containing a suite of utilities ranging from assertion tools to format string utilities and more. This library is designed to help streamline everyday tasks and enforce best practices in C++ development.

## Table of Contents

- [NTT C++ Core Library](#ntt-c-core-library)
  - [Table of Contents](#table-of-contents)
  - [Features](#features)
  - [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Installation](#installation)
      - [Build as a separate library](#build-as-a-separate-library)
      - [For CMake projects:](#for-cmake-projects)
  - [Usage](#usage)
    - [Include](#include)
    - [Support features:](#support-features)
  - [Contributing](#contributing)
  - [License](#license)
  - [Acknowledgements](#acknowledgements)

## Features

- **Assertion Utilities:** Provides enhanced assertion macros and functions for debugging during development.
- **Format String Utilities:** Simplifies string formatting more safely and flexibly than C-style formatting.
- **Type Traits and Helpers:** Offers additional compile-time checks and helper templates.
- **Error Handling:** Centralized error reporting and logging utilities.
- **Cross-Platform Support:** Optimized for performance and compatibility across different operating systems.

## Getting Started

### Prerequisites

- A C++ compiler that supports C++14 or above.
- CMake version 3.10 or higher for building the library.
- Standard libraries available with your C++ compiler.
  - MinGW on Windows (can be downloaded from [MSYS2](https://www.msys2.org/))
  - Visual Studio on Windows (version 2019 or later) with C++ support (can be downloaded from [Microsoft](https://visualstudio.microsoft.com/))
  - GCC on Linux (can be installed using package manager)

### Installation

#### Build as a separate library

Clone the repository and include the source directory in your C++ project:

    git clone https://github.com/threezinedine/ntt-lib.git

Change directory to build scripts:

- MinGW:

  - Debug:

    ```bash
      cd ntt-lib
      cd PCBuild/MinGW/Debug
      g.bat # for building the project
      b.bat # for building the project and running the example
      t.bat # for running the tests
      gb.bat # for building the project and running the tests
      bt.bat # for building the project, running the tests
      gbt.bat # for building the project, running the tests
    ```

  - Release:

    ```bash
      cd ntt-lib
      cd PCBuild/MinGW/Release
      g.bat # for building the project
      b.bat # for building the project and running the example
      t.bat # for running the tests
      gb.bat # for building the project and running the tests
      bt.bat # for building the project, running the tests
      gbt.bat # for building the project, running the tests
    ```

  - Visual Studio:

    ```bash
    cd ntt-lib
    cd PCBuild/VisualStudio
    g.bat # for building the project
    cd ../../build
    ```

    Open the solution file in Visual Studio and build the project.

#### For CMake projects:

```cmake
add_subdirectory(ntt-lib)
target_link_libraries(your_project PRIVATE NTTLib)
```

## Usage

### Include

To include the library in your C++ project, add the following line to your source file:

```cpp
  #include <NTTLib.hpp>
```

### Support features:

This library provides a suite of utilities to help streamline everyday tasks and enforce best practices in C++ development. The following features are currently supported:

- [x] Type traits
- [x] Assertion utilities
- [x] String formatting utilities
- [x] Smart pointers
- [x] Console printing utilities
- [ ] Concurrent utilities

## Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository on GitHub.
2. Create a feature branch: `git checkout -b feature/your-feature`.
3. Commit your changes and ensure tests pass.
4. Open a pull request with a detailed description of your changes.

For major changes, please open an issue first to discuss what you would like to change.

## License

This library is licensed under [The Unlicense](https://unlicense.org). See the [LICENSE](LICENSE) file for details.

## Acknowledgements

Thanks to all contributors and open source projects that have inspired this library. Special thanks to ntt for maintaining and continuously improving the library.

If you have any questions or feedback, please send the request to the email threezinedine@gmail.com

Happy coding!
