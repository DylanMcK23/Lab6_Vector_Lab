CC=gcc
CFLAGS=-Wall
LDFLAGS=
SOURCES= ui.c vect_math.c vect_storage.c main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=math

all: $(SOURCES) $(EXECUTABLE)

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
	$(CC) -MM $< > $*.d

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) *.d