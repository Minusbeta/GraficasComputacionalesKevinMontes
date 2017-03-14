
#include "PrimitiveManager.h"
#include "TriangleGL.h"
#include "CubeGL.h"
#include "MeshCerdo.h"

PrimitiveBase*	PrimitiveManager::GetPrimitive(unsigned int index) {
	if (index >= primitives.size())
		return 0;

	return primitives[index];
}

int  PrimitiveManager::CreateTriangle() {
	PrimitiveBase *primitive = new Trangle();
	primitive->Create();
	primitives.push_back(primitive);
	return (int)(primitives.size()-1);
}

int	 PrimitiveManager::CreateCube(){
	PrimitiveBase *primitive = new Cube();
	primitive->Create();
	primitives.push_back(primitive);
	return (int)(primitives.size() - 1);
}

int PrimitiveManager::CreateCerdo(char *fname)
{
	PrimitiveBase *primitive = new CerdoGL();
	primitive->Create(fname);
	primitives.push_back(primitive);
	return (int)(primitives.size() - 1);
}

void PrimitiveManager::DrawPrimitives() {
	for(unsigned int i=0;i<primitives.size();i++){
		primitives[i]->Draw(0,&(*pVP).m[0][0]);
	}
}

void PrimitiveManager::DestroyPrimitives() {
	for (unsigned int i = 0; i < primitives.size(); i++) {
		primitives[i]->Destroy();
		delete primitives[i];
	}
	primitives.clear();
}