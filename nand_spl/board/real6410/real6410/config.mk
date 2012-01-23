# PAD_TO used to generate a 4kByte binary needed for the combined image
# -> PAD_TO = CONFIG_SYS_TEXT_BASE + 4096
PAD_TO := $(shell expr $$(($(CONFIG_SYS_TEXT_BASE) + 4096)))

ifeq ($(debug),1)
PLATFORM_CPPFLAGS += -DDEBUG
endif
