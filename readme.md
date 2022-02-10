# Vision 2022
Ratchet Rockers vision solution for FRC season 2022 "Rapid React"

## Adding platforms
This project should already support Windows/x64, Linux/x64, & Linux/arm64
To add additional platforms you'll need to cross compile opencv using the following commands.
```
cmake -S . -B builddir/ -DBUILD_SHARED_LIBS=OFF -DBUILD_TEST=OFF -DBUILD_PERF_TEST=OFF \
-DCMAKE_BUILD_TYPE=Release -DBUILD_opencv_highgui=OFF -DBUILD_FAT_JAVA_LIB=ON -DBUILD_opencv_python3=OFF \
-DBUILD_JAVA=ON
```
Then run `cmake --build builddir/ --parallel` after that get the file `builddir/lib/libopencv-java<version>.<so/dll/dynlib>`
and place it in `vision/src/vendor/opencv/<platform>/<arch>`

## Resources
- [Jetson nano cross compiler toolchain](https://developer.nvidia.com/embedded/dlc/l4t-gcc-7-3-1-toolchain-64-bit-32-1)
- [Custom images for Jetson nano](https://pythops.com/post/create-your-own-image-for-jetson-nano-board)
- [What is FIRST?](https://www.firstinspires.org/)
