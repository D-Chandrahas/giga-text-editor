#include <ncurses.h>

int main(){
	initscr(); /* Start curses mode */
	noecho(); /* Don't echo characters */
	raw(); /* Line buffering disabled */
	keypad(stdscr, TRUE); /* Use keypad */
	int xmax, ymax;
	getmaxyx(stdscr, ymax, xmax); /* Get screen size */
	printw("%d %d\n%d %d\n",LINES,COLS,ymax,xmax); /* Print size of screen */
	addch('C' | A_REVERSE);
	int ch;
	addch('\n');
	for(int i = 0; i < COLS; i++){
				addch(' ');
			}
			addch('\n');
			refresh();

	while((ch = getch())!='`'){
		printw("%d", ch);
		refresh();
	} /* Wait for user input */
	endwin(); /* End curses mode */
	return 0;
}