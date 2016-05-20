CC = gcc -O3 -Wall -g -I /app/hdfs/include -L /app/hdfs/lib/native -L /app/jdk1.7.0_45/jre/lib/amd64/server

RECO_SRC = $(wildcard *.c)
DEBUG = -DDEBUG -DDEBUG_INFO -DDEBUG_DEBUG -Wall
LIBS = -lm -lpthread -lhdfs -ljvm

all: $(RECO_SRC)
                $(CC) -o hdfstest  $(RECO_SRC) $(DEBUG) $(LIBS)
.SUFFIXES: .c.o
        .c.o:
                $(CC) -c -o $@ $< $(DEBUG) $(LIBS)


clean :
        find ./ -name "*.*o" -exec rm -f {} +
        rm -f hdfstest 
