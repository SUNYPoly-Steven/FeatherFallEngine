#include "Mesh.h"
#include "../logging/Logging.h"
#include <fstream>

namespace core { namespace mesh {

	Mesh::Mesh(const char* filepath)
	{
		ReadFile(filepath);
	} 

	Mesh::~Mesh() {}

	void Mesh::ReadFile(const char* filepath)
	{
		/*
			ffm file format spec:
				-line 1 is number of verts

				-then each line after will have a vertex on it
				all data for the single vertex will be on the same 
				line for that vertex

				-after verts are done the very next line is the 
				index count

				-then the index array will begin on the next line
				and continue until the file is over

				-each line will contain 3 unsigned ints that when
				used as indexes into the vert array will make a 
				triangle in the mesh
		*/
		std::fstream file(filepath);
		if (!file.is_open()) {
			Log::printWarning("Model could not be loaded!");
		}

		
		
	}


} }