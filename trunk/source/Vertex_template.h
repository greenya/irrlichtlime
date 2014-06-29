#if !defined(_REFCLASS_) || !defined(_WRAPCLASS_)
#error _REFCLASS_ and _WRAPCLASS_ must be defined for this file to process.
#endif

public:

	Vector3Df Position;
	Vector3Df Normal;
	Color Color;
	Vector2Df TCoords;

	virtual String^ ToString() override
	{
		return String::Format("Vertex3D: Type={0}; Position={1}", Type, Position);
	}