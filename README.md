### libpath ###
Python (os.path) like, c++ path library

### 开这个坑的理由是：###

* Python 的 os.path 库比较好用（个人感受）。
* C++ 并没有找到比较好用的路径库

* 基于以上非常充分的理由，开个坑，造个轮子，但愿不会烂尾。


### build static library: ###

    $ cmake .
    $ make

### build for ios device static library: ###
    $ cmake . -DCMAKE_TOOLCHAIN_FILE=toolchain/ios.cmake -DIOS_PLATFORM=OS

### build for ios simulator static library: ###
    $ cmake . -DCMAKE_TOOLCHAIN_FILE=toolchain/ios.cmake -DIOS_PLATFORM=SIMULATOR

### build for ios 64bit simulator static library: ###
    $ cmake . -DCMAKE_TOOLCHAIN_FILE=toolchain/ios.cmake -DIOS_PLATFORM=SIMULATOR64

### build for android: ###
    $ cmake . -DCMAKE_TOOLCHAIN_FILE=toolchain/android.toolchain.cmake  \
    		  -DANDROID_NDK=<your ndk path>								\
    		  -DANDROID_ABI=<armeabi or armeabi-v7a ... >				
example:<br>
```
$ cmake . -DCMAKE_TOOLCHAIN_FILE=toolchain/android.toolchain.cmake -DANDROID_NDK=/Users/xiaochen/Develop/crystax-ndk-10.2.1 -DANDROID_TOOLCHAIN_NAME=arm-linux-androideabi-4.9 -DANDROID_NATIVE_API_LEVEL=8 -DANDROID_ABI=armeabi
```