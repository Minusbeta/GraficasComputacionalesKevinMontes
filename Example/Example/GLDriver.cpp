#include "GLDriver.h"
#include <iostream>
#include <string>

void EGLError(const char* c_ptr) {
	EGLint iErr = eglGetError();
	if (iErr != EGL_SUCCESS) {
		std::cout << "EGL CALL: " << c_ptr << " Error Code: " << iErr << std::endl;
	}
}

void	GLDriver::InitDriver() {
	EGLint numConfigs, w, h;
	HDC	hDC = GetDC(eglWindow);
	eglDisplay = eglGetDisplay(hDC);

	EGLError("eglGetDisplay");

	EGLint iMajorVersion, iMinorVersion;

	if (!eglInitialize(eglDisplay, &iMajorVersion, &iMinorVersion)) {
		std::cout << "Failed to initialize egl" << std::endl;
	}

	eglBindAPI(EGL_OPENGL_ES_API);

	EGLError("eglBindAPI");

	const EGLint attribs[] = {
		EGL_SURFACE_TYPE,	EGL_WINDOW_BIT,
		EGL_RENDERABLE_TYPE,	EGL_OPENGL_ES2_BIT,
		EGL_BLUE_SIZE,		8,
		EGL_GREEN_SIZE,		8,
		EGL_RED_SIZE,		8,
		EGL_ALPHA_SIZE,		8,
		EGL_DEPTH_SIZE,		16,
		EGL_NONE
	};

	eglChooseConfig(eglDisplay, attribs, &eglConfig, 1, &numConfigs);

	EGLError("eglBindAPI");

	eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, eglWindow, NULL);

	EGLError("eglCreateWindowSurface");

	EGLint ai32ContextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
	eglContext = eglCreateContext(eglDisplay, eglConfig, NULL, ai32ContextAttribs);

	EGLError("eglCreateContext");

	if (eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext) == EGL_FALSE) {
		std::cout << "Failed to make current" << std::endl;
		return;
	}

	eglQuerySurface(eglDisplay, eglSurface, EGL_WIDTH, &w);
	eglQuerySurface(eglDisplay, eglSurface, EGL_HEIGHT, &h);
	
	std::string GL_Version = std::string((const char*)glGetString(GL_VERSION));
	std::string GL_Extensions = std::string((const char*)glGetString(GL_EXTENSIONS));
	std::cout << "GL Version: " << GL_Version << "\n\nExtensions\n\n" << GL_Extensions << std::endl;
}

void	GLDriver::CreateSurfaces() {

}

void	GLDriver::DestroySurfaces() {

}

void	GLDriver::Update() {

}

void	GLDriver::DestroyDriver() {
	eglDestroySurface(eglDisplay, eglSurface);
	eglDestroyContext(eglDisplay, eglContext);
	eglTerminate(eglDisplay);
}

void	GLDriver::SetWindow(void *window) {
	eglWindow = GetActiveWindow();
}

void	GLDriver::Clear() {
	glClearColor(1.0, 0.8117647058823529,0.0,1.0);  //The world is a yellow canvas
	
	glClear(GL_COLOR_BUFFER_BIT);
}

void	GLDriver::SwapBuffers() {
	eglSwapBuffers(eglDisplay, eglSurface);
}