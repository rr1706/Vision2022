# Vision 2022

Rachet Rockers vision solution for FRC season 2022 "Rapid React"

## Setup guide

1. `pip install -r requirements.txt`
2. Add python module bin directory to path
3. `meson builddir/`
4. `meson compile -C builddir/`

#### To deploy

1. `meson builddir/ --cross-file resources/meson/jetson-nano.ini`
2. `meson compile -C builddir/`
3. `meson compile deploy -C builddir/`

## Resources

[Jetson nano cross compiler toolchain](https://developer.nvidia.com/embedded/dlc/l4t-gcc-7-3-1-toolchain-64-bit-32-1)
