CC = g++
OFLAGS = -o 
CFLAGS = -Wall
EFLAGS = valgrind 

lab:
	$(CC) $(CFLAGS) main.cpp source.cpp mersenne_twister.cpp $(OFLAGS) TP
exec :
	$(EFLAGS) ./lab
clean: 
	rm -rf lab