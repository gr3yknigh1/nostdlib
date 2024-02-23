#
# Makefile
#
# TODO: Update devdoc
#
# Requirements
#
#   * gcc
#   * clang-tidy
#   * clang-format
#   * cppcheck
#   * compiledb
#
# HOW TO USE
#
# $ make all   # builds all lib
# $ make test  # builds and runs all unittests
# $ make tests # builds all unittests
#
# $ make lint  # runs linters on all sources: clang-tidy cppcheck clang-format (in check mode)
# $ make fmt   # (or make format) formats all sources
#
# $ make clean # removes all binaries, compile_commands.json
#
# ADDITIONAL BUILD OPTIONS
#
# DEBUG_MODE
#
# If you what to build something with debug info enabled, add BUILD_CONFIG=DEBUG environment variable before run make.
#
# Example:
#
# $ BUILD_CONFIG=DEBUG make all   # builds lib with debug info enabled
# $ BUILD_CONFIG=DEBUG make test  # builds tests and run them with debug info enabled
#
# SANITIZERS
#
# If you what to build with sanitizers, add USE_SANITIZE=<name-of-sanitizer> environment variable before run make.
#
# Note: Currently only address sanitizer is available.
#
# EXAMPLE:
#
# $ USE_SANITIZE=ADDRESS make all   # builds lib with address sanitizer
# $ USE_SANITIZE=ADDRESS make test  # builds tests and run them with address sanitizer
#


PHONY := \
	default all build \
	install uninstall \
	format fmt lint \
	test tests \
	gcov_report \
	clean

ALL       :=
CLEAN     :=
UNINSTALL :=

RM := rm -rf

THIS_MAKE_FILE     := $(abspath $(lastword $(MAKEFILE_LIST)))
THIS_MAKE_FILE_DIR := $(realpath $(patsubst %/,%,$(dir $(THIS_MAKE_FILE))))

SRCROOT  := $(THIS_MAKE_FILE_DIR)


default: all


# ============== [ COMPILATION ] ==============
#
CC       := clang
CFLAGS   := -Wall -Wextra -pedantic -std=c2x
INCFLAGS := -I $(SRCROOT)/include
LDFLAGS  := -lm
AR       := ar
ARFLAGS  := rcs

ifeq ($(BUILD_CONFIG), DEBUG)
    CFLAGS += -O0 -g -D CONFIG_DEBUG
else
    CFLAGS += -Werror -O2 -D CONFIG_RELEASE
endif

ifeq ($(USE_SANITIZE), ADDRESS)
    CFLAGS += -fsanitize=address
endif

ifeq ($(USE_SANITIZE), LEAK)
    CFLAGS += -fsanitize=leak
endif

ifeq ($(WITH_COVERAGE), yes)
    CFLAGS += -fprofile-arcs
    CFLAGS += -ftest-coverage
endif


include $(SRCROOT)/make/detect-os.mk
include $(SRCROOT)/make/platform.mk
include $(SRCROOT)/make/tools.mk


# ================== [ NOSTDLIB ] ===================
#
#
LIBNOC_DIR   := $(SRCROOT)/src
LIBNOC_INC   := $(SRCROOT)/include/nostdlib
LIBNOC_BIN   := libnoc.a

LIBNOC_SRCS   := \
    $(LIBNOC_DIR)/fmt/sprintf/impls.c \
    $(LIBNOC_DIR)/fmt/parser.c \
    $(LIBNOC_DIR)/fmt/helpers.c \
    $(LIBNOC_DIR)/io.c \
    $(LIBNOC_DIR)/from_str.c \
    $(LIBNOC_DIR)/to_str.c \
    $(LIBNOC_DIR)/char.c \
    $(LIBNOC_DIR)/abs.c \
    $(LIBNOC_DIR)/countdigits.c \
    $(LIBNOC_DIR)/flt_charcount.c \
    $(LIBNOC_DIR)/string.c \
    $(LIBNOC_DIR)/memory.c

