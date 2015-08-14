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
		std::deque<std::string> lines;
		FILE *file = fopen(filepath, "rt");
		
		char lineHeader[128];
		float x, y, z;
		bool hasUvs = false, hasNormals = false;

		std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
		std::vector< maths::vec3 > temp_vertices;
		std::vector< maths::vec2 > temp_uvs;
		std::vector< maths::vec3 > temp_normals;

		while (fscanf(file, "%s", lineHeader) != EOF){
			if (strcmp(lineHeader, "v") == 0){
				fscanf(file, "%f %f %f\n", &x, &y, &z);
				temp_vertices.push_back(maths::vec3(x, y, z));
			}
			else if (strcmp(lineHeader, "vt") == 0){
				hasUvs = true;
				fscanf(file, "%f %f\n", &x, &y);
				temp_uvs.push_back(maths::vec2(x, y));
			}
			else if (strcmp(lineHeader, "vn") == 0){
				hasNormals = true;
				fscanf(file, "%f %f %f\n", &x, &y, &z);
				temp_normals.push_back(maths::vec3(x, y, z));
			}
			else if (strcmp(lineHeader, "f") == 0){
				unsigned int vIdx[3], vtIdx[3], vnIdx[3];
				if (hasUvs && hasNormals){
					fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
						&vIdx[0], &vtIdx[0], &vnIdx[0], &vIdx[1], &vtIdx[1], &vnIdx[1], &vIdx[2], &vtIdx[2], &vnIdx[2]);
				}
				else if (hasUvs && !hasNormals){
					fscanf(file, "%d/%d %d/%d %d/%d\n",	&vIdx[0], &vtIdx[0], &vIdx[1], &vtIdx[1], &vIdx[2], &vtIdx[2]);
				}
				else if (!hasUvs && hasNormals){
					fscanf(file, "%d//%d %d//%d %d//%d\n", &vIdx[0], &vnIdx[0], &vIdx[1], &vnIdx[1], &vIdx[2], &vnIdx[2]);
				}
				else if (!hasUvs && !hasNormals){
					fscanf(file, "%d %d %d\n", &vIdx[0], &vIdx[1], &vIdx[2]);
				}

				for (unsigned int i = 0; i < 3; i++){						//3 vertices each face (Triangles)
					vertexIndices.push_back(vIdx[i] - 1);
					if (hasUvs)	uvIndices.push_back(vtIdx[i] - 1);
					if (hasNormals)	normalIndices.push_back(vnIdx[i] - 1);
				}
			}
			else{
				fscanf(file, "%*[^\n]", NULL);
			}
		}
		fclose(file);

		std::vector<maths::vec3> out_vertex(temp_vertices.size());
		std::vector<maths::vec2> out_uvs(temp_vertices.size());
		std::vector<maths::vec3> out_normals(temp_vertices.size());

		for (unsigned int i = 0; i < vertexIndices.size(); i++){
			unsigned int vertexPointer = vertexIndices[i];
			out_vertex[vertexPointer] = temp_vertices[vertexIndices[i]];
			if (hasUvs) out_uvs[vertexPointer] = temp_uvs[uvIndices[i]];
			if (hasNormals) out_normals[vertexPointer] = temp_normals[normalIndices[i]];
		}
	}
}