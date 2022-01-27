# Vision 2022
Rachet Rockers vision solution for FRC season 2022 "Rapid React"

## Setup guide
- ### Native 
    1. `pip install -r requirements.txt` ensure pip bin directory is added to path
    2. `conan install . -if builddir/conan` or install opencv 4 with your package manager
    3. `meson builddir/`
    4. `meson compile -C builddir/` re-run this command to recompile
- ### Jetson Nano
    1. `conan install . -if builddir/conan -pr:b=resources/conan/profiles/jetson-nano --build missing`
    2. `meson builddir/ --buildtype release --cross-file resources/meson/jetson-nano.ini` use the `--reconfigure` flag if you've already built for native
    3. `meson compile -C builddir/`
    4. `meson compile deploy -C builddir/`

## Resources
- [Jetson nano cross compiler toolchain](https://developer.nvidia.com/embedded/dlc/l4t-gcc-7-3-1-toolchain-64-bit-32-1)
- [What is FIRST?](https://www.firstinspires.org/)

### Coding Conventions
- #### C++
    - Folders and namespaces should be in lowercase
        - example: `sources/include/rr1706/utils/`
    - Files and classes should be in PascalCase
        - example: `RoboRIOClient.cpp`
    - Variables should be in snake_case 
        - example: `double camera_offset;`
    - Functions and methods should be in camelCase 
        - example: `void sendMessage();`
    - Private variables should be prefixed with `_`
        - example: `void _sendMessage();`
    - Private function should be prefixed with `_`
        - example: `double _camera_offset;`
    - Lines shouldn't extend past 120 columns