LIBNOC_HDRS := \
	$(wildcard $(LIBNOC_INC)/*.h) \
	$(wildcard $(LIBNOC_INC)/**/*.h)

LIBNOC_OBJS := $(patsubst $(LIBNOC_DIR)/%.c, $(LIBNOC_DIR)/%.o, $(LIBNOC_SRCS))


$(LIBNOC_BIN): $(LIBNOC_OBJS)
	$(AR) $(ARFLAGS) $(LDFLAGS) $@ $^


$(LIBNOC_DIR)/%.o: $(LIBNOC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCFLAGS) -c $^ -o $@


ALL     += $(LIBNOC_BIN)
CLEAN   += $(LIBNOC_OBJS) $(LIBNOC_BIN)


# ================== [ UNIT TESTING ] ===================
#
#
TEST_DIR  := $(LIBNOC_DIR)/tests
TEST_SRCS :=
TEST_BINS := $(patsubst $(TEST_DIR)/%.c, $(TEST_DIR)/%.bin, $(TEST_SRCS))


CLEAN += $(TEST_BINS)

TEST_CFLAGS :=

# NOTE: Unused
ifeq ($(TEST_MODE), NOFORK)
    TEST_CFLAGS += -D CK_NOFORK
endif

TEST_LDFLAGS := $(shell pkg-config --cflags --libs check)

$(TEST_DIR)/%.bin: $(TEST_DIR)/%.c $(LIBNOC_BIN)
	$(CC) $(CFLAGS) $^ -o $@ $(TEST_LDFLAGS) $(LDFLAGS)


all: $(ALL)


build: $(LIBNOC_BIN)


tests: $(TEST_BINS)


test: $(TEST_BINS)
	@for test in $(TEST_BINS); do $$test ; done


ifeq ($(PREFIX),)
    PREFIX := /usr
endif


INSTALL_LIB_DIR    := $(DESTDIR)$(PREFIX)/lib
INSTALL_LIB        := $(INSTALL_LIB_DIR)/$(LIBNOC_BIN)

INSTALL_INC_DIR    := $(DESTDIR)$(PREFIX)/include/nostdlib
INSTALL_HDRS       := $(patsubst $(LIBNOC_INC)/%, $(INSTALL_INC_DIR)/%, $(LIBNOC_HDRS))

UNINSTALL += \
	$(INSTALL_LIB) \
	$(INSTALL_INC_DIR) \
	$(INSTALL_PKGCFG)


install: $(INSTALL_HDRS) $(INSTALL_LIB)

uninstall:
	$(RM) $(UNINSTALL)

$(INSTALL_INC_DIR):
	install -d $@

$(INSTALL_LIB_DIR):
	install -d $@

$(INSTALL_INC_DIR)/%: $(LIBNOC_INC)/% $(INSTALL_INC_DIR)
	install -d $(shell dirname $@)
	install -m 755 $< $(shell dirname $@)

$(INSTALL_LIB): $(LIBNOC_BIN) $(INSTALL_LIB_DIR)
	install -m 755 -D $< $@

LCOV_REPORT  := $(SRCROOT)/s21_string.lcov_report
COV_HTML_OUT := $(SRCROOT)/out

CLEAN += \
	$(wildcard $(SRCROOT)/*.gcov $(TEST_DIR)/*.gcov) \
	$(wildcard $(SRCROOT)/*.gcda $(TEST_DIR)/*.gcda) \
	$(wildcard $(SRCROOT)/*.gcno $(TEST_DIR)/*.gcno) \
	$(COV_HTML_OUT) \
	$(LCOV_REPORT)

gcov_report:
	$(MAKE) clean
	$(MAKE) BUILD_CONFIG=DEBUG WITH_COVERAGE=yes all tests
	$(MAKE) test
	lcov -t s21_string -o $(LCOV_REPORT) -c -d .
	genhtml -o $(COV_HTML_OUT) $(LCOV_REPORT)

clean:
	$(RM) $(CLEAN)

lint: run-clang-format run-cppcheck

format fmt: run-clang-reformat

.PHONY: $(PHONY)
