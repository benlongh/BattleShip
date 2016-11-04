.PHONY: coverage clean

battleship: Battleship.c
	gcc -Wall Battleship.c -o battleship

coverage:
	gcc -fprofile-arcs -ftest-coverage Battleship.c -o battleship

clean:
	rm -f battleship a.out *.gcov *.gcno *.gcda
