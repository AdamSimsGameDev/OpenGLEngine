#pragma once

template<typename T>
class Queue;

template<typename T>
class QueueEntry
{
	friend Queue;

public:
	QueueEntry(const T& Data)
	{
		m_Data = (T*)::operator new(sizeof(T));
		*m_Data = Data;
	}	
	QueueEntry(const QueueEntry& Other)
	{
		if (std::is_pointer<T>())
		{
			m_Data = Other.m_Data;
		}
		else
		{
			m_Data = T(*Other.m_Data);
		}
	}
	QueueEntry(QueueEntry&& arr) noexcept
	{
		if (std::is_pointer<T>())
		{
			m_Data = Other.m_Data;
		}
		else
		{
			m_Data = T(*Other.m_Data);
		}
	}
	~QueueEntry()
	{
		if (m_Data)
		{
			m_Data.~T();
		}
	}

	T& Get() { return *m_Data; }
	const T& Get() const { return *m_Data; }

	QueueEntry<T>* Next() { return m_Next; }
	const QueueEntry<T>* Next() const { return m_Next; }

private:
	T* m_Data = nullptr;
	QueueEntry<T>* m_Next = nullptr;
};

template<typename T>
class Queue
{
public:
	Queue()
	{

	}

	Queue(const Queue& Other)
	{
		m_Size = Other.m_Size;

		if (std::is_pointer<T>())
		{
			m_Head = Other.m_Head;
			m_Tail = Other.m_Tail;
		}
		else
		{
			auto Current = Other.m_Head;
			while (Current)
			{
				Enqueue(T(Current));
				Current = Current.Next();
			}
		}
	}

	~Queue()
	{
		T D;
		while (Dequeue(D))
		{
			if (!std::is_pointer<T>())
			{
				D.~T();
			}
		}

		m_Size = 0;

		m_Head = nullptr;
		m_Tail = nullptr;
	}
	
	void Enqueue(const T& Data)
	{
		QueueEntry<T>* NewEntry = new QueueEntry<T>(Data);
		if (m_Head == nullptr)
		{
			m_Head = NewEntry;
			m_Tail = NewEntry;
			return;
		}

		m_Tail->m_Next = NewEntry;
		m_Tail = NewEntry;

		m_Size++;
	}

	bool Dequeue(T& OutValue)
	{
		if (m_Head == nullptr)
		{
			return false;
		}

		OutValue = m_Head->Get();
		m_Head = m_Head->Next();
		m_Size--;
		return true;
	}

	uint32_t Num() const { return m_Size; }

private:
	QueueEntry<T>* m_Head = nullptr;
	QueueEntry<T>* m_Tail = nullptr;

	uint32_t m_Size = 0;
};