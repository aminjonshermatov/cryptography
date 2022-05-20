CC := gcc
FILE := dsa

all:
	$(CC) $(FILE).c \
		lib/BigDigits/bigd.c \
		lib/BigDigits/bigdigits.c \
		lib/BigDigits/bigdtypes.h \
		-o $(FILE)

clear:
	rm $(FILE)