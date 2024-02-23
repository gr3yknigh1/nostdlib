# /make/platform.mk
#

BUILD_PLATFORM ?= Linux

ifeq ($(BUILD_PLATFORM),Linux)
	CFLAGS += -D NOC_PLATFORM_LINUX
else
	$(error Unsupported platform)
endif
