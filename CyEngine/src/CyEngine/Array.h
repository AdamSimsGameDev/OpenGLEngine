#pragma once

template<typename Arr>
class ArrayItr
{
public:
	using ValueType = typename Arr::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;

public:
	ArrayItr(PointerType ptr)
		: m_Ptr(ptr) {}

	ArrayItr& operator++()
	{
		m_Ptr++;
		return *this;
	}
	ArrayItr& operator++(int)
	{
		ArrayItr itr = *this;
		++(*this);
		return itr;
	}

	ArrayItr& operator--()
	{
		m_Ptr++;
		return *this;
	}
	ArrayItr& operator--(int)
	{
		ArrayItr itr = *this;
		--(*this);
		return itr;
	}

	ReferenceType operator[](int index)
	{
		return *(m_Ptr[index]);
	}

	PointerType operator->()
	{
		return m_Ptr;
	}	
	ReferenceType operator*()
	{
		return *m_Ptr;
	}

	bool operator==(const ArrayItr& other) const { return m_Ptr == other.m_Ptr; }
	bool operator!=(const ArrayItr& other) const { return !(*this == other); }

private:
	PointerType m_Ptr;
};

template<typename Arr>
class ArrayItrConst
{
public:
	using ValueType = typename Arr::ValueType;
	using PointerType = const ValueType*;
	using ReferenceType = const ValueType&;

public:
	ArrayItrConst(PointerType ptr)
		: m_Ptr(ptr) {}

	ArrayItrConst& operator++()
	{
		m_Ptr++;
		return *this;
	}
	ArrayItrConst& operator++(int)
	{
		ArrayItrConst itr = *this;
		++(*this);
		return itr;
	}

	ArrayItrConst& operator--()
	{
		m_Ptr++;
		return *this;
	}
	ArrayItrConst& operator--(int)
	{
		ArrayItrConst itr = *this;
		--(*this);
		return itr;
	}

	ReferenceType operator[](int index)
	{
		return *(m_Ptr[index]);
	}

	PointerType operator->()
	{
		return m_Ptr;
	}
	ReferenceType operator*()
	{
		return *m_Ptr;
	}

	bool operator==(const ArrayItrConst& other) const { return m_Ptr == other.m_Ptr; }
	bool operator!=(const ArrayItrConst& other) const { return !(*this == other); }

private:
	PointerType m_Ptr;
};

class ArrayBase
{
public:
	virtual size_t Count() const { return 0; }
	virtual size_t GetElementSize() const { return 0; }
	virtual void* GetArrStartPtr() const { return nullptr; }
	virtual void Reserve(size_t capacity) { }
	virtual void SetSize(size_t size) { }
	virtual void AddDefault() { }
};

template<typename T>
class Array : ArrayBase
{
public:
	using ValueType = T;
	using Iterator = ArrayItr<Array<T>>;
	using ConstIterator = ArrayItrConst<Array<T>>;

public:
	Array()
	{
		Reserve(2);
	}

	T& operator[](size_t index)
	{
		return m_Data[index];
	}
	const T& operator[](size_t index) const
	{
		return m_Data[index];
	}

	virtual void Reserve(size_t capacity) override
	{
		if (capacity < m_Size)
			return;

		T* n = new T[capacity];
		for (int i = 0; i < m_Size; i++)
			n[i] = std::move(m_Data[i]);

		m_Capacity = capacity;
		std::swap(m_Data, n);
		delete[] n;
	}
	virtual void SetSize(size_t size) override
	{
		m_Size = size;
	}

	void Add(const T& value)
	{
		if (m_Size == m_Capacity)
			Reserve(m_Capacity * 2);
		m_Data[m_Size++] = value;
	}
	void Add(T&& value)
	{
		if (m_Size == m_Capacity)
			Reserve(m_Capacity * 2);
		m_Data[m_Size++] = value;
	}

	template<typename... Args>
	T& Emplace(Args&&... args)
	{
		if (m_Size >= m_Capacity)
			Realloc(m_Capacity + m_Capacity);
		new (&m_Data[m_Size]) T(std::forward<Args>(args)...);
		return m_Data[m_Size++];
	}

	void RemoveLast()
	{
		if (m_Size == 0)
			return;
		m_Size--;
		m_Data[m_Size].~T();
	}

	void Clear()
	{
		for (size_t i = 0; i < m_Size; i++)
			m_Data[i].~T();
		m_Size = 0;
	}

	virtual size_t Count() const override { return m_Size; }
	virtual size_t GetElementSize() const override { return sizeof(T); }
	virtual void* GetArrStartPtr() const override { return m_Data; }

	T* Data() { return m_Data; }
	const T* Data() const { return m_Data; }

	Iterator begin()
	{
		return Iterator(m_Data);
	}
	Iterator end()
	{
		return Iterator(m_Data + m_Size);
	}

	ConstIterator begin() const
	{
		return ConstIterator(m_Data);
	}
	ConstIterator end() const
	{
		return ConstIterator(m_Data + m_Size);
	}

protected:
	virtual void AddDefault() override final
	{
		Add(T());
	}

private:
	T* m_Data = nullptr;

	size_t m_Size = 0;
	size_t m_Capacity = 0;
};
