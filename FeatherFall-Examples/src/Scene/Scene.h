#pragma once

namespace Application { namespace Scene {
		
	class Scene {
	private:

	public:

		Scene();
		virtual ~Scene();

		virtual void OnUpdate(float deltaTime);
		virtual void OnRender();
		virtual void OnImGuiRender();

	private:

	};

} }