#if !defined(_REFCLASS_) || !defined(_WRAPCLASS_) || !defined(_WRAPTYPE_)
#error _REFCLASS_, _WRAPCLASS_ and _WRAPTYPE_ must be defined for this file to process.
#endif

public ref class _REFCLASS_ : Lime::NativeValue<_WRAPCLASS_>
{
	#include "Dimension2D_template.h"
};