#pragma once
#include "CyEngine/Core.h"
#include "CyEngine/Threads/Thread.h"

namespace Cy
{
	class ThreadManager
	{
	public:
		template <typename ThreadType=Thread, class... _Args>
		void CreateThread(String name)
		{
			ThreadType* thread = new ThreadType(name);
			m_Threads.Add(thread);
			thread->StartThread();
		}

		static void StopAllThreads();

		static ThreadManager& Get();

	private:
		void Initialise();

	private:
		static SharedPtr<ThreadManager> s_ThreadManager;

		Array<Thread*> m_Threads;
	};
}
