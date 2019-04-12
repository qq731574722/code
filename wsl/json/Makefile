CFILES 	= $(wildcard *.c)
OBJS    = $(CFILES:.c=.o)
CC		= gcc
DEFIN	= -Ilibxtest -fprofile-arcs -ftest-coverage
LIBS	= -Llibxtest -lxtest -ldl 
CFLAGS	= $(FLAG) -Wall $(DEFIN)
TARGET	= xtest
COVDIR	= lcov

.PHONY: all clean cleanall libxtest

$(TARGET): $(OBJS) libxtest
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

libxtest:
	(cd libxtest && make)

debug: 
	$(CC) -g -Wall $(DEFIN) -o $(TARGET) $(CFILES) $(LIBS)

clean:
	(cd libxtest && make clean)
	rm -f *.o *.output *.stackdump *.gcov *.gcda *.gcno *.info $(TARGET)
	rm -rf $(COVDIR)
	rm -f *.yaml

install:
	(cd libxtest && make install)
	cp -f $(TARGET) /usr/bin && chmod a+x /usr/bin/$(TARGET)

lcov:
	lcov -c -d . -o json.info
	genhtml -o $(COVDIR) json.info