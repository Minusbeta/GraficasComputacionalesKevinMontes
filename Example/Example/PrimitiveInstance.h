#ifndef UAD_PRIMITIVE_INSTANCE_H
#define UAD_PRIMITIVE_INSTANCE_H

#include "PrimitiveBase.h"
//#include <d3dx9math.h>
#include "CMatrix4D.h"

#include "Config.h"

class PrimitiveInst {
public:
	void	CreateInstance(PrimitiveBase *pPrim, CMatrix4D *pVP) {
		pBase = pPrim;
		pViewProj = pVP;
		Position = Identity();
		Scale = Identity();
		Rotation_X = Identity();
		Rotation_Y = Identity();
		Rotation_Z = Identity();
		Final = Identity();
	}

	void	TranslateAbsolute(float x, float y, float z);
	void	RotateXAbsolute(float ang);
	void	RotateYAbsolute(float ang);
	void	RotateZAbsolute(float ang);
	void	ScaleAbsolute(float sc);

	void	TranslateRelative(float x, float y, float z);
	void	RotateXRelative(float ang);
	void	RotateYRelative(float ang);
	void	RotateZRelative(float ang);
	void	ScaleRelative(float sc);

	void	Update();
	void	Draw();

	CMatrix4D		Position;
	CMatrix4D		Scale;
	CMatrix4D		Rotation_X;
	CMatrix4D		Rotation_Y;
	CMatrix4D		Rotation_Z;
	CMatrix4D		Final;

	CMatrix4D		*pViewProj;

	PrimitiveBase	*pBase;
};


#endif