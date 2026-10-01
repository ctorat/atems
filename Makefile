#
# Copyright (c) 2026, Apollo Telephone Laboratories.
# Provided under the BSD-3 clause.
#

CONFIG_CHIP = atmc02

CFILES = $(shell find core/ -name "*.c")
CFILES += $(shell find soc/$(CONFIG_CHIP)/ -name "*.c")
OFILES = $(CFILES:.c=.o)
DFILES = $(CFILES:.c=.d)

CC = gcc

CFLAGS =		\
	-Wall		\
	-pedantic	\
	-Ihead

.PHONY: all
all: $(OFILES)
	$(CC) $(OFILES) -o atems

-include $(DFILES)
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
