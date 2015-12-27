#pragma once

#include "stdafx.h"

namespace IrrlichtLime
{

generic <typename T>
public ref class NativeList abstract : NativeCollection<T>, IList<T>	//interface not implemented yet
{
public:
	
	virtual property T default[int]
	{
		T get(int index) = 0; 
		void set(int index, T value) = 0;
	}

	//Already in NativeCollection
	/*property int Count
	{
		int get() = 0;
	}*/

	property bool IsReadOnly
	{
		virtual bool get() override sealed
		{
			return false;	//NativeLists are writeable
		}
	}
	
	virtual void Add(T item) override = 0;
	virtual void Insert(int index, T item) = 0;
	virtual void RemoveAt(int index) = 0;
	virtual void Clear() override = 0;

internal:	//for invisible methods
#pragma warning (push)
#pragma warning (disable: 4100)	//hide unused parameter warnings
	virtual bool Remove(T item) override sealed
	{
		throw gcnew NotSupportedException();
	}

	virtual int IndexOf(T item) sealed = IList<T>::IndexOf
	{
		throw gcnew NotSupportedException();
	}
#pragma warning (pop)
};

template <typename RefClass, typename WrappingClass, typename NativeClass>
private ref class NativeListIrrArrayTemplate : NativeList<RefClass>
{
public:

	NativeListIrrArrayTemplate(irr::core::array<NativeClass>& ar)
	{
		this->ar = &ar;
	}

	property RefClass default[int]
	{
		virtual RefClass get(int index) override sealed
		{
			LIME_ASSERT(index >= 0 && index < Count);
			return WrappingClass::Wrap((*ar)[index]);
		}

		virtual void set(int index, RefClass value) override sealed
		{
			LIME_ASSERT(index >= 0 && index < Count);
			(*ar)[index] = value.ToNative();
		}
	}

	property int Count
	{
		virtual int get() override sealed
		{
			return ar->size();
		}
	}

	virtual void Add(RefClass item) override sealed
	{
		ar->push_back(item.ToNative());
	}

	virtual void Insert(int index, RefClass item) override sealed
	{
		LIME_ASSERT(index >= 0 && index <= Count);
		ar->insert(item.ToNative(), index);
	}

	//virtual bool Remove(RefClass item) override sealed
	//{
	//	//won't compile, SGUISprites don't have an == operator
	//	throw gcnew NotSupportedException("Not supported, because not implemented in Irrlicht itself.");
	//	/*
	//	int index = ar->linear_search(item.ToNative());	//signed int, because it can return -1
	//	if (index == -1)
	//		return false;
	//	else
	//	{
	//		ar->erase(index);
	//		return true;
	//	}*/
	//}

	virtual void RemoveAt(int index) override sealed
	{
		LIME_ASSERT(index >= 0 && index < Count);
		ar->erase(index);
	}

	virtual void Clear() override sealed
	{
		ar->clear();
	}

	virtual NativeIterator<RefClass>^ GetIterator() override sealed
	{
		return gcnew Iterator(*ar);
	}

private:

	//Helper class for enumerating
	ref class Iterator : NativeIterator<RefClass>
	{
	public:

		Iterator (irr::core::array<NativeClass>& ar)
		{
			this->ar = &ar;
			reset = true;
		}

		property RefClass Current
		{
			virtual RefClass get() override sealed
			{
				return WrappingClass::Wrap((*ar)[index]);
			}
		}

		virtual bool MovePrevious() override
		{
			if (ar->empty())
				return false;

			if (reset)	//reset? set to array end
			{
				index = ar->size() - 1;
				reset = false;
			}
			else
			{
				if (index < 0) //passed the first element?
					return false;
				index--;
			}

			return true;
		}

		virtual bool MoveNext() override
		{
			if (ar->empty())
				return false;

			if (reset)	//reset? set to array start
			{
				index = 0;
				reset = false;
			}
			else
			{
				if (!(index < ar->size() - 1)) //passed the last element?
					return false;
				index++;
			}

			return true;
		}

		virtual void Reset() override
		{
			reset = true;
		}

		irr::core::array<NativeClass>* ar;
		unsigned int index;
		bool reset;
	};

private:

	irr::core::array<NativeClass>* ar;	//non const, so we can call push_back, etc
};
}