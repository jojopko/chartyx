CC = gcc
CF = -g -Wall
LN = -lSDL2 -lSDL2_ttf

BD = build
SD = src
HD = include

HEADERS = \
$(HD)/element_button.h $(HD)/element_container.h $(HD)/element_label.h $(HD)/types.h \
$(HD)/element.h $(HD)/layer.h $(HD)/gui.h 

OM = $(BD)/gui.o $(BD)/element.o $(BD)/layer.o

test: $(BD)/test1 $(BD)/libgui.a

all: $(BD)/libgui.a

#test1
$(BD)/test1: tests/test1.c $(BD)/libgui.a
	$(CC) $(CF) $(LN) -lSDL2_image $< -o $@ -L./build -l:libgui.a

#compile
$(BD)/libgui.a: $(OM)
	ar r $@ $(OM)

$(BD)/gui.o: $(SD)/gui.c $(HEADERS)
	$(CC) $(CF) $(LN) -c $< -o $@

$(BD)/element.o: $(SD)/element.c $(HEADERS)
	$(CC) $(CF) $(LN) -c $< -o $@

$(BD)/layer.o: $(SD)/layer.c $(HEADERS)
	$(CC) $(CF) $(LN) -c $< -o $@