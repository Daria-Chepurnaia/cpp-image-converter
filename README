
# ImgConverter: A Cross-Platform Image Conversion Tool


ImgConverter is a C++ image conversion tool that supports JPEG, BMP, and PPM formats. This educational project was created to enhance my skills in C++ programming and image processing.


## Table of Contents
1. [Features](#features)
2. [Installation](#installation)
3. [Usage](#usage)
4. [Building from Source](#building-from-source)
5. [Dependencies](#dependencies)
6. [License](#license)

---

## Features

- **Supports multiple formats**: ImgConverter supports the JPEG, BMP, and PPM image formats, enabling flexible image conversions across common formats.
- **Cross-platform compatibility**: The tool builds on Windows and Linux, leveraging the CMake build system for streamlined cross-platform support.
- **Integration with LibJPEG**: ImgConverter integrates `LibJPEG`, demonstrating proficiency in configuring and using external C libraries within a C++ project.
- **Efficient build management**: Debug and Release configurations are supported with optimization flags to maximize performance in production while retaining debugging capabilities during development.

---

## Installation

### Prerequisites
1. Ensure **CMake** (minimum version 3.11) is installed.
2. Ensure **LibJPEG** library is available on your system. Instructions to build it from source are provided below if necessary.

### Clone the Repository
```bash
git clone git@github.com:Daria-Chepurnaia/cpp-image-converter.git
cd ImgConverter
```

---

## Usage

### Command-line Conversion
ImgConverter can be used to convert images from one format to another:

```bash
imgconv <input_file> <output_file>
```

For example:
```bash
imgconv input_image.jpg output_image.ppm
```

If the conversion is successful, the output message will confirm the completion.

---

## Building from Source

### Step 1: Set Up and Compile LibJPEG

To ensure smooth integration, build and install the `LibJPEG` library. Here’s a quick guide:

1. Download the source code for `LibJPEG` (e.g., `jpegsr.tar.gz` for Linux or `jpegsr.zip` for Windows).
2. Extract the archive and run the configuration script:
   ```bash
   mkdir build
   cd build
   ../configure --enable-shared=no CPPFLAGS="-O3" CFLAGS="-O3"
   ```
3. Compile the library:
   ```bash
   make
   ```

### Step 2: Build ImgConverter with CMake

1. Create a build directory and configure the project:
   ```bash
   mkdir debug
   cd debug
   cmake ../ImgConverter -DCMAKE_BUILD_TYPE=Debug -DLIBJPEG_DIR=<path_to_LibJPEG>
   ```
2. Compile the project:
   ```bash
   cmake --build .
   ```


---

## Dependencies

1. **LibJPEG**: Provides support for JPEG image decoding. Required to build and link successfully with ImgConverter.
2. **CMake**: Cross-platform build system.
3. **Compiler with C++17 support**: Required for modern C++ features used in this project.

---

## License

This project is licensed under the MIT License. See [LICENSE](https://github.com/Daria-Chepurnaia/cpp-image-converter/blob/master/LICENSE) for more information.
