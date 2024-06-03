#include "cypch.h"
#include "Thread.h"

namespace Cy
{
    void Thread::StartThread()
    {
        m_Thread = std::thread(&Thread::RunThread, this);
        m_IsRunning = true;
    }

    void Thread::CancelThread()
    {
        m_IsRunning = false;
    }

    void Thread::RunThread()
    {
        SetThreadDescription(GetCurrentThread(), m_Name.ToWString().c_str());

        int c = 0;
        while (m_IsRunning)
        {
            if (c % 10000 == 1)
            {
                CY_LOG("Ran on thread");
            }
            c++;
        }
    }
}
