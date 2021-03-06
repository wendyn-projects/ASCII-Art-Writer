SOURCE  = aaw_dbline_fonts.c aaw_grid_fonts.c aaw_round_fonts.c aaw_sline_fonts.c ascii_art_writer.c main.c program.c shell.c
HEADER  = aaw_dbline_fonts.h aaw_grid_fonts.h aaw_round_fonts.h aaw_sline_fonts.h ascii_art_writer.h program.h shell.h

OBJS    = aaw_dbline_fonts.o aaw_grid_fonts.o aaw_round_fonts.o aaw_sline_fonts.o ascii_art_writer.o main.o program.o shell.o
TARGET  = aawriter.run
CC	    = gcc
CFLAGS  = -c -Wall
LFLAGS  = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(TARGET) $(LFLAGS)

aaw_dbline_fonts.o: aaw_dbline_fonts.c
	$(CC) $(CFLAGS) aaw_dbline_fonts.c 

aaw_grid_fonts.o: aaw_grid_fonts.c
	$(CC) $(CFLAGS) aaw_grid_fonts.c 

aaw_round_fonts.o: aaw_round_fonts.c
	$(CC) $(CFLAGS) aaw_round_fonts.c 
	
aaw_sline_fonts.o: aaw_sline_fonts.c
	$(CC) $(CFLAGS) aaw_sline_fonts.c 

ascii_art_writer.o: ascii_art_writer.c
	$(CC) $(CFLAGS) ascii_art_writer.c 

main.o: main.c
	$(CC) $(CFLAGS) main.c 

program.o: program.c
	$(CC) $(CFLAGS) program.c 

shell.o: shell.c
	$(CC) $(CFLAGS) shell.c 


clean:
	rm -f $(OBJS) $(TARGET)
