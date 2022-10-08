#include "main_header.hpp"


static const char CANCEL_CODE[2] = {char(3),'\0'};
static int CUR_Y_TEXT = 0;
static int CUR_X_TEXT = 0;



void initialize_program(){
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
	mvaddstr(OPN_FLD_1,0,"CTRL + W");
	mvaddstr(OPN_FLD_1,25,"CTRL + X");
	mvaddstr(OPN_FLD_1,50,"CTRL + G");
	mvaddstr(OPN_FLD_1,75,"CTRL + O");
	attroff(A_REVERSE);
	mvaddstr(OPN_FLD_1,8," Write Out");
	mvaddstr(OPN_FLD_1,33," Exit");
	mvaddstr(OPN_FLD_1,58," Go to Line");
	mvaddstr(OPN_FLD_1,83," Open File");
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

void add_enter_btn(const std::string& btn_name){
	attron(A_REVERSE);
	mvaddstr(OPN_FLD_1,100,"ENTER");
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
	std::string new_filepath = take_inp("Enter Filename: ",filepath,32,126,100);
	if((new_filepath != CANCEL_CODE) and (new_filepath != "")){
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

void goto_line(const std::list<std::string>& text){
	int cur_x, cur_y, lines_text = text.size();
	getyx(stdscr, cur_y, cur_x);
	std::string inp_line_no = take_inp("Enter Line Number: ",std::to_string(CUR_Y_TEXT+1),48,57,9);
	if((inp_line_no == CANCEL_CODE) or (inp_line_no == "")){
		move(cur_y, cur_x);
		refresh();
		return;
	}
	int y_text = stoi(inp_line_no) - 1;
	if(y_text >= lines_text){y_text = lines_text - 1;}
	CUR_Y_TEXT = y_text;
	CUR_X_TEXT = 0;
	if(lines_text - y_text >= LINES_TEXT_AREA){
		render_full(text,y_text,0);
		move(0,0);
	}
	else{
		int y_text_render = lines_text - LINES_TEXT_AREA;
		if(y_text_render < 0){y_text_render = 0;}
		render_full(text,y_text_render,0);
		move(y_text-y_text_render,0);
	}
	refresh();
	return;
}

bool writefile(const std::string &filepath,const std::list<std::string>& text) {
	std::ofstream ofile(filepath,std::ios::trunc);
	if(!ofile){return false;}
	for(const auto& line : text){
		ofile << line;
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
			inp += char(3);
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
	if(!ifile){
		ctn_btn("Failed to Open File: " + filepath);
		ifile.close();
		return;
	}
	std::string line;
	while(!ifile.eof()){
		std::getline(ifile,line);
		line.push_back('\n');
		text.push_back(line);
	}
	ifile.close();
	return;
}

//if button is ctrl + c ,does not work in readfile(), but works in writefile()
void ctn_btn(const std::string& prompt){
	add_enter_btn("Continue");
	print_inp_fld(prompt);
	refresh();
	int ch;
	while((ch = getch()) != '\n'){}
	remove_btn();
	clr_inp_fld();
	return;
}

void render_full(const std::list<std::string>& text,int y_text,int x_text){
	clr_txt_area();
	auto it = std::next(text.begin(),y_text);
	int render_lines_no;
	if(text.size()-y_text < LINES_TEXT_AREA){
		render_lines_no = text.size()-y_text;
	}
	else{render_lines_no = LINES_TEXT_AREA;}
	if(x_text == 0){
		for(int i=0;i<render_lines_no;i++,it++){
			mvaddstr(i,0,(it->substr(x_text,COLS-1)).c_str());
			if((it->length()) > COLS-1 + x_text){
				mvaddch(i,COLS-1,'>' | A_REVERSE);
			}
		}
	}
	else{
		for(int i=0;i<render_lines_no;i++,it++){
			if(it->length() > x_text){
				mvaddch(i,0,'<' | A_REVERSE);
				mvaddstr(i,1,(it->substr(x_text,COLS-2)).c_str());
			}
			if((it->length()) > COLS-2 + x_text){
				mvaddch(i,COLS-1,'>' | A_REVERSE);
			}
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

bool restart_program(std::string& filepath){
	std::list<std::string> text;
	if(filepath != ""){
		readfile(filepath,text);
	}
	else{text.push_back("\n");}
	int ch;
	int cur_x = 0;
	int cur_y = 0;
	CUR_X_TEXT = 0;
	CUR_Y_TEXT = 0;
	initialize_program();
	render_full(text,0,0);
	move(0,0);

	while(TRUE){
		ch = getch();
		if(ch == CTRL('X')){endwin();return false;}
		if(ch == CTRL('W')){write_out(filepath,text);continue;}
		if(ch == CTRL('G')){goto_line(text);continue;}
		if(ch == CTRL('O')){
			if(open_file(filepath)){endwin();return true;}
			else{continue;}
		}
		if(ch == KEY_UP){key_up(text);continue;}
		if(ch == KEY_DOWN){key_down(text);continue;}
		if(ch == KEY_LEFT){key_left(text);continue;}
		if(ch == KEY_RIGHT){key_right(text);continue;}
		if(ch == KEY_ENTER or ch == '\n'){key_enter(text);continue;}
		if(ch >= 32 and ch <= 126){key_char(text,ch);continue;}
		if(ch == KEY_BACKSPACE or ch == '\b'){key_backspace(text);continue;}
		if(ch == KEY_DC or ch == 127){key_delchar(text);continue;}
		refresh();
	}
}

bool open_file(std::string& filepath){
	std::string new_filepath = take_inp("Enter Filepath: ","",32,126,100);
	if(new_filepath == CANCEL_CODE){return false;}
	else{filepath = new_filepath;return true;}
}

int scr_x_state(int x_text){
	if(x_text <= COLS - 2){return 0;}
	else{return (x_text)-(x_text-(COLS-1))%(COLS-2);}
}

inline int scr_y_state(int y_text,int y){return ((y_text) - (y));}

int get_cur_x(int x_text){
	if(x_text <= COLS - 2){return x_text;}
	else{return x_text - scr_x_state(x_text) + 1;}
}

void key_up(const std::list<std::string>& text){
	if(CUR_Y_TEXT == 0){return;}
	int cur_x,cur_y;
	getyx(stdscr,cur_y,cur_x);
	CUR_Y_TEXT--;
	auto it = std::next(text.begin(),CUR_Y_TEXT);
	if(CUR_X_TEXT > it->length()-1){
		CUR_X_TEXT = it->length()-1;
	}
	if(cur_y == 0){
		render_full(text,CUR_Y_TEXT,scr_x_state(CUR_X_TEXT));
		move(0,get_cur_x(CUR_X_TEXT));
	}
	else{
		render_full(text,scr_y_state(CUR_Y_TEXT,cur_y-1),scr_x_state(CUR_X_TEXT));
		move(cur_y-1,get_cur_x(CUR_X_TEXT));
	}
	refresh();
	return;
}

void key_down(const std::list<std::string>& text){
	if(CUR_Y_TEXT == text.size()-1){return;}
	int cur_x,cur_y;
	getyx(stdscr,cur_y,cur_x);
	CUR_Y_TEXT++;
	auto it = std::next(text.begin(),CUR_Y_TEXT);
	if(CUR_X_TEXT > it->length()-1){
		CUR_X_TEXT = it->length()-1;
	}
	if(cur_y == MAX_Y_TEXT_AREA){
		render_full(text,CUR_Y_TEXT-(LINES_TEXT_AREA-1),scr_x_state(CUR_X_TEXT));
		move(MAX_Y_TEXT_AREA,get_cur_x(CUR_X_TEXT));
	}
	else{
		render_full(text,scr_y_state(CUR_Y_TEXT,cur_y+1),scr_x_state(CUR_X_TEXT));
		move(cur_y+1,get_cur_x(CUR_X_TEXT));
	}
	refresh();
	return;
}

void key_left(const std::list<std::string>& text){
	if(CUR_X_TEXT <= 0 and CUR_Y_TEXT <= 0){return;}
	if(CUR_X_TEXT <= 0 and CUR_Y_TEXT > 0){
		auto it = std::next(text.begin(),CUR_Y_TEXT-1);
		CUR_X_TEXT = it->length()-1;
		key_up(text);
		return;
	}
	int cur_x,cur_y;
	getyx(stdscr,cur_y,cur_x);
	CUR_X_TEXT--;
	if(CUR_X_TEXT+1 > COLS-2  and cur_x == 1){
		render_full(text,scr_y_state(CUR_Y_TEXT,cur_y),scr_x_state(CUR_X_TEXT));
		move(cur_y,get_cur_x(CUR_X_TEXT));
	}
	else{
		move(cur_y,cur_x-1);
	}
	refresh();
	return;
}

void key_right(const std::list<std::string>& text){
	auto it = std::next(text.begin(),CUR_Y_TEXT);
	if((CUR_X_TEXT + 1 >= (it->length())) and (CUR_Y_TEXT + 1 >= (text.size()))){return;}
	if((CUR_X_TEXT + 1 >= (it->length())) and (CUR_Y_TEXT + 1 < (text.size()))){
		CUR_X_TEXT = 0;
		key_down(text);
		return;
	}
	int cur_x,cur_y;
	getyx(stdscr,cur_y,cur_x);
	CUR_X_TEXT++;
	if(cur_x == COLS-2){
		render_full(text,scr_y_state(CUR_Y_TEXT,cur_y),scr_x_state(CUR_X_TEXT));
		move(cur_y,get_cur_x(CUR_X_TEXT));
	}
	else{
		move(cur_y,cur_x+1);
	}
	refresh();
	return;
}

void key_enter(std::list<std::string>& text){
	int cur_x,cur_y;
	getyx(stdscr,cur_y,cur_x);
	auto it = std::next(text.begin(),CUR_Y_TEXT);
	std::string new_line = it->substr(CUR_X_TEXT);
	it->erase(CUR_X_TEXT);
	it->push_back('\n');
	text.insert(++it,new_line);
	CUR_X_TEXT = 0;
	key_down(text);
	refresh();
	return;
}

void key_char(std::list<std::string>& text,int ch){
	int cur_x,cur_y;
	getyx(stdscr,cur_y,cur_x);
	auto it = std::next(text.begin(),CUR_Y_TEXT);
	it->insert(CUR_X_TEXT,1,ch);
	CUR_X_TEXT++;
	render_full(text,scr_y_state(CUR_Y_TEXT,cur_y),scr_x_state(CUR_X_TEXT));
	move(cur_y,get_cur_x(CUR_X_TEXT));
	refresh();
	return;
}

void key_backspace(std::list<std::string>& text){
	if(CUR_X_TEXT <= 0 and CUR_Y_TEXT <= 0){return;}
	if(CUR_X_TEXT <= 0 and CUR_Y_TEXT > 0){
		auto curr = std::next(text.begin(),CUR_Y_TEXT);
		auto prev = std::prev(curr);
		CUR_X_TEXT = prev->length() - 1;
		prev->pop_back();
		prev->append(*curr);
		text.erase(curr);
		key_up(text);
		return;
	}
	int cur_x,cur_y;
	getyx(stdscr,cur_y,cur_x);
	auto it = std::next(text.begin(),CUR_Y_TEXT);
	it->erase(CUR_X_TEXT-1,1);
	CUR_X_TEXT--;
	render_full(text,scr_y_state(CUR_Y_TEXT,cur_y),scr_x_state(CUR_X_TEXT));
	move(cur_y,get_cur_x(CUR_X_TEXT));
	refresh();
	return;
}

void key_delchar(std::list<std::string>& text){
	int cur_x,cur_y;
	getyx(stdscr,cur_y,cur_x);
	auto it = std::next(text.begin(),CUR_Y_TEXT);
	if(CUR_X_TEXT >= it->length()-1 and CUR_Y_TEXT >= text.size()-1){return;}
	if(CUR_X_TEXT >= it->length()-1 and CUR_Y_TEXT < text.size()-1){
		auto curr = std::next(text.begin(),CUR_Y_TEXT);
		auto next = std::next(curr);
		curr->pop_back();
		curr->append(*next);
		text.erase(next);
		render_full(text,scr_y_state(CUR_Y_TEXT,cur_y),scr_x_state(CUR_X_TEXT));
		move(cur_y,get_cur_x(CUR_X_TEXT));
		refresh();
		return;
	}
	it->erase(CUR_X_TEXT,1);
	render_full(text,scr_y_state(CUR_Y_TEXT,cur_y),scr_x_state(CUR_X_TEXT));
	move(cur_y,get_cur_x(CUR_X_TEXT));
	refresh();
	return;
}

