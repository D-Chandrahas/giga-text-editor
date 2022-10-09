#include "main_header.hpp"


void resize_handler(int sig){
	resize_flag = 1;
}

int main(int argc, char** argv){
	resize_flag = 0;
	signal(SIGWINCH, resize_handler);
	std::string filepath = "";
	if(argc > 1){
		filepath = argv[1];
	}
	while(true){
		if(!restart_program(filepath)){
			break;
		};
	}
	return 0;
}