#include "my_header.hpp"


extern const char CANCEL_CODE[2] = {char(3),'\0'};



//https://docs.microsoft.com/en-us/cpp/cpp/extern-cpp?view=msvc-170
//(ref:restart_program())make them extern variables and replace wherever they can be replaced
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