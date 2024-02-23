# /make/deteck-os.mk
#
# Reference:
#   <https://stackoverflow.com/questions/714100/os-detecting-makefile>
#

# Detect build platform
ifeq ($(OS),Windows_NT)
    $(error We doesn't support Windows)
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CFLAGS += -D HOST_OS_LINUX
    endif
    ifeq ($(UNAME_S),Darwin)
        CFLAGS += -D HOST_OS_OSX
    endif
endif
