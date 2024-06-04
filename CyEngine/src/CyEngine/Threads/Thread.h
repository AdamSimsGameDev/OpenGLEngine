#pragma once
#include "CyEngine/Core.h"

#include <thread>

namespace Cy
{
	class Thread
	{
		friend class ThreadManager;

	public:
		Thread(const String& name)
			: m_Name(name)
			, m_IsRunning(false)
		{
		}
		~Thread()
		{
			m_IsRunning = false;
		}

		virtual void StartThread();
		virtual void CancelThread();

		const String& GetName() const { return m_Name; }

		std::thread& GetThread() { return m_Thread; }
		const std::thread& GetThread() const { return m_Thread; }

	protected:
		void RunThread();
		virtual void ThreadTick();

	private:
		String m_Name;
		std::thread m_Thread;
		std::atomic<bool> m_IsRunning;
	};
}
