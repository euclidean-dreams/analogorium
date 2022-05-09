cmake_minimum_required(VERSION 3.13)
project(analogorium VERSION 0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(ARM "build for ARM instead of x86 architectures" OFF)

add_compile_options(-Wno-psabi)

include(lib/cmake-utils/dependency-integrator.cmake)

integrate_cmake_dependency(
        NAME cppzmq
        GIT_URL git@github.com:zeromq/cppzmq.git
        GIT_TAG dd663fafd830466d34cba278c2cfd0f92eb67614
)

integrate_cmake_dependency(
        NAME impresario-utils
        GIT_URL git@github.com:impresario-systems/impresario-utils.git
        GIT_TAG origin/dev
)

integrate_cmake_dependency(
        NAME portaudio
        GIT_URL git@github.com:PortAudio/portaudio.git
        GIT_TAG 147dd722548358763a8b649b3e4b41dfffbcfbb6
)

if (ARM)
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
else ()
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
        src/signal/Signal.cpp src/signal/Signal.h src/signal/Essentia.cpp src/signal/Essentia.h src/primordium/SignalConduit.h src/primordium/AudioDeviceSlinger.cpp src/primordium/AudioDeviceSlinger.h src/primordium/RingBuffer.cpp src/primordium/RingBuffer.h src/shapery/Shapery.cpp src/shapery/Shapery.h src/shapery/Shaper.h src/shapery/StftShaper.cpp src/shapery/StftShaper.h src/shapery/tabled/Equalizer.cpp src/shapery/tabled/Equalizer.h src/shapery/AutoGain.cpp src/shapery/AutoGain.h src/shapery/AutoBalance.cpp src/shapery/AutoBalance.h src/shapery/tabled/AutoEqualizer.cpp src/shapery/tabled/AutoEqualizer.h)
list(APPEND TARGETS analogorium)
add_executable(analogorium src/main.cpp ${SOURCE_FILES})

# finalize
foreach (target IN LISTS TARGETS)
    target_include_directories(${target} PRIVATE src)
    target_link_libraries(${target} PRIVATE impresario-utils)
    if (ARM)
        target_include_directories(${target} PRIVATE ${CMAKE_BINARY_DIR}/ne10-src/inc)
        target_link_libraries(${target} PRIVATE NE10)
    else ()
        target_link_libraries(${target} PRIVATE muFFT)
    endif ()
    target_link_libraries(${target} PRIVATE portaudio)
endforeach ()
