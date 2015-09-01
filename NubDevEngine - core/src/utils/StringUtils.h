#pragma once

#include <string>
#include <sstream>
#include <vector>

namespace engine {

	static std::vector<std::string> split_string(const std::string &s, char delimeter) {
		std::vector<std::string> elems;
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delimeter)) {
			elems.push_back(item);
		}
		return elems;
	}

	static void class_name(std::string &path, bool upperCase = true){
		path = split_string(path, ':').back();
		path = split_string(path, ' ').front();
		if (upperCase){
			for (std::string::iterator p = path.begin(); path.end() != p; ++p)
				*p = toupper(*p);
		}
	}

}