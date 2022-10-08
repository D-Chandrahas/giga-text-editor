#include "main_header.hpp"



int main(int argc, char** argv){
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