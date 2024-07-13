cmake_minimum_required(VERSION 3.20)
project(nostdlib LANGUAGES C)

option(NOC_BUILD_TESTS "Also build unittests" ON)

set(NOC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(NOC_SOURCES_DIR ${PROJECT_SOURCE_DIR}/src)

add_library(noc
    ${NOC_SOURCES_DIR}/abs.c
    ${NOC_SOURCES_DIR}/buf.c
    ${NOC_SOURCES_DIR}/countdigits.c
    ${NOC_SOURCES_DIR}/from_str.c
    ${NOC_SOURCES_DIR}/char.c
    ${NOC_SOURCES_DIR}/io.c
    ${NOC_SOURCES_DIR}/memory.c
    ${NOC_SOURCES_DIR}/flt_charcount.c
    ${NOC_SOURCES_DIR}/fmt/sprintf/impls.c
    ${NOC_SOURCES_DIR}/fmt/helpers.c
    ${NOC_SOURCES_DIR}/fmt/parser.c
    ${NOC_SOURCES_DIR}/string.c
    ${NOC_SOURCES_DIR}/to_str.c

    # ${NOC_SOURCES_DIR}/fmt/sscanf.c

    ${NOC_INCLUDE_DIR}/nostdlib/rc.h
    ${NOC_INCLUDE_DIR}/nostdlib/numeric/flt_charcount.h
    ${NOC_INCLUDE_DIR}/nostdlib/numeric/to_str.h
    ${NOC_INCLUDE_DIR}/nostdlib/numeric/from_str.h
    ${NOC_INCLUDE_DIR}/nostdlib/numeric/abs.h
    ${NOC_INCLUDE_DIR}/nostdlib/numeric/countdigits.h
    ${NOC_INCLUDE_DIR}/nostdlib/memory.h
    ${NOC_INCLUDE_DIR}/nostdlib/version.h
    ${NOC_INCLUDE_DIR}/nostdlib/sys/posix.h
    ${NOC_INCLUDE_DIR}/nostdlib/limits.h
    ${NOC_INCLUDE_DIR}/nostdlib/platform.h
    ${NOC_INCLUDE_DIR}/nostdlib/types.h
    ${NOC_INCLUDE_DIR}/nostdlib/bits.h
    ${NOC_INCLUDE_DIR}/nostdlib/_internal/fmt/sprintf/impls.h
    ${NOC_INCLUDE_DIR}/nostdlib/_internal/fmt/helpers.h
    ${NOC_INCLUDE_DIR}/nostdlib/_internal/fmt/parser.h
    ${NOC_INCLUDE_DIR}/nostdlib/string.h
    ${NOC_INCLUDE_DIR}/nostdlib/char.h
    ${NOC_INCLUDE_DIR}/nostdlib/macros.h
    ${NOC_INCLUDE_DIR}/nostdlib/math/round.h
    ${NOC_INCLUDE_DIR}/nostdlib/math/mod.h
    ${NOC_INCLUDE_DIR}/nostdlib/io.h
    ${NOC_INCLUDE_DIR}/nostdlib/buf.h
)

target_compile_features(
    noc PRIVATE c_std_11
)

target_include_directories(
    noc PRIVATE ${PROJECT_SOURCE_DIR}/include
)

# TODO(i.akkuzin): Remove when we finally implement math library by our self [2024/07/06]
target_link_libraries(noc PRIVATE m)

if(NOC_BUILD_TESTS)
    enable_testing()
    find_package(nocheck CONFIG REQUIRED)
    foreach(NOC_TEST_SOURCE
        ${PROJECT_SOURCE_DIR}/tests/test_memory.c
    )
        get_filename_component(NOC_TEST_NAME ${NOC_TEST_SOURCE} NAME_WE)
        add_executable(${NOC_TEST_NAME} ${NOC_TEST_SOURCE})

        target_link_libraries(
            ${NOC_TEST_NAME}
            PRIVATE nocheck::nocheck
        )

        target_compile_features(${NOC_TEST_NAME} PRIVATE c_std_11)

        add_test(${NOC_TEST_NAME} ${NOC_TEST_NAME})
    endforeach()
endif()

install(TARGETS noc PUBLIC_HEADER)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
