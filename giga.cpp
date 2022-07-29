#include <ncurses.h>
#include "functions.hpp"
#include <string>



int main(){
	initscr();
	noecho();
	raw();
	keypad(stdscr, TRUE);
	print_menu();
	move(0,0);
	int ch;
	int cur_x = 0;
	int cur_y = 0;
	while(TRUE){
		ch = getch();
		if(ch == 24){break;}
		if(ch == 15){write_out("Hello World!");continue;}
		if(ch == 12){goto_line();continue;}
		else{
			addch(ch);
		}
		refresh();
	}
	endwin();
	return 0;
}