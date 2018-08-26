#pragma once

namespace core { namespace thread {

	//The amount of threads to give the thread manager
	#define MAX_THREADS 100

	class ThreadManager {
	public:

	private:

		//Kept private to make singleton
		ThreadManager();

		//array of threads that could be used.
		//TODO: make a "ThreadPool" class to manager threads in a better way
		std::thread threads[MAX_THREADS];

	public:

		//The function to get the ThreadManager instance
		static ThreadManager* Get();

		//try_dispatch_thread() could be a way to go about using the threads

	};

} }