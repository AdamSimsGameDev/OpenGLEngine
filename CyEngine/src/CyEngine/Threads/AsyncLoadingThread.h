#pragma once
#include "CyEngine/Core.h"
#include "CyEngine/Threads/Thread.h"

namespace Cy
{
	class AsyncLoadingThread : public Thread
	{
	public:
		AsyncLoadingThread(const String& name)
			: Thread(name)
		{
		}

	protected:
		virtual void ThreadTick() override;
	};
}
