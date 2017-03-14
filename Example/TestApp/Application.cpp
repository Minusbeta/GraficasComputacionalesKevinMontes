#include "Application.h"

void TestApp::InitVars() {
	DtTimer.Init();
	Position = CVector4D(0.0f, 0.0f, -1.0f, 1);
	Orientation = CVector4D(0.0f, 0.0f, 0.0f, 0);
	Offset = CVector4D(0, 0, 10.0f, 0);
	OriVer = 0;
	OriHor = 0;
}

void TestApp::CreateAssets() {
	PrimitiveMgr.SetVP(&VP);
	int indexMesh = PrimitiveMgr.CreateCerdo("Models/Scene.X");
	Meshes[0].CreateInstance(PrimitiveMgr.GetPrimitive(indexMesh), &VP);
	indexMesh = PrimitiveMgr.CreateCerdo("Models/Cerdo.X");
	Meshes[1].CreateInstance(PrimitiveMgr.GetPrimitive(indexMesh), &VP);
	/*int indexTriangle = PrimitiveMgr.CreateTriangle();
	Triangles[0].CreateInstance(PrimitiveMgr.GetPrimitive(indexTriangle), &VP);*/
	CMatrix4D View;
	CVector4D Pos = CVector4D(0.0f, 1.0f, 5.0f, 1);
	Up = CVector4D(0.0f, 1.0f, 0.0f, 0);
	CVector4D LookAt = CVector4D(0.0001f, 0.0001f, 0.0001f, 1) - Pos;

	View = LookAtRH(Pos, LookAt, Up);
	CMatrix4D Proj;
	Proj = PerspectiveFovRH(45 * 3.1416 / 180, 1280.0f / 720.0f, 1.0f, 10000.0f);
	VP = View*Proj;


}

void TestApp::DestroyAssets() {
	PrimitiveMgr.DestroyPrimitives();
}

void TestApp::OnUpdate() {
	DtTimer.Update();

	OnInput();

	Offset.x = cosf(OriVer) * sinf(OriHor);
	Offset.y = sinf(OriVer);
	Offset.z = cosf(OriVer) * cosf(OriHor);
	Offset.w = 0;

	View = LookAtRH(Position, Position + Offset, Up);

	OnDraw();
}

void TestApp::OnDraw() {


	CMatrix4D Proj;
	Proj = PerspectiveFovRH(45 * 3.1416 / 180, 1280.0f / 720.0f, 0.1f, 1000.0f);
	VP = Scaling(0.1f, 0.1f, 0.1f)*View*Proj;

	pFramework->pVideoDriver->Clear();

	Meshes[0].Draw();
	Meshes[1].Draw();
	//Triangles[0].Draw();

	pFramework->pVideoDriver->SwapBuffers();
}

void TestApp::OnInput() {

	/*if (IManager.PressedKey(SDLK_UP)) {
	Position.y += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_DOWN)) {
	Position.y -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_LEFT)) {
	Position.x -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_RIGHT)) {
	Position.x += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_z)) {
	Position.z -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_x)) {
	Position.z += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP_PLUS)) {
	Scaling.x += 1.0f*DtTimer.GetDTSecs();
	Scaling.y += 1.0f*DtTimer.GetDTSecs();
	Scaling.z += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP_MINUS)) {
	Scaling.x -= 1.0f*DtTimer.GetDTSecs();
	Scaling.y -= 1.0f*DtTimer.GetDTSecs();
	Scaling.z -= 1.0f*DtTimer.GetDTSecs();
	}

	/*if (IManager.PressedKey(SDLK_KP5)) {
	Orientation.x -= 60.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP6)) {
	Orientation.x += 60.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP2)) {
	Orientation.y -= 60.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP3)) {
	Orientation.y += 60.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP0)) {
	Orientation.z -= 60.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP_PERIOD)) {
	Orientation.z += 60.0f*DtTimer.GetDTSecs();
	}*/

	if (IManager.PressedKey(SDLK_UP))
	{
		CVector4D AuxOffset = Offset;
		Position = Position + Normalize(AuxOffset) * 2 * DtTimer.GetDTSecs();
	}
	if (IManager.PressedKey(SDLK_DOWN))
	{
		CVector4D AuxOffset = Offset;
		Position = Position - Normalize(AuxOffset) * 2 * DtTimer.GetDTSecs();
	}
	if (IManager.PressedKey(SDLK_RIGHT))
	{
		CVector4D AuxOffset = Offset;
		CVector4D Dir = Cross3(Normalize(AuxOffset), Up);
		Position = Position + Dir * 2 * DtTimer.GetDTSecs();
	}
	if (IManager.PressedKey(SDLK_LEFT))
	{
		CVector4D AuxOffset = Offset;
		CVector4D Dir = Cross3(Up, Normalize(AuxOffset));
		Position = Position + Dir * 2 * DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_w))
	{
		OriVer += 0.5*DtTimer.GetDTSecs();
	}
	if (IManager.PressedKey(SDLK_s))
	{
		OriVer -= 0.5*DtTimer.GetDTSecs();
	}
	if (IManager.PressedKey(SDLK_a))
	{
		OriHor += 0.5*DtTimer.GetDTSecs();
	}
	if (IManager.PressedKey(SDLK_d))
	{
		OriHor -= 0.5*DtTimer.GetDTSecs();
	}
	if (IManager.MouseMove)
	{
		float deltax = IManager.lastX - IManager.mx;
		float deltay = IManager.lastY - IManager.my;
		OriHor += deltax*DtTimer.GetDTSecs();
		OriVer += deltay*DtTimer.GetDTSecs();

	}
}

void TestApp::OnPause() {

}

void TestApp::OnResume() {

}

void TestApp::OnReset() {

}