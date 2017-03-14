#ifndef UAD_CUBE_GL_H
#define UAD_CUBE_GL_H

#include "Config.h"

#include "UtilsGL.h"

#ifdef USING_OPENGL_ES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "TexturaGLh.h"
#elif defined(USING_D3D11)
#include "TextureD3D.h"
#include <D3Dcompiler.h>
#endif

#include "CMatrix4D.h"
#include "PrimitiveBase.h"

class Cube : public PrimitiveBase {
public:
	Cube()
#ifdef USING_OPENGL_ES
		: shaderID(0)
#endif
	{}

#ifdef USING_D3D11
	struct CBuffer {
		CMatrix4D WVP;
		CMatrix4D World;
	};
#endif

	void Create();
	void Create(char *) {}
	void Transform(float *t);
	void Draw(float *t, float *vp);
	void Destroy();

#ifdef USING_OPENGL_ES
	GLuint	shaderID;
	GLint	vertexAttribLoc;
	GLint	normalAttribLoc;
	GLint	uvAttribLoc;
	GLint	diffuseLoc;


	GLint  matWorldViewProjUniformLoc;
	GLint  matWorldUniformLoc;

	GLuint			VB;
	GLuint			IB;
#elif defined(USING_D3D11)
	ComPtr<ID3D11Buffer>		IB;
	ComPtr<ID3D11Buffer>		VB;
	ComPtr<ID3D11VertexShader>  pVS;
	ComPtr<ID3D11PixelShader>   pFS;
	ComPtr<ID3DBlob>            VS_blob;
	ComPtr<ID3DBlob>            FS_blob;
	ComPtr<ID3D11InputLayout>   Layout;
	ComPtr<ID3D11Buffer>        pd3dConstantBuffer;

	Cube::CBuffer	CnstBuffer;
#endif

	int		TexId;
	CVertex			vertices[24];
	unsigned short	indices[36];
	CMatrix4D	transform;
	Textura		*tex;
};


#endif