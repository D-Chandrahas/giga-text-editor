#ifndef MY_HEADER_HPP
#define MY_HEADER_HPP


#include <ncurses.h>
#include <string>
#include <fstream>
#include <list>


#define INP_FLD (LINES-2)
#define TEXT_Y_MAX (INP_FLD-1)
#define OPN_FLD_1 (INP_FLD+1)



void init();

void print_menu();

void add_btn(char ch, const std::string& btn_name);

void remove_btn();

void write_out(const std::string& filepath,const std::string& text);

void goto_line(int cur_line,int lines_text);

bool writefile(const std::string &filepath,const std::string &contents);

void clr_inp_fld();

std::string take_inp(const std::string& prompt, std::string inp,int l_ascii_lim, int u_ascii_lim, int max_len);

void print_inp_fld(const std::string& msg,int col = 0);

void readfile(const std::string& filepath, std::list<std::string>& text);


#endif