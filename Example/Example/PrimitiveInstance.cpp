#include "PrimitiveInstance.h"

void PrimitiveInst::TranslateAbsolute(float x, float y, float z) {
	Position = Translation(x, y, z);
}

void PrimitiveInst::RotateXAbsolute(float ang) {
	Rotation_X = RotationX(ang*3.1416 / 180);
}

void PrimitiveInst::RotateYAbsolute(float ang) {
	Rotation_Y = RotationY(ang*3.1416 / 180);
}

void PrimitiveInst::RotateZAbsolute(float ang) {
	Rotation_Z = RotationZ(ang*3.1416 / 180);
}

void PrimitiveInst::ScaleAbsolute(float sc) {
	Scale = Scaling(sc, sc, sc);
}

void PrimitiveInst::TranslateRelative(float x, float y, float z) {
	CMatrix4D tmp;
	tmp = Translation(x, y, z);
	Position = Position * tmp;
}

void PrimitiveInst::RotateXRelative(float ang) {
	CMatrix4D tmp;
	tmp = RotationX(ang*3.1416 / 180);
	Rotation_X = Rotation_X * tmp;
}

void PrimitiveInst::RotateYRelative(float ang) {
	CMatrix4D tmp;
	tmp = RotationY(ang*3.1416 / 180);
	Rotation_Y = Rotation_Y * tmp;
}

void PrimitiveInst::RotateZRelative(float ang) {
	CMatrix4D tmp;
	tmp = RotationZ(ang*3.1416 / 180);
	Rotation_Z = Rotation_Z * tmp;
}

void PrimitiveInst::ScaleRelative(float sc) {
	CMatrix4D tmp;
	tmp = Scaling(sc, sc, sc);
	Scale = Scale * tmp;
}

void PrimitiveInst::Update() {
	Final = Scale*Rotation_X*Rotation_Y*Rotation_Z*Position;
}

void PrimitiveInst::Draw() {
	pBase->Draw(&Final.m[0][0], &(*pViewProj).m[0][0]);
}
