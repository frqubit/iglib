# IGLib

Isometric Graphics Library (IGLib) is an SFML-based library for creating isometric visuals. I started this project when learning about SFML and C++. It's sat abandoned for a while, but I'm now picking it back up to add more features and polish it up.

**WARNING:** This library is in VERY early development, and is not ready for use.

## Features

### Shapes

| Feature | Status |
| --- | --- |
| Cubes | :heavy_check_mark: |
| Rectangular prisms | :heavy_check_mark: |
| Slopes and pyramids | :hourglass: |
| Spheres | :x: |

### Visuals

| Feature | Status |
| --- | --- |
| Textures | :heavy_check_mark: |
| Animation | :hourglass: |
| Lighting | :x: |
| Shadows | :x: |
| Special effects | :x: |

### Motion

| Feature | Status |
| --- | --- |
| Translation | :heavy_check_mark: |
| Scaling | :hourglass: |
| Rotation | :x: |

### Input

| Feature | Status |
| --- | --- |
| Mouse | :hourglass: |
| Keyboard | :x: |

### Other

| Feature | Status |
| --- | --- |
| Collision detection | :x: |
| Physics | :x: |

## Usage

### Prerequisites

- SFML
- CMake (3.0 or higher)
- C++ compiler (must support C++11)
- Make (technically optional, but it's what the build script uses)

### Building (Linux)

```bash
git clone https://github.com/cryptikkUS/iglib
cd iglib

# build.sh does the following for you
cmake -S . -B build
make -C build -j$(nproc)
```

### What about Windows?

Windows is supported, but I don't have a build process for it. This is planned.
