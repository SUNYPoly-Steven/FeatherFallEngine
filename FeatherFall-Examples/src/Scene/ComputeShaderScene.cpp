#include <GL/glew.h>
#include "debuging.h"
#include "ComputeShaderScene.h"
#include "ImGui/imgui.h"

namespace Application { namespace Scene {

	ComputeShaderScene::ComputeShaderScene() 
		: compute(new core::graphics::Shader("res/shaders/c_HelloCompute.shader")),
		gfx(new core::graphics::Shader("res/shaders/g_HelloCompute.shader"))
	{

		GLuint vertArray;
		glGenVertexArrays(1, &vertArray);
		glBindVertexArray(vertArray);

		GLuint posBuf;
		glGenBuffers(1, &posBuf);
		glBindBuffer(GL_ARRAY_BUFFER, posBuf);
		float data[] = {
			-1.0f, -1.0f,
			-1.0f, 1.0f,
			1.0f, -1.0f,
			1.0f, 1.0f
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, data, GL_STREAM_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);




		GLCall(glGenTextures(1, &tex));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 512, 512, 0, GL_RGBA, GL_FLOAT, NULL));

		// Because we're also using this tex as an image (in order to write to it),
		// we bind it to an image unit as well
		glBindImageTexture(0, tex, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

		gfx->bind();
		gfx->setUniform1i("srcTex", 0);

		compute->bind();
		compute->setUniform1i("destTex", 0);//set the image2D to use texture slot 0
	}

	ComputeShaderScene::~ComputeShaderScene()
	{
		delete compute;
		delete gfx;
	}

	void ComputeShaderScene::OnUpdate(float deltaTime)
	{
		time = time + deltaTime;
		lastDelta = deltaTime;
		compute->bind();
		compute->setUniform1f("roll", time);
		GLCall(glDispatchCompute(512/16, 512/16, 1)); //512^2 threads in 16^2 blocks
	}

	void ComputeShaderScene::OnRender()
	{
		gfx->bind();
		GLCall(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
	}
	
	void ComputeShaderScene::OnImGuiRender()
	{
		ImGui::Text("This is animation is\nbeing calculated on the GPU\nusing compute shaders!!");
		ImGui::Text("Time: %.3f\nDeltaTime: %.3f", time, lastDelta);
	}

} }