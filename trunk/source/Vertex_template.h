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

private:

	//Position property
	virtual Vector3Df getPosition() sealed = IVertex3D::Position::get { return Position; }
	virtual void setPosition(Vector3Df value) sealed = IVertex3D::Position::set { Position = value; }
	
	//Normal property
	virtual Vector3Df getNormal() sealed = IVertex3D::Normal::get { return Normal; }
	virtual void setNormal(Vector3Df value) sealed = IVertex3D::Normal::set { Normal = value; }

	//Color property
	virtual Video::Color getColor() sealed = IVertex3D::Color::get { return Color; }
	virtual void setColor(Video::Color value) sealed = IVertex3D::Color::set { Color = value; }

	//TCoords property
	virtual Vector2Df getTCoords() sealed = IVertex3D::TCoords::get { return TCoords; }
	virtual void setTCoords(Vector2Df value) sealed = IVertex3D::TCoords::set { TCoords = value; }