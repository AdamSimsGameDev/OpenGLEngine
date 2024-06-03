#include "cypch.h"
#include "ThreadManager.h"

namespace Cy
{
	SharedPtr<ThreadManager> ThreadManager::s_ThreadManager = nullptr;

	ThreadManager& ThreadManager::Get()
	{
		if (s_ThreadManager == nullptr)
		{
			s_ThreadManager = new ThreadManager();
			s_ThreadManager->Initialise();
		}
		return *s_ThreadManager;
	}

	void ThreadManager::StopAllThreads()
	{
		for (auto& thread : Get().m_Threads)
		{
			thread->CancelThread();
		}
	}

	void ThreadManager::Initialise()
	{

	}
}
