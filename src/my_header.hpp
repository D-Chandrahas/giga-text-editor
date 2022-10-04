#ifndef MY_HEADER_HPP
#define MY_HEADER_HPP


#include <ncurses.h>
#include <string>
#include <fstream>
#include <list>


#define OPN_FLD_SIZE 1
#define INP_FLD (LINES - OPN_FLD_SIZE - 1)
#define LINES_TEXT_AREA (LINES - OPN_FLD_SIZE - 1)
#define MAX_Y_TEXT_AREA (LINES_TEXT_AREA - 1)
#define OPN_FLD_1 (INP_FLD + 1)



void initialize_program();

void print_menu();

void add_btn(char ch, const std::string& btn_name);

void add_enter_btn(const std::string& btn_name);

void remove_btn();

void write_out(const std::string& filepath,const std::list<std::string>& text);

void goto_line(const std::list<std::string>& text);

bool writefile(const std::string &filepath,const std::list<std::string>& text);

void clr_inp_fld();

std::string take_inp(const std::string& prompt, std::string inp,int l_ascii_lim, int u_ascii_lim, int max_len);

void print_inp_fld(const std::string& msg);

void readfile(const std::string& filepath, std::list<std::string>& text);

void ctn_btn(const std::string& prompt);

void render_full(const std::list<std::string>& text,int y_text,int x_text);

void clr_txt_area();

bool restart_program(std::string& filepath);

bool open_file(std::string& filepath);

int scr_x_state(int x_text);

void key_up(const std::list<std::string>& text);

void key_down(const std::list<std::string>& text);

//void key_left(const std::list<std::string>& text);

//void key_right(const std::list<std::string>& text);



#endif