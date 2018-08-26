#pragma once
#include <vector>

namespace core { namespace profiler { 

	class Profiler {
	private:

		std::vector<int> subframes;

	public:

		Profiler();
		~Profiler();

		BeginFrame();
		EndFrame();

		BeginSubFrame();
		EndSubFrame();

		ProfilerRender();

	private:



	};

}}