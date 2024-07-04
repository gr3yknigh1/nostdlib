cmake_minimum_required(VERSION 3.20)
project(nostdlib LANGUAGES C)

add_library(
    noc

    ${PROJECT_SOURCE_DIR}/src/abs.c
    ${PROJECT_SOURCE_DIR}/src/countdigits.c
    ${PROJECT_SOURCE_DIR}/src/from_str.c
    ${PROJECT_SOURCE_DIR}/src/char.c
    ${PROJECT_SOURCE_DIR}/src/io.c
    ${PROJECT_SOURCE_DIR}/src/memory.c
    ${PROJECT_SOURCE_DIR}/src/flt_charcount.c
    ${PROJECT_SOURCE_DIR}/src/fmt/sprintf/impls.c
    ${PROJECT_SOURCE_DIR}/src/fmt/helpers.c
    # ${PROJECT_SOURCE_DIR}/src/fmt/sscanf.c
    ${PROJECT_SOURCE_DIR}/src/fmt/parser.c
    ${PROJECT_SOURCE_DIR}/src/string.c
    ${PROJECT_SOURCE_DIR}/src/to_str.c

    # Headers
    ${PROJECT_SOURCE_DIR}/include/nostdlib/rc.h
    ${PROJECT_SOURCE_DIR}/include/nostdlib/numeric/flt_charcount.h
    ${PROJECT_SOURCE_DIR}/include/nostdlib/numeric/to_str.h
    ${PROJECT_SOURCE_DIR}/include/nostdlib/numeric/from_str.h
    ${PROJECT_SOURCE_DIR}/include/nostdlib/numeric/abs.h
    ${PROJECT_SOURCE_DIR}/include/nostdlib/numeric/countdigits.h
    ${PROJECT_SOURCE_DIR}/include/nostdlib/memory.h
    ${PROJECT_SOURCE_DIR}/include/nostdlib/version.h
    ${PROJECT_SOURCE_DIR}/include/nostdlib/sys/posix.h
    ${PROJECT_SOURCE_DIR}/include/nostdlib/limits.h
    ${PROJECT_SOURCE_DIR}/include/nostdlib/platform.h
    ${PROJECT_SOURCE_DIR}/include/nostdlib/types.h
    ${PROJECT_SOURCE_DIR}/include/nostdlib/bits.h
    ${PROJECT_SOURCE_DIR}/include/nostdlib/_internal/fmt/sprintf/impls.h
    ${PROJECT_SOURCE_DIR}/include/nostdlib/_internal/fmt/helpers.h
    ${PROJECT_SOURCE_DIR}/include/nostdlib/_internal/fmt/parser.h
    # ${PROJECT_SOURCE_DIR}/include/nostdlib/_internal/fmt/sscanf.h
    ${PROJECT_SOURCE_DIR}/include/nostdlib/string.h
    ${PROJECT_SOURCE_DIR}/include/nostdlib/char.h
    ${PROJECT_SOURCE_DIR}/include/nostdlib/macros.h
    ${PROJECT_SOURCE_DIR}/include/nostdlib/math/round.h
    ${PROJECT_SOURCE_DIR}/include/nostdlib/math/mod.h
    ${PROJECT_SOURCE_DIR}/include/nostdlib/io.h
    ${PROJECT_SOURCE_DIR}/include/nostdlib/buf.h
)

target_compile_features(
    noc PRIVATE c_std_11
)

target_include_directories(
    noc PRIVATE ${PROJECT_SOURCE_DIR}/include
)
