#include "my_header.hpp"


int LINES_TEXT = 0;



int main(int argc, char** argv){

	init();
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