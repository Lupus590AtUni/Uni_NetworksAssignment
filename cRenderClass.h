#pragma once

//https://msdn.microsoft.com/en-us/library/windows/desktop/ms737629(v=vs.85).aspx
// I think opengl glut may need some window.h stuff, so add this just in case
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <iostream>
#include <tchar.h>
#include "GL/glut.h"
#include "NA_Vector.h"

struct sRGB
{
	float r, g, b;
};

class cRenderClass
{
public:

	bool mouseIsScary = false;
	NA_Vector mousePos;

	cRenderClass(const int, const int);
	~cRenderClass();

	void create(int argc, _TCHAR* argv[]);
	void loop();

	void clear();

	void render();
	void setColour(float, float, float);
	void setPointSize(int);
	void drawPixel(int, int);

private:

	int		 m_sw, m_sh;
	int		 m_point_size;
	float	*m_buffer;
	sRGB	 m_colour;
};



extern void winReshapeFunc(GLint w, GLint h);
extern void renderScene();
extern void update();
extern void mouse(int x, int y);
extern void click(int button, int state, int x, int y);
extern void key(unsigned char c, int x, int y);