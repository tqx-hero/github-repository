#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
//curses的helloworld
int main(){
	initscr();
	move(5,15);
	printw("%s","Hello World!");
	refresh();
	sleep(2);
	endwin();
	return 0;
}
