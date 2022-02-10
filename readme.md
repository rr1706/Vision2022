# Vision 2022
Rachet Rockers vision solution for FRC season 2022 "Rapid React"

Looking for a lighter serialization method

## Setup guide
`apt install build-essential python3-pip cmake pkg-config-aarch64-linux-gnu`
- ### Native 
    1. `pip install -r requirements.txt` ensure pip bin directory is added to path
    2. `meson builddir/`
    3. `meson compile -C builddir/` re-run this command to recompile
- ### Jetson Nano
    1. `pip install -r requirements.txt` ensure pip bin directory is added to path
    2. `meson builddir/ --buildtype release --cross-file resources/meson/jetson-nano.ini`
    3. `meson compile -C builddir/` re-run this command to recompile
    4. `meson compile deploy -C builddir/` To deploy if you're connected to the nano

## Resources
- [Jetson nano cross compiler toolchain](https://developer.nvidia.com/embedded/dlc/l4t-gcc-7-3-1-toolchain-64-bit-32-1)
- [Custom images for Jetson nano](https://pythops.com/post/create-your-own-image-for-jetson-nano-board)
- [Yocto](https://medium.com/techbeatly/baking-custom-linux-images-for-embedded-devices-using-yocto-925b3b225c54)
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
