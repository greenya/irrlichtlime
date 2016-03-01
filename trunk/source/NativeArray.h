#pragma once

#include "stdafx.h"

using namespace System::Collections::Generic;

namespace IrrlichtLime
{

generic <typename T>
public ref class NativeArray abstract : public IList<T>
{
public:

	virtual property T default [int]
	{
		T get(int index) = 0;
		void set (int index, T value) = 0;
	}

	virtual property int Count
	{
		int get() = 0;
	}

	virtual array<T>^ ToArray()
	{
		int length = Count;
		array<T>^ a = gcnew array<T>(length);
		for (int i = 0; i < length; i++)
			a[i] = this[i];
		return a;
	}

	virtual IEnumerator<T>^ GetEnumerator()
	{
		return gcnew NativeArrayEnumerator(this);
	}

	property bool IsReadOnly
	{
		virtual bool get() = 0;
	}

#pragma warning (push)
#pragma warning (disable: 4100)	//hide unused parameter warnings
	virtual void Add(T item) sealed
	{
		throw gcnew NotSupportedException("Changing element count is not supported!");
	}

	virtual void Insert(int index, T item)
	{
		throw gcnew NotSupportedException("Changing element count is not supported!");
	}

	virtual bool Remove(T item) sealed
	{
		throw gcnew NotSupportedException("Changing element count is not supported!");
	}

	virtual void RemoveAt(int index) sealed
	{
		throw gcnew NotSupportedException("Changing element count is not supported!");
	}

	virtual void Clear() sealed
	{
		throw gcnew NotSupportedException("Changing element count is not supported!");
	}
#pragma warning (pop)

	virtual bool Contains(T item)	//subclasses may have a faster implementation
	{
		IEqualityComparer<T>^ comparer = EqualityComparer<T>::Default;
		int length = Count;
		for (int i = 0; i < length; i++)
			if (comparer->Equals(this[i], item))
				return true;
		return false;
	}

	virtual int IndexOf(T item)
	{
		IEqualityComparer<T>^ comparer = EqualityComparer<T>::Default;
		int length = Count;
		for (int i = 0; i < length; i++)
			if (comparer->Equals(this[i], item))
				return i;
		return -1;
	}

	virtual void CopyTo(array<T>^ array, int arrayIndex)
	{
		if (array == nullptr)
			throw gcnew ArgumentNullException("array");
		if (arrayIndex < 0)
			throw gcnew ArgumentOutOfRangeException("arrayIndex");
		if (arrayIndex + Count > array->Length)
			throw gcnew ArgumentException("arrayIndex");

		int count = Count;

		for (int i = 0; i < count; i++)
			array[i + arrayIndex] = this[i];
	}

private:

	virtual System::Collections::IEnumerator^ GetEnumerator2() sealed = System::Collections::IEnumerable::GetEnumerator
	{
		return GetEnumerator();
	}

	ref class NativeArrayEnumerator sealed : public IEnumerator<T>
	{
	public:

		virtual bool MoveNext() sealed
		{
			if( currentIndex < a->Count - 1 )
            {
                currentIndex++;
                return true;
            }
            return false;
		}

		property T Current
		{
			virtual T get() sealed
			{
				return a[currentIndex];
			}
		}

		virtual void Reset() sealed
		{
			currentIndex = -1;
		}

	internal:

		NativeArrayEnumerator(NativeArray<T>^ a)
			: a(a), currentIndex(-1)
		{ }

	private:

		virtual Object^ getCurrent2() sealed = System::Collections::IEnumerator::Current::get
		{
			return Current;
		}

		~NativeArrayEnumerator()
		{ }

		int currentIndex;
		NativeArray<T>^ a;
	};

internal:

	virtual void* GetPointer() = 0;	//should return a pointer to the first element, but can also return null if not possible

};

template <typename RefClass, typename WrapClass, typename NativeClass>
public ref class NativeArrayReadOnlyTemplate sealed : public NativeArray<RefClass>
{
	
internal:

	NativeArrayReadOnlyTemplate(const core::array<NativeClass>* ar)
	{
		this->ar = ar;
	}

public:

#pragma warning (push)
#pragma warning (disable: 4100)	//hide unused parameter warnings
	property RefClass default [int]
	{
		virtual RefClass get(int index) override sealed
		{
			return WrapClass::Wrap((*ar)[index]);
		}

		virtual void set(int index, RefClass value) override sealed
		{
			throw gcnew NotSupportedException();
		}
	}
#pragma warning (pop)


	property int Count
	{
		virtual int get() override sealed
		{
			return ar->size();
		}
	}

	property bool IsReadOnly
	{
		virtual bool get() override sealed
		{
			return true;
		}
	}

internal:
	
	virtual void* GetPointer() override sealed
	{
		return const_cast<core::array<NativeClass>*>(ar)->pointer();	//Note: make sure to read only on this one!
	}

	const core::array<NativeClass>* ar;
};
}