#include "Mesh.h"
#include "../logging/Logging.h"
#include "../Auto.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/material.h>

namespace core { namespace mesh {

	Mesh::Mesh(const char* filepath)
	{
		//FF_ASSERT(ReadFile(filepath));
	} 

	Mesh::~Mesh() {}

	core::graphics::Renderable3D* Mesh::ReadFile(const char* filepath)
	{
		
		const aiScene* scene = aiImportFile(filepath, aiProcessPreset_TargetRealtime_MaxQuality);
		
		//Don't forget to release assimp's data
		Auto(aiReleaseImport(scene));

		if (!scene) {
			Log::printError("Could not load file!");
			Log::printError(aiGetErrorString());
			// load fail
			return nullptr;
		}

		//FF_ASSERT(scene->mNumMeshes == 1);

		aiMesh* mesh = scene->mMeshes[0];
		std::vector<float> verts;
		for (int vertIdx = 0; vertIdx < mesh->mNumVertices; vertIdx++) {
			aiVector3D pos  = mesh->mVertices[vertIdx];
			aiVector3D norm = mesh->mNormals[vertIdx];

			// add position data to vertex
			verts.push_back(pos.x);  // pX
			verts.push_back(pos.y);  // pY
			verts.push_back(pos.z);  // pZ

			verts.push_back(norm.x); // nX
			verts.push_back(norm.y); // nY
			verts.push_back(norm.z); // nZ

			// add color data to vertex. (just make it white)
			verts.push_back(1.0f);   // cR
			verts.push_back(1.0f);   // cG
			verts.push_back(1.0f);   // cB
			verts.push_back(1.0f);   // cA

		}

		std::vector<unsigned int> indecies;
		indecies.reserve(mesh->mNumFaces * 3);
		for (int faceIdx = 0; faceIdx < mesh->mNumFaces; faceIdx++) {
			FF_ASSERT(mesh->mFaces[faceIdx].mNumIndices == 3u);

			indecies.push_back(mesh->mFaces[faceIdx].mIndices[0]);
			indecies.push_back(mesh->mFaces[faceIdx].mIndices[1]);
			indecies.push_back(mesh->mFaces[faceIdx].mIndices[2]);

		}

		// return success
		return new core::graphics::Renderable3D(
			(void*)verts.data(), 
			indecies.data(), 
			verts.size() * sizeof(float), 
			indecies.size()
		);
		
	}


} }