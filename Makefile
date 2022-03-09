main:
	mkdir -p bin
	gcc src/main.c -o bin/BatNav
	./bin/BatNav

runsrv:
	./bin/BatNav server

runcli:
	./bin/BatNav client