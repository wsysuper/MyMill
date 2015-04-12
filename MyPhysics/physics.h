
#include <math.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include <drawstuff/drawstuff.h>
#include <ode/ode.h>

#ifndef DEFAULT_PATH_TO_TEXTURES
#ifdef WIN32
#define DEFAULT_PATH_TO_TEXTURES "..\\textures\\"
#else
#define DEFAULT_PATH_TO_TEXTURES "../textures/"
#endif
#endif

#ifndef DRAWSTUFF_TEXTURE_PATH
#define DRAWSTUFF_TEXTURE_PATH "../drawstuff/textures"
#endif

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

// constants to convert degrees to radians and the reverse
#define RAD_TO_DEG (180.0/M_PI)
#define DEG_TO_RAD (M_PI/180.0)

// light vector. LIGHTZ is implicitly 1
#define LIGHTX (1.0f)
#define LIGHTY (0.4f)

// ground and sky
#define SHADOW_INTENSITY (0.65f)
#define GROUND_R (0.5f) 	// ground color for when there's no texture
#define GROUND_G (0.5f)
#define GROUND_B (0.3f)

const float ground_scale = 1.0f/1.0f;	// ground texture scale (1/size)
const float ground_ofsx = 0.5;		// offset of ground texture
const float ground_ofsy = 0.5;
const float sky_scale = 1.0f/4.0f;	// sky texture scale (1/size)
const float sky_height = 1.0f;		// sky height above viewpoint

//***************************************************************************
// PPM image object

typedef unsigned char byte;

class Image {
	int image_width,image_height;
	byte *image_data;
public:
	Image (char *filename);
	// load from PPM file
	~Image();
	int width() { return image_width; }
	int height() { return image_height; }
	byte *data() { return image_data; }
};



//***************************************************************************
// Texture object.

class Texture {
	Image *image;
	GLuint name;
public:
	Texture (char *filename);
	~Texture();
	void bind (int modulate);
};

//***************************************************************************
// OpenGL utility stuff

void setCamera (float x, float y, float z, float h, float p, float r);

// sets the material color, not the light color

void setColor (float r, float g, float b, float alpha);
void setTransform (const float pos[3], const float R[12]);
//void setTransformD (const double pos[3], const double R[12]);

//***************************************************************************

void setShadowTransform();

void drawConvex (float *_planes,unsigned int _planecount,
						float *_points,
						unsigned int _pointcount,
						unsigned int *_polygons);

void drawBox (const float sides[3]);

void drawPatch (float p1[3], float p2[3], float p3[3], int level);

void drawSphere();

void drawSphereShadow (float px, float py, float pz, float radius);

void drawTriangle (const float *v0, const float *v1, const float *v2, int solid);

void drawCapsule (float l, float r);

void drawCylinder (float l, float r, float zoffset);

void normalizeVector3 (float v[3]);

