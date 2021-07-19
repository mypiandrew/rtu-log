all: rtu

rtu: 
	gcc rtu.c -o rtu -lsqlite3 -lmodbus -lm 

clean:
	rm -rf *.o rtu
