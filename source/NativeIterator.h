#pragma once

#include "stdafx.h"

using namespace System::Collections::Generic;

namespace IrrlichtLime
{

generic <typename T>
public ref class NativeIterator abstract : IEnumerator<T>
{
public:
	
	virtual property T Current
	{
		T get() = 0;
	}

	virtual bool MovePrevious() = 0;
	virtual bool MoveNext() = 0;
	virtual void Reset() = 0;

	virtual ~NativeIterator() {}

private:

	virtual Object^ getCurrent2() sealed = System::Collections::IEnumerator::Current::get
	{
		return Current;
	}

};

//RefClass is the class, which will be returned in the Current property
//WrappingClass is the classname (without gc handle), whose Wrap method will be called, to wrap the native object
//NativeClass is the class
template <typename RefClass, typename WrappingClass, typename NativeClass>
private ref class IteratorIrrListTemplate sealed : NativeIterator<RefClass>
{
public:

	IteratorIrrListTemplate(const irr::core::list<NativeClass*>& list)
	{
		this->list = &list;
		iter = nullptr;
	}

	property RefClass Current
	{
		virtual RefClass get() override sealed
		{
			return (RefClass)WrappingClass::Wrap(**iter);	//* is overloaded and returns the object the iterator is pointing on
		}
	}

	virtual bool MovePrevious() override sealed
	{
		if (iter == nullptr)
		{
			if (list->empty())
				return false;

			iter = new irr::core::list<NativeClass*>::ConstIterator(list->getLast());
			return true;
		}
		else if ((*iter) == (list->begin()))
			return false;
		else
		{
			--(*iter);
			return true;
		}
	}

	virtual bool MoveNext() override sealed
	{
		if (iter == nullptr)
		{
			if (list->empty())
				return false;

			iter = new irr::core::list<NativeClass*>::ConstIterator(list->begin());
			return true;
		}
		else if ((*iter) == (list->getLast()))
			return false;
		else
		{
			++(*iter);
			return true;
		}
	}

	virtual void Reset() override sealed
	{
		if (iter != nullptr)
		{
			delete iter;
			iter = nullptr;
		}
	}

	!IteratorIrrListTemplate()
	{
		Reset();
	}

	virtual ~IteratorIrrListTemplate()
	{
		this->!IteratorIrrListTemplate();
	}

private:

	const irr::core::list<NativeClass*>* list;
	typename irr::core::list<NativeClass*>::ConstIterator* iter;	//typename is needed. don't know why exactly (I tried it also iside the brackets, but there it doesn't work...)
};

generic <typename T>
public ref class NativeCollection abstract : ICollection<T>
{
public:

	virtual NativeIterator<T>^ GetIterator() = 0;
	
	property int Count
	{
		virtual int get() = 0;
	}

	property bool IsReadOnly
	{
		virtual bool get()
		{
			return true;
		}
	}

	virtual bool Contains(T item)
	{
		IEqualityComparer<T>^ comparer = EqualityComparer<T>::Default;

		for each (T listItem in this)
			if (comparer->Equals(listItem, item))
				return true;
		return false;
	}

	virtual void CopyTo(array<T>^ array, int arrayIndex)
	{
		if (array == nullptr)
			throw gcnew ArgumentNullException("array");
		if (arrayIndex < 0)
			throw gcnew ArgumentOutOfRangeException("arrayIndex");
		if (arrayIndex + Count > array->Length)
			throw gcnew ArgumentException("arrayIndex");

		int index = arrayIndex;

		for each (T listItem in this)
			array[index++] = listItem;
	}

protected:

	virtual IEnumerator<T>^ GetEnumerator() sealed = IEnumerable<T>::GetEnumerator
	{
		return GetIterator();
	}

	virtual System::Collections::IEnumerator^ GetEnumerator2() sealed = System::Collections::IEnumerable::GetEnumerator
	{
		return GetIterator();
	}
	
internal:	//for invisible methods

#pragma warning (push)
#pragma warning (disable: 4100)	//hide unused parameter warnings
	virtual void Add(T item) = ICollection<T>::Add
	{
		throw gcnew NotSupportedException();
	}

	virtual bool Remove(T item) = ICollection<T>::Remove
	{
		throw gcnew NotSupportedException();
	}
#pragma warning (pop)

	virtual void Clear() = ICollection<T>::Clear
	{
		throw gcnew NotSupportedException();
	}
};

template <typename RefClass, typename WrappingClass, typename NativeClass>
private ref class CollectionIrrListTemplate sealed : NativeCollection<RefClass>
{
public:

	CollectionIrrListTemplate(const irr::core::list<NativeClass*>& list)
	{
		this->list = &list;
	}

	virtual NativeIterator<RefClass>^ GetIterator() override sealed
	{
		return gcnew IteratorIrrListTemplate<RefClass, WrappingClass, NativeClass>(*list);
	}

	property int Count
	{
		virtual int get() override sealed
		{
			return list->size();
		}
	}

	//TODO: implement here, so it is faster. but we don't have a unified way to access the native objects, so it is not possible now
	/*virtual bool Contains(RefClass item) override sealed
	{
	}*/

private:

	const irr::core::list<NativeClass*>* list;
};

}