#include "ThreadManager.h"

namespace core { namespace thread {

	//private constructor
	ThreadManager::ThreadManager() {

	}

	//get singleton instance
	ThreadManager::Get() {
		static ThreadManager instance;
		return instance;
	}

} }