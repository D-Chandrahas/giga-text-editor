#include "my_header.hpp"



void init(){
	initscr();
	noecho();
	raw();
	keypad(stdscr, TRUE);
	print_menu();
	move(0,0);
	refresh();
	return;
}

void print_menu(){
    attron(A_REVERSE);
    mvaddstr(OPN_FLD_1,0,"CTRL + O");
    mvaddstr(OPN_FLD_1,25,"CTRL + X");
	mvaddstr(OPN_FLD_1,50,"CTRL + L");
    attroff(A_REVERSE);
    mvaddstr(OPN_FLD_1,8," Write Out");
    mvaddstr(OPN_FLD_1,33," Exit");
	mvaddstr(OPN_FLD_1,58," Go to Line");
	move(0,0);
    refresh();
    return;
}

void add_btn(char ch,const std::string& btn_name){
	attron(A_REVERSE);
	mvaddstr(OPN_FLD_1,100,"CTRL + ");
	addch(ch);
	attroff(A_REVERSE);
	addch(' ');
	addstr(btn_name.c_str());
	refresh();
	return;
}

void remove_btn(){
	mvaddstr(OPN_FLD_1,100,"                    ");
	refresh();
	return;
}

//change this to take list of strings and write to file
void write_out(const std::string& filepath,const std::string& text){
	int cur_x, cur_y;
	getyx(stdscr, cur_y, cur_x);
	const std::string& new_filepath = take_inp("Enter Filename: ",filepath,32,126,100);
	if(!new_filepath.empty()){
		add_btn('C',"Continue");
		if(!writefile(new_filepath, text)){
			print_inp_fld("Failed to Write File...");
		}
		else{
			print_inp_fld("File Written Successfully!");
		}
		refresh();
		int ch;
		while((ch = getch()) != 3){}
		remove_btn();
		clr_inp_fld();
	}
	move(cur_y, cur_x);
	refresh();
	return;
}

void goto_line(int cur_line,int lines_text){
	int cur_x, cur_y;
	getyx(stdscr, cur_y, cur_x);
	const std::string& inp_line_no = take_inp("Enter Line Number: ",std::to_string(cur_line+1),48,57,9);
	if(inp_line_no.empty()){
		move(cur_y, cur_x);
		refresh();
		return;
	}
	int line_no = stoi(inp_line_no) - 1;
	if(line_no >= lines_text){
		if(lines_text != 0){line_no = lines_text - 1;}
		else{line_no = 0;}
	}
	//scroll text
	move(line_no % INP_FLD,0);
	refresh();
	return;
}

//change this to take list of strings and write to file
bool writefile(const std::string &filepath,const std::string &contents) {
	std::ofstream ofile(filepath,std::ios::trunc);
	if(!ofile){return false;}
	ofile << contents;
	ofile.close();
	return true;
}

void clr_inp_fld(){
	mvaddstr(INP_FLD,0,"                                                                                                                        ");
	refresh();
	return;
}

std::string take_inp(const std::string& prompt,std::string inp,int l_ascii_lim,int u_ascii_lim,int max_len){
	add_btn('C',"Cancel");
	print_inp_fld(prompt);
	print_inp_fld(inp,prompt.length());
	attron(A_REVERSE);
	int ch;
	while((ch = getch()) != '\n'){
		if(ch == '\b'){
			if(!inp.empty()){
    			inp.pop_back();
				attroff(A_REVERSE);
				addstr("\b \b");
				attron(A_REVERSE);
				refresh();
				continue;
			}
			continue;
		}
		if(ch == 3){
			inp.clear();
			break;
		}
		if(ch > u_ascii_lim or ch < l_ascii_lim or inp.length() >= max_len){continue;}
		inp += ch;
		addch(ch);
		refresh();
	}
	attroff(A_REVERSE);
	remove_btn();
	clr_inp_fld();
	return inp;
}

void print_inp_fld(const std::string& msg,int col){
	attron(A_REVERSE);
	mvaddstr(INP_FLD,col,msg.c_str());
	attroff(A_REVERSE);
	refresh();
	return;
}

void readfile(const std::string& filepath, std::list<std::string>& text){}