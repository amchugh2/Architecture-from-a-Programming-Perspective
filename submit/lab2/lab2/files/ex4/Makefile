PROJECT = key-value

SRC_FILES= key-value.c\
		key-value.h\
		main.c\
		Makefile\
		process-file.c\
		process-file.h\
		README

CFLAGS = -g -Wall -std=c11
LDFLAGS = -lm

$(PROJECT):	key-value.o main.o process-file.o
		$(CC) key-value.o main.o process-file.o $(LDFLAGS) -o $@

clean:
	rm -f *.o $(PROJECT) $(PROJECT).tar.gz

dist:			$(PROJECT).tar.gz

$(PROJECT).tar.gz:	$(SRC_FILES)	
			tar -cf $(PROJECT).tar $(SRC_FILES)
			gzip -f $(PROJECT).tar

depend:
	$(CC) -MM $(CPPFLAGS) *.c

main.o: main.c key-value.c process-file.c
key-value.o: key-value.c key-value.h
process-file.o: process-file.c process-file.h
