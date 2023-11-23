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

template<typename T, size_t size>
class FixedArray
{
public:
	using ValueType = T;
	using Iterator = ArrayItr<FixedArray<T, size>>;
	using ConstIterator = ArrayItrConst<FixedArray<T, size>>;

public:
	constexpr size_t Count() const { return size; }

	T& operator[](size_t index) { return m_Data[index]; }
	const T& operator[](size_t index) const { return m_Data[index]; }

	T* Data() { return m_Data; }
	const T* Data() const { return m_Data; }

	Iterator begin()
	{
		return Iterator(m_Data);
	}
	Iterator end()
	{
		return Iterator(m_Data + size);
	}

	ConstIterator begin() const
	{
		return ConstIterator(m_Data);
	}
	ConstIterator end() const
	{
		return ConstIterator(m_Data + size);
	}

private:
	T m_Data[size];
};

template<typename T>
class Array
{
public:
	using ValueType = T;
	using Iterator = ArrayItr<Array<T>>;
	using ConstIterator = ArrayItrConst<Array<T>>;

public:
	Array()
	{
		Realloc(2);
	}
	Array(const Array& other)
	{
		Realloc(other.m_Capacity);
		m_Size = other.m_Size;
		*m_Data = *other.m_Data;
	}
	~Array()
	{
		Clear();
	}

	void Add(const T& value)
	{
		if (m_Size >= m_Capacity)
			Realloc(m_Capacity + m_Capacity);
		new(&m_Data[m_Size]) T(std::move(value));
		m_Size++;
	}
	void Add(T&& value)
	{
		if (m_Size >= m_Capacity)
			Realloc(m_Capacity + m_Capacity);
		new(&m_Data[m_Size]) T(std::move(value));
		m_Size++;
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

	size_t Count() const { return m_Size; }

	T& operator[](size_t index) { return m_Data[index]; }
	const T& operator[](size_t index) const { return m_Data[index]; }

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

private:
	void Realloc(size_t newCapacity)
	{
		T* n = (T*)::operator new(newCapacity * sizeof(T));

		size_t size = m_Size;
		if (newCapacity < size)
			size = newCapacity;

		for (size_t i = 0; i < size; ++i)
			new (&n[i]) T(std::move(m_Data[i]));

		for (size_t i = 0; i < m_Size; ++i)
			m_Data[i].~T();

		::operator delete(m_Data, m_Capacity * sizeof(T));
		m_Size = size;
		m_Data = n;
		m_Capacity = newCapacity;
	}

private:
	T* m_Data = nullptr;

	size_t m_Size = 0;
	size_t m_Capacity = 0;
};
