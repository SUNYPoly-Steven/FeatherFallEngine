#include "Renderable3D.h"
#include "../logging/Logging.h"
#include "../Auto.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/material.h>

namespace core { namespace graphics {

	Renderable3D::Renderable3D()
		: vbo(new core::buffers::VBO(nullptr, 0)), 
		ibo(new core::buffers::IBO(nullptr, 0)), 
		m_mlMatrix(1.0f)
	{
	}

	Renderable3D::Renderable3D(const void* vertData, const unsigned int* indexData, unsigned int vertexSize, unsigned int indexSize, bool staticDraw /* = true */)
		: vbo(new core::buffers::VBO(vertData, vertexSize, staticDraw)),
		ibo(new core::buffers::IBO(indexData, indexSize, staticDraw)),
		m_mlMatrix(1.0f) 
	{
		buffers::BufferLayout layout = buffers::BufferLayout();
		layout.push<float>(3); //position
		layout.push<float>(3); //normal
		layout.push<float>(4); //color

		vao.addBuffer(*vbo, layout);

	}

	Renderable3D::Renderable3D(const char* filepath)
		: m_mlMatrix(1.0f)
	{
		const aiScene* scene = aiImportFile(filepath, aiProcessPreset_TargetRealtime_MaxQuality);

		//Don't forget to release assimp's data
		Auto(aiReleaseImport(scene));

		if (!scene) {
			Log::printError("Could not load file!");
			Log::printError(aiGetErrorString());
		}

		//FF_ASSERT(scene->mNumMeshes == 1);

		aiMesh* mesh = scene->mMeshes[0];
		std::vector<float> verts;
		for (unsigned int vertIdx = 0; vertIdx < mesh->mNumVertices; vertIdx++) {
			aiVector3D pos = mesh->mVertices[vertIdx];
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
		for (unsigned int faceIdx = 0; faceIdx < mesh->mNumFaces; faceIdx++) {
			FF_ASSERT(mesh->mFaces[faceIdx].mNumIndices == 3u);

			indecies.push_back(mesh->mFaces[faceIdx].mIndices[0]);
			indecies.push_back(mesh->mFaces[faceIdx].mIndices[1]);
			indecies.push_back(mesh->mFaces[faceIdx].mIndices[2]);

		}

		vbo = new buffers::VBO((void*)verts.data(), verts.size() * sizeof(float));
		ibo = new buffers::IBO(indecies.data(), indecies.size());

		buffers::BufferLayout layout;
		layout.push<float>(3); // pos
		layout.push<float>(3); // normal
		layout.push<float>(4); // color

		vao.addBuffer(*vbo, layout);


	}

	Renderable3D::~Renderable3D()
	{
		delete vbo;
		delete ibo;
	}


} }