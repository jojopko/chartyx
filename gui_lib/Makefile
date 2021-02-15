CC = gcc
CF = -g -Wall
LN = -lSDL2 -lSDL2_ttf

BD = build
SD = src
HD = include

HEADERS = \
$(HD)/element_button.h $(HD)/element_container.h $(HD)/element_label.h $(HD)/types.h \
$(HD)/element.h

OM = $(BD)/gui.o $(BD)/element.o

test: $(BD)/test1 $(BD)/libgui.a

all: $(BD)/libgui.a

$(BD)/test1: tests/test1.c
	$(CC) $(CF) $(LN) -lSDL2_image $< -o $@ -L./build -l:libgui.a

$(BD)/libgui.a: $(OM)
	ar r $@ $(OM)

$(BD)/gui.o: $(SD)/gui.c $(HD)/gui.h $(HEADERS)
	$(CC) $(CF) $(LN) -c $< -o $@

$(BD)/element.o: $(SD)/element.c $(HD)/gui.h $(HEADERS)
	$(CC) $(CF) $(LN) -c $< -o $@
