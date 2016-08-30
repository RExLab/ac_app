cmd_Release/obj.target/panel/src/gpio.o := g++ '-DNODE_GYP_MODULE_NAME=panel' '-D_LARGEFILE_SOURCE' '-D_FILE_OFFSET_BITS=64' '-DBUILDING_NODE_EXTENSION' -I/root/.node-gyp/0.12.6/src -I/root/.node-gyp/0.12.6/deps/uv/include -I/root/.node-gyp/0.12.6/deps/v8/include -I../node_modules/nan  -fPIC -pthread -Wall -Wextra -Wno-unused-parameter -O3 -ffunction-sections -fdata-sections -fno-tree-vrp -fno-omit-frame-pointer -fno-rtti -fno-exceptions -MMD -MF ./Release/.deps/Release/obj.target/panel/src/gpio.o.d.raw  -c -o Release/obj.target/panel/src/gpio.o ../src/gpio.cc
Release/obj.target/panel/src/gpio.o: ../src/gpio.cc ../src/gpioclass.h
../src/gpio.cc:
../src/gpioclass.h:
