#include "my_header.hpp"

//add open new file button by transfering code in main() into a new function called start_interface(string& filename)
// and putting start_interface() in a infinite loop in main and when new file btn is pressed change filename and return;
//filename variable is outside loop
//implement exit by having a bool exit=start_interface(filename) (or) start_interface(filename,bool& exit) and if exit break;

//make them global variables and replace wherever they can be replaced
int main(int argc, char** argv){
	std::list<std::string> text;
	std::string filepath = "";
	if(argc > 1){
		filepath = argv[1];
		readfile(filepath,text);
	}
	int ch;
	int cur_x = 0;
	int cur_y = 0;
	int lines_text = text.size();
	int cur_y_text = 0;
	int cur_x_text = 0;
	init();
	render_full(text,0);
	move(0,0);

	while(TRUE){
		ch = getch();
		if(ch == 24){break;}
		if(ch == 15){write_out(filepath,text);continue;}
		if(ch == 12){goto_line(text,cur_y_text,lines_text);continue;}
		else{
			addch(ch);
		}
		refresh();
	}
	endwin();
	return 0;
}