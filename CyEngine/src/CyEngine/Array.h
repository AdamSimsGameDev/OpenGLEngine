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
	virtual int Count() const { return 0; }
	virtual int GetElementSize() const { return 0; }
	virtual void* GetArrStartPtr() const { return nullptr; }
	virtual void Reserve(int capacity) { }
	virtual void SetSize(int size) { }
	virtual void AddDefault() { }
	virtual void RemoveAt(int position) { }
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
	Array(std::initializer_list<T> l)
	{
		Reserve(SizeTToInt(l.size()));
		for (auto ptr = l.begin(); ptr < l.end(); ptr++)
		{
			Add(*ptr);
		}
	}
	Array(const Array& arr)
	{
		Reserve(arr.m_Capacity);
		m_Size = arr.m_Size;
		for (int i = 0; i < m_Size; i++)
		{
			if (std::is_pointer<T>())
			{
				m_Data[i] = arr.m_Data[i];
			}
			else 
			{
				m_Data[i] = T(arr.m_Data[i]);
			}
		}
	}
	Array(Array&& arr) noexcept
	{
		m_Size = arr.m_Size;
		m_Capacity = arr.m_Capacity;

		arr.m_Size = 0;
		arr.m_Capacity = 0;

		std::swap(m_Data, arr.m_Data);
		::operator delete(arr.m_Data, m_Capacity * sizeof(T));
		arr.m_Size = 0;
	}
	~Array()
	{
		for (int i = 0; i < m_Size; i++)
		{
			if (!std::is_pointer<T>())
			{
				m_Data[i].~T();
			}
		}
		m_Size = 0;
		m_Data = nullptr;
	}

	Array& operator=(const Array& arr)
	{
		Reserve(arr.m_Capacity);
		m_Size = arr.m_Size;
		for (int i = 0; i < m_Size; i++)
		{
			if (std::is_pointer<T>())
			{
				m_Data[i] = arr.m_Data[i];
			}
			else
			{
				m_Data[i] = T(arr.m_Data[i]);
			}
		}
		return *this;
	}
	Array& operator=(Array&& arr) noexcept
	{
		m_Size = arr.m_Size;
		m_Capacity = arr.m_Capacity;

		arr.m_Size = 0;
		arr.m_Capacity = 0;

		std::swap(m_Data, arr.m_Data);
		::operator delete(arr.m_Data, m_Capacity * sizeof(T));
		return *this;
	}

	T* operator*() { return m_Data; }
	const T* operator*() const { return m_Data; }

	T& operator[](int index)
	{
		return m_Data[index];
	}
	const T& operator[](int index) const
	{
		return m_Data[index];
	}

	const T& First() const { return m_Data[0]; }
	T& First() { return m_Data[0]; }

	const T& Last() const { return m_Data[Count() - 1]; }
	T& Last() { return m_Data[Count() - 1]; }

	T Pop()
	{
		T t = (*this)[Count() - 1];
		RemoveAt(Count() - 1);
		return t;
	}

	virtual void Reserve(int capacity) override
	{
		if (capacity < m_Size)
			return;

		T* n = (T*)::operator new(capacity * sizeof(T));
		for (int i = 0; i < m_Size; i++)
			n[i] = std::move(m_Data[i]);
		for (int i = 0; i < m_Size; i++)
			m_Data[i].~T();

		std::swap(m_Data, n);
		::operator delete(n, m_Capacity * sizeof(T));
		m_Capacity = capacity;
	}
	virtual void SetSize(int size) override
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
		m_Data[m_Size++] = T(value);
	}

	template<typename... Args>
	T& Emplace(Args&&... args)
	{
		if (m_Size >= m_Capacity)
			Reserve(m_Capacity + m_Capacity);
		new (&m_Data[m_Size]) T(std::forward<Args>(args)...);
		return m_Data[m_Size++];
	}

	void RemoveLast()
	{
		RemoveAt(m_Size - 1);
	}

	void Clear()
	{
		for (int i = 0; i < m_Size; i++)
			m_Data[i].~T();
		m_Size = 0;
	}

	int IndexOf(const T& item) const 
	{
		for (int i = 0; i < m_Size; i++)
		{
			if (item == m_Data[i])
			{
				return i;
			}
		}
		return -1;
	}

	bool Remove(const T& item)
	{
		int index = IndexOf(item);
		if (index == -1)
			return false;
		RemoveAt(index);
		return true;
	}

	void InsertAt(const T& item, int position)
	{
		// if the position is at the end, just add the item to the end.
		if (position >= m_Size)
		{
			Add(item);
			return;
		}

		// reserve space, should we need to.
		if (m_Size >= m_Capacity)
			Reserve(m_Capacity + m_Capacity);

		// set the size
		m_Size = m_Size + 1;

		// loop backwards
		for (int i = m_Size - 1; i > position; i--)
		{
			m_Data[i] = m_Data[i - 1];
		}
		m_Data[position] = item;
	}

	virtual void RemoveAt(int position) override final
	{
		if (position < 0 || position >= m_Size)
			return;
		for (int i = position; i < m_Size - 1; i++)
		{
			m_Data[i] = m_Data[i + 1];
		}
		m_Size--;
	}

	void Reverse()
	{
		int start = 0;
		int end = Count() - 1;
		for (; start < end; start++, end--)
		{
			T p = m_Data[start];
			m_Data[start] = m_Data[end];
			m_Data[end] = p;
		}
	}

	virtual int Count() const override { return m_Size; }
	virtual int GetElementSize() const override { return sizeof(T); }
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

	int m_Size = 0;
	int m_Capacity = 0;
};
