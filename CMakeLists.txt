cmake_minimum_required(VERSION 3.13)
project(analogorium VERSION 0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# turn one of these on
option(_arm "build for arm" OFF)
option(_arm64 "build for arm64" OFF)
option(_x86 "build for x86" OFF)

add_compile_options(-Wno-psabi)

include(lib/cmake-utils/dependency-integrator.cmake)

integrate_cmake_dependency(
        NAME impresario-utils
        GIT_URL git@github.com:impresario-systems/impresario-utils.git
        GIT_TAG origin/flow
)

if (_arm)
    SET(GNULINUX_PLATFORM ON)
    SET(NE10_LINUX_TARGET_ARCH armv7)
    set(CMAKE_POLICY_DEFAULT_CMP0048 NEW)
    SET(NE10_ENABLE_MATH OFF)
    SET(NE10_ENABLE_PHYSICS OFF)
    SET(NE10_ENABLE_IMGPROC OFF)
    SET(NE10_BUILD_EXAMPLES OFF)
    integrate_cmake_dependency(
            NAME ne10
            GIT_URL git@github.com:projectNe10/Ne10.git
            GIT_TAG 1f059a764d0e1bc2481c0055c0e71538470baa83
    )
endif ()
if (_arm64)
    SET(GNULINUX_PLATFORM ON)
    SET(NE10_LINUX_TARGET_ARCH aarch64)
    set(CMAKE_POLICY_DEFAULT_CMP0048 NEW)
    SET(NE10_ENABLE_MATH OFF)
    SET(NE10_ENABLE_PHYSICS OFF)
    SET(NE10_ENABLE_IMGPROC OFF)
    SET(NE10_BUILD_EXAMPLES OFF)
    integrate_cmake_dependency(
            NAME ne10
            GIT_URL git@github.com:projectNe10/Ne10.git
            GIT_TAG 1f059a764d0e1bc2481c0055c0e71538470baa83
    )
endif ()
if (_x86)
    add_compile_definitions(USE_MUFFT)
    SET(MUFFT_ENABLE_FFTW OFF)
    integrate_cmake_dependency(
            NAME mufft
            GIT_URL git@github.com:Themaister/muFFT.git
            GIT_TAG 47bb08652eab399c2c7d460abe5184857110f130
    )
endif ()

set(
        SOURCE_FILES
        src/Config.h

        src/primordium/AudioDeviceSlinger.cpp src/primordium/AudioDeviceSlinger.h
        src/primordium/RingBuffer.cpp src/primordium/RingBuffer.h
        src/primordium/SignalConduit.h

        src/signal/Signal.cpp src/signal/Signal.h
        src/signal/Essentia.cpp src/signal/Essentia.h

        src/shapery/Shaper.h
        src/shapery/Shapery.cpp src/shapery/Shapery.h
        src/shapery/StftShaper.cpp src/shapery/StftShaper.h
        src/shapery/AutoBalance.cpp src/shapery/AutoBalance.h

        # unsorted
)
list(APPEND TARGETS analogorium)
add_executable(analogorium src/main.cpp ${SOURCE_FILES})

# finalize
foreach (target IN LISTS TARGETS)
    target_include_directories(${target} PRIVATE src)
    target_link_libraries(${target} PRIVATE impresario-utils)
    if (_arm OR _arm64)
        target_include_directories(${target} PRIVATE ${CMAKE_BINARY_DIR}/ne10-src/inc)
        target_link_libraries(${target} PRIVATE NE10)
    endif ()
    if (_x86)
        target_link_libraries(${target} PRIVATE muFFT)
    endif ()
    target_include_directories(${target} PRIVATE /opt/homebrew/Cellar/portaudio/19.7.0/include)
    target_link_libraries(${target} PRIVATE /opt/homebrew/Cellar/portaudio/19.7.0/lib/libportaudio.2.dylib)
endforeach ()
