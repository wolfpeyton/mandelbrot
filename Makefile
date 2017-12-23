all: parallel

parallel: parallel.c
    gcc -pthread $^ -o $@

.PHONY: clean
clean:
    rm -rf *.o *~ parallel *.pbm