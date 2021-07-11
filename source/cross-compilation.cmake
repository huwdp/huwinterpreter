# the name of the target operating system
set(CMAKE_SYSTEM_NAME Windows)

 

# which compilers to use
set(CMAKE_C_COMPILER i686-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER i686-w64-mingw32-g++)

set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++ -I$mxe/usr/i686-w64-mingw32.static/include -Wall -Wextra -Wlogical-op -Wuseless-cast -Wdouble-promotion -Wformat=2  -lkernel32 -luser32 -lgdi32 -lshell32 -DGLEW_STATIC=1 -DAL_LIBTYPE_STATIC=1")

set(CMAKE_FIND_ROOT_PATH /usr/i686-w64-mingw32)

# adjust the default behavior of the find commands:
# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)

 

# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)


