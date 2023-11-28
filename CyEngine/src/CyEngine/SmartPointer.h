#pragma once

struct ReferenceCount
{
public:
	ReferenceCount()
	{
		m_SharedCount = 1;
		m_WeakCount = 0;
	}

	bool IsValid() const 
	{ 
		return m_SharedCount > 0; 
	}	
	
	bool ShouldInvalidate() const
	{
		return m_SharedCount == 0 && m_WeakCount == 0;
	}

	void IncrementShared() 
	{ 
		if (m_SharedCount == 0)
			return;
		m_SharedCount++; 
	}
	void DecrementShared() 
	{
		if (m_SharedCount == 0)
			return;
		m_SharedCount--; 
	}
	void IncrementWeak() 
	{ 
		m_WeakCount++; 
	}
	void DecrementWeak() 
	{
		m_WeakCount--; 
	}

private:
	size_t m_SharedCount;
	size_t m_WeakCount;
};

template<typename T>
class SharedPtr;

template<typename T>
class WeakPtr;

template<typename T>
class SharedPtr
{
	friend class WeakPtr<T>;

public:
	SharedPtr()
	{
		ptr = nullptr;
		rc = nullptr;
	}
	SharedPtr(T* p)
	{
		ptr = p;
		rc = new ReferenceCount();
	}
	SharedPtr(T* p, ReferenceCount* r)
	{
		ptr = p;
		rc = r;
		rc->IncrementShared();
	}
	SharedPtr(const SharedPtr& other)
	{
		ptr = other.ptr;
		rc = other.rc;
		rc->IncrementShared();
	}
	~SharedPtr()
	{
		rc->DecrementShared();
		if (!rc->IsValid())
		{
			ptr->~T();
			ptr = nullptr;

			if (rc->ShouldInvalidate())
			{
				delete[] rc;
				rc = nullptr;
			}
		}
	}
	
	operator T*() const { return ptr; }
	T* operator->() const { return ptr; }

	T* Get() const
	{
		return ptr;
	}

	bool IsValid() const 
	{ 
		return rc->IsValid(); 
	}

private:
	T* ptr;
	ReferenceCount* rc;
};

template<typename T>
class WeakPtr
{
	friend class SharedPtr<T>;

public:
	WeakPtr()
	{
		ptr = nullptr;
		rc = nullptr;
	}
	WeakPtr(const SharedPtr<T>& sp)
	{
		ptr = sp.ptr;
		rc = sp.rc;
		rc->IncrementWeak();
	}	
	WeakPtr(const WeakPtr& wp)
	{
		ptr = wp.ptr;
		rc = wp.rc;
		rc->IncrementWeak();
	}
	~WeakPtr()
	{
		rc->DecrementWeak();
		if (rc->ShouldInvalidate())
		{
			delete[] rc;
			rc = nullptr;
		}
	}

	operator T*() const { return ptr; }
	T* operator->() const { return ptr; }

	T* Get() const
	{
		return ptr;
	}

	bool IsValid() const
	{
		return rc->IsValid();
	}

private:
	T* ptr;
	ReferenceCount* rc;
};
