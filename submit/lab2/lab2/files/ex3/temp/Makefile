PROJECT = quadr

SRC_FILES=	main.c\
	   	Makefile\
	   	quadr.c\
	   	README\
		quadr.h\
	   	test.data

CFLAGS = -g -Wall -std=c11
LDFLAGS = -lm

$(PROJECT):	quadr.o main.o
		$(CC) quadr.o main.o $(LDFLAGS) -o $@:

clean:
		rm -f *.o $(PROJECT) $(PROJECT).tar.gz

#creates a tar achive of all the SRC_FILES
dist:	$(PROJECT).tar.gz

#compresses the archive
$(PROJECT).tar.gz:	$(SRC_FILES)
			tar -cf $(PROJECT).tar $(SRC_FILES)
			gzip -f $(PROJECT).tar

depend:
	$(CC) -MM $(CPPFLAGS) *.c

#automatically generated dependencies produced by make depend
main.o: main.c quadr.h
quadr.o: quadr.c quadr.h


