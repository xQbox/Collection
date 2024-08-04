CC := gcc
CFLAGS := -Wall -Werror -Wpedantic -std=c99 -g


app.exe: main.o mtr_alloc.o mtr_io.o mtr_op.o 
	$(CC) -o $@ $^

main.o: main.c *.h
	$(CC) $(CFLAGS) -c $<

mtr_alloc.o: mtr_alloc.c mtr_alloc.h
	$(CC) $(CFLAGS) -c $<

mtr_io.o: mtr_io.c mtr_io.h
	$(CC) $(CFLAGS) -c $<

mtr_op.o: mtr_op.c mtr_op.h
	$(CC) $(CFLAGS) -c $<	


clean:
	rm *.exe *.o
