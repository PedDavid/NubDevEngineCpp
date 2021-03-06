#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <vector>
#include "timer.h"
#include "../maths/maths.h"

namespace engine{

	std::string read_file(const char* filepath);

	std::deque<std::string> read_file_lines(const char* filepath);
	std::deque<std::string> read_file_lines1(const char* filepath);

	void read_obj(const char* filepath, std::vector<maths::vec3> &temp_vertices, std::vector<unsigned int> &vertexIndices);
}