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

void write_out(const std::string& filepath,const std::list<std::string>& text){
	int cur_x, cur_y;
	getyx(stdscr, cur_y, cur_x);
	const std::string& new_filepath = take_inp("Enter Filename: ",filepath,32,126,100);
	if(!new_filepath.empty()){
		if(!writefile(new_filepath, text)){
			ctn_btn("Failed to Write File...");
		}
		else{
			ctn_btn("File Written Successfully!");
		}
	}
	move(cur_y, cur_x);
	refresh();
	return;
}

void goto_line(const std::list<std::string>& text,int cur_y_text,int lines_text){
	int cur_x, cur_y;
	getyx(stdscr, cur_y, cur_x);
	const std::string& inp_line_no = take_inp("Enter Line Number: ",std::to_string(cur_y_text+1),48,57,9);
	if(inp_line_no.empty()){
		move(cur_y, cur_x);
		refresh();
		return;
	}
	int y_text = stoi(inp_line_no) - 1;
	if(y_text >= lines_text){
		if(lines_text != 0){y_text = lines_text - 1;}
		else{y_text = 0;}
	}
	render_full(text,y_text);
	move(0,0);
	refresh();
	return;
}

bool writefile(const std::string &filepath,const std::list<std::string>& text) {
	std::ofstream ofile(filepath,std::ios::trunc);
	if(!ofile){return false;}
	for(const auto& line : text){
		ofile << line << std::endl;
	}
	ofile.close();
	return true;
}

void clr_inp_fld(){
	move(INP_FLD,0);
	for(int i=0;i<COLS;i++){
		addch(' ');
	}
	refresh();
	return;
}

std::string take_inp(const std::string& prompt,std::string inp,int l_ascii_lim,int u_ascii_lim,int max_len){
	add_btn('C',"Cancel");
	print_inp_fld(prompt + inp);
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

void print_inp_fld(const std::string& msg){
	attron(A_REVERSE);
	mvaddstr(INP_FLD,0,msg.c_str());
	attroff(A_REVERSE);
	refresh();
	return;
}

void readfile(const std::string& filepath, std::list<std::string>& text){
	std::ifstream ifile(filepath);
	if(!ifile){ctn_btn("Failed to Open File: " + filepath);}
	std::string line;
	while(!ifile.eof()){
		std::getline(ifile,line);
		text.push_back(line);
	}
	ifile.close();
	return;
}

void ctn_btn(const std::string& prompt){
	add_btn('C',"Continue");
	print_inp_fld(prompt);
	refresh();
	int ch;
	while((ch = getch()) != 3){}
	remove_btn();
	clr_inp_fld();
	return;
}

void render_full(const std::list<std::string>& text,int y_text){
	clr_txt_area();
	auto it = std::next(text.begin(),y_text);
	int render_lines_no;
	if(text.size()-y_text < LINES_TEXT_AREA){
		render_lines_no = text.size()-y_text;
	}
	else{render_lines_no = LINES_TEXT_AREA;}
	for(int i=0;i<render_lines_no;i++,it++){
		if(it->length() <= COLS){
			mvaddstr(i,0,it->c_str());
		}
		else{
			mvaddstr(i,0,it->substr(0,COLS-1).c_str());
			addch('>' | A_REVERSE);
		}
	}
	refresh();
	return;
}

void clr_txt_area(){
	for(int i=0;i<=MAX_Y_TEXT_AREA;i++){
		move(i,0);
		for(int j=0;j<COLS;j++){
			addch(' ');
		}
	}
	refresh();
	return;
}