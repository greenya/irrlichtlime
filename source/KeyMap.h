#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;
using namespace System::Collections::Generic; // for Dictionary and List

namespace IrrlichtLime {

public ref class KeyMap
{
public:

	KeyMap()
	{
		m_Map = gcnew Dictionary<KeyAction, List<KeyCode>^>();
	}

	void Add(KeyAction action, KeyCode keyCode)
	{
		if (!m_Map->ContainsKey(action))
			m_Map->Add(action, gcnew List<KeyCode>());

		if (!m_Map[action]->Contains(keyCode))
			m_Map[action]->Add(keyCode);
	}

	property Dictionary<KeyAction, List<KeyCode>^>^ Map
	{
		Dictionary<KeyAction, List<KeyCode>^>^ get() { return m_Map; }
	}

internal:

	// Allocates and fills SKeyMap array, returning poiter on it and count of elements in it.
	// Note: you should delete keyMapArray pointer manually.
	int GetSKeyMapArray(SKeyMap*& keyMapArray)
	{
		core::array<SKeyMap> l;

		for each (KeyValuePair<KeyAction, List<KeyCode>^>^ v in m_Map)
		{
			for each (KeyCode c in v->Value)
			{
				SKeyMap m;
				m.Action = (EKEY_ACTION)v->Key;
				m.KeyCode = (EKEY_CODE)c;
				l.push_back(m);
			}
		}

		if (l.size() == 0)
			return 0;

		keyMapArray = new SKeyMap[l.size()];
		for (u32 i = 0; i < l.size(); i++)
			keyMapArray[i] = l[i];

		return l.size();
	}

private:

	Dictionary<KeyAction, List<KeyCode>^>^ m_Map;
};

} // end namespace IrrlichtLime