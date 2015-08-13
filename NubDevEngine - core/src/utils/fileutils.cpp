#include "fileutils.h"


namespace engine{

	std::string read_file(const char* filepath){
		FILE *file = fopen(filepath, "rt"); //open file has "r"ead-only "t"ext
		fseek(file, 0, SEEK_END);
		unsigned long length = ftell(file);

		char *data = new char[length + 1];
		memset(data, 0, length + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);
		fclose(file);

		std::string result(data);
		delete[] data;
		return result;
	}

	std::deque<std::string> read_file_lines(const char* filepath){
		std::deque<std::string> file;
		std::ifstream input(filepath);
		std::string line;
		while (getline(input, line)){
			file.push_back(line);
		}
		return file;
	}

	std::deque<std::string> read_file_lines1(const char* filepath){
		std::deque<std::string> lines;
		FILE *file = fopen(filepath, "rt");
		char line[128];
		while (fscanf(file, "%2000[^\n]\n", line) != EOF){
			lines.push_back(line);
		}
		fclose(file);
		return lines;
	}

	void read_obj(const char* filepath){

	}

}