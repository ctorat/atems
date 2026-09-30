#
# Copyright (c) 2026, Apollo Telephone Laboratories.
# Provided under the BSD-3 clause.
#

CFILES = $(shell find core/ -name "*.c")
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
