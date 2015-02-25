OUTPUT = threads

SOURCES.c = main.c threads.c

CFLAGS += -g -Wall
LDLIBS += -lpthread

FILES = file1 file2 file3 file4 file5 file6 file7

all: $(OUTPUT)

$(OUTPUT): $(SOURCES.c) $(SOURCES.h)
	$(LINK.c) $(LDLIBS) -o $(OUTPUT) $(SOURCES.c)

run:
	./$(OUTPUT) $(FILES)

clean:
	$(RM) $(OUTPUT) $(FILES)