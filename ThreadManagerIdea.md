# Thread Manager Idea
- Start with core::thread::ThreadManager class. Make this a singleton (see introspection Test for impl.)
- core::thread::ThreadManager::Get() gets a static instance of the class. 
- class will have an array of threads to dispatch when asked to with ThreadManager.try_thread_dispatch() (or something to that effect)
- the thread manager will essentialy wrap the use of std::thread to make implementing a job system easier.
- once figuring out how std::mutex works you could wrap that here as well. Or make a different wrapper if you feel the need to.
- if the Manager does not have a thread to dispatch at the moment of a call, should it add it to a job queue? woudnt that just make it a JobManager at that point if it did?

## Example Class Statement

    namespace core {
		namespace thread {
			class ThreadManager {
			public: 
				
			private:
				std::thread threads[MAX_THREADS];

				ThreadManager(); // Make the constructer private as to not be able to use it

			public:
				try_dispatch_thread(/*some job functioin pointer?*/);

			}
		}
	}