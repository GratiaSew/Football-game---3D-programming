// w1654554_Football_cw02.cpp : main project file.

#include <fstream>
#include <cstdlib>
#include <string>
#include <iostream>
#include <stdio.h>
#include "math.h"
#include "stdafx.h"
#include "freeglut.h"
#include <Windows.h>
#include <iostream>
#include <ctime>
#include <vector>

using namespace std;


int windowWidth = 1280;//widht of the game window
int windowHeight = 720;//height of the game window

static float worldRotation = 90.0;

GLfloat cameraPossition[3] = {0.0f,2.5f,-7.0f};

GLuint wallFormat, ballFormat, targetFormat, skyFormat, grassFormat,
redTargetFormat, blueTargetFormat, greenTargetFormat, 
palmBranchFormat, orangeFlowerFormat, yellowFlowerFormat,
slitherHorizontalFormat, slitherVerticleFormat;

GLfloat ballPossition[3] = { 0.0f,0.5f,0.0f };
GLfloat ballRotation = 0.0f;
GLfloat ballDiameter = 1.0f;

GLint imageWidth, imageHeight, imageComponents;
GLenum eFormat;

int score, attemps;

// part of extracted code "texture.c" by Michael Sweet (OpenGL SuperBible)
// texture buffers and stuff
int i;                       /* Looping var */
BITMAPINFO	*info;           /* Bitmap information */
GLubyte	    *bits;           /* Bitmap RGB pixels */
GLubyte     *ptr;            /* Pointer into bit buffer */
GLubyte	    *rgba;           /* RGBA pixel buffer */
GLubyte	    *rgbaptr;        /* Pointer into RGBA buffer */
GLubyte     temp;            /* Swapping variable */
GLenum		type;            /* Texture type */
GLuint		texture;         /* Texture object */

//each face lighting normals from each face to face
GLfloat faceLightingNormals[108] =
{
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,

	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,

	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,

	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,

	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f

};

GLfloat trangleForCubeVertexData[108] =
{

	//wind will happen to clockwise
	//each will happen with 3 triangles
	0.5f, -0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, 0.5f,

	0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, 0.5f,

	-0.5f, 0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, 0.5f,
	
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, 0.5f,
	
	0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,
	
	0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f
};

GLfloat gtextureCoordsForSkyFormat[72] = {
	//face 1
	0.75,0.33,      //    0,1,
	0.75,0.67,     //    1,1,
	0.5,0.33,     //    0,0,
	0.5,0.33,     //    0,0,
	0.75,0.67,    //    1,0,
	0.5,0.67,   //    1,1,

	//face 2
	0.5,1.0, //    1,1,
	0.25,1, //    0,1,
	0.5,0.67, //    1,0,
	0.5,0.67, //    1,0,
	0.25,1.0, //    0,1			
	
	//face 3
	0,0.67,//    1,1,
	0,0.33,//    0,1,
	0.25,0.67,//    1,0,
	0.25,0.67,//    1,0,
	0,0.33,//    0,1,
	0.25,0.33,//    0,0,
    
	//face 4
	0.25,0.0,//    0,1,
	0.5,0.0,//    1,1,
	0.25,0.33,//    0,0,
	0.25,0.33,//    0,0,
	0.5,0.0,//    1,1,
	0.5,0.33,//    0,0,
	
	//face 5
	0.5,0.67,//    1,0,
	0.25,0.67,//    0,0,
	0.5,0.33,//    1,1,
	0.5,0.33,//    1,1,
	0.25,0.67,//    0,0,
	0.25,0.33,//    0,1,
			  
	//face 6
	0.75,0.33,//    1,1,
	1.0,0.33,//    0,1,
	0.75,0.67,//    1,0,
	0.75,0.67,//    1,0,
	1.0,0.33,//    0,1,
	1.0,0.67//    0,0

};


typedef struct
{
	GLbyte	identityFieldSize;              // Size of ID field that follows header (0)
	GLbyte	colorMapType;           // 0 = None, 1 = paletted
	GLbyte	imageType;              // 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle
	unsigned short	colorMapEntry;  // First colour map entry
	unsigned short	colorMapSize; // Number of colors
	unsigned char 	colorMapBits;   // bits per palette entry
	unsigned short	xstart;         // image x origin
	unsigned short	ystart;         // image y origin
	unsigned short	width;          // width in pixels
	unsigned short	height;         // height in pixels
	GLbyte	bits;                   // bits per pixel (8 16, 24, 32)
	GLbyte	iDescriptor;             // image descriptor
}
TGAHEADER;
#pragma pack(8)

GLbyte *gltLoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat)
{
	FILE * filePointer;			// File pointer
	TGAHEADER tgaFileHeader;		// TGA file header
	unsigned long lImageSize;		// Size in bytes of image
	short sDepth;			// Pixel depth;
	GLbyte	*pBits = NULL;          // Pointer to bits

	// Default/Failed values
	*iWidth = 0;
	*iHeight = 0;
	*eFormat = GL_BGR_EXT;
	*iComponents = GL_RGB8;

	// Attempt to open the file
	//pFile = fopen(szFileName, "rb");
	fopen_s(&filePointer, szFileName, "rb");

	if (filePointer == NULL)
		return NULL;

	// Read in header (binary)
	fread(&(tgaFileHeader.identityFieldSize), sizeof(char), 1, filePointer);
	fread(&(tgaFileHeader.colorMapType), sizeof(char), 1, filePointer);
	fread(&(tgaFileHeader.imageType), sizeof(char), 1, filePointer);
	fread(&(tgaFileHeader.colorMapEntry), sizeof(short), 1, filePointer);
	fread(&(tgaFileHeader.colorMapSize), sizeof(short), 1, filePointer);
	fread(&(tgaFileHeader.colorMapEntry), sizeof(char), 1, filePointer);
	fread(&(tgaFileHeader.xstart), sizeof(short), 1, filePointer);
	fread(&(tgaFileHeader.ystart), sizeof(short), 1, filePointer);
	fread(&(tgaFileHeader.width), sizeof(short), 1, filePointer);
	fread(&(tgaFileHeader.height), sizeof(short), 1, filePointer);
	fread(&(tgaFileHeader.bits), sizeof(char), 1, filePointer);
	fread(&(tgaFileHeader.iDescriptor), sizeof(char), 1, filePointer);

	// Do byte swap for big vs little endian
#ifdef __APPLE__
	LITTLE_ENDIAN_WORD(&tgaHeader.colorMapStart);
	LITTLE_ENDIAN_WORD(&tgaHeader.colorMapLength);
	LITTLE_ENDIAN_WORD(&tgaHeader.xstart);
	LITTLE_ENDIAN_WORD(&tgaHeader.ystart);
	LITTLE_ENDIAN_WORD(&tgaHeader.width);
	LITTLE_ENDIAN_WORD(&tgaHeader.height);
#endif


	// Get width, height, and depth of texture
	*iWidth = tgaFileHeader.width;
	*iHeight = tgaFileHeader.height;
	sDepth = tgaFileHeader.bits / 8;

	// Put some validity checks here. Very simply, I only understand
	// or care about 8, 24, or 32 bit targa's.
	if (tgaFileHeader.bits != 8 && tgaFileHeader.bits != 24 && tgaFileHeader.bits != 32)
		return NULL;

	// Calculate size of image buffer
	lImageSize = tgaFileHeader.width * tgaFileHeader.height * sDepth;

	// Allocate memory and check for success
	pBits = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
	if (pBits == NULL)
		return NULL;

	// Read in the bits
	// Check for read error. This should catch RLE or other 
	// weird formats that I don't want to recognize
	if (fread(pBits, lImageSize, 1, filePointer) != 1)
	{
		free(pBits);
		return NULL;
	}

	// Set OpenGL format expected
	switch (sDepth)
	{
	case 3:
		*eFormat = GL_BGR_EXT;
		*iComponents = GL_RGB8;
		break;
	case 4:
		*eFormat = GL_BGRA_EXT;
		*iComponents = GL_RGBA8;
		break;
	case 1:
		*eFormat = GL_LUMINANCE;
		*iComponents = GL_LUMINANCE8;
		break;
	};


	// Done with File
	fclose(filePointer);

	// Return pointer to image data
	return pBits;
}

void setWindow() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (GLfloat)windowWidth / (GLfloat)windowHeight, 1.0f, 50.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, -1, 0, 0, 0, 0, 1, 0);
}

void setViewport(GLint left, GLint right, GLint bottom, GLint top) {
	glViewport(left, bottom, right - left, top - bottom);
}

void updateCameraAndLight() {
	gluLookAt(cameraPossition[0], cameraPossition[1], cameraPossition[2], 0, 1.0, 50, 0, 1, 0);
}

void createSky() {
	glPushMatrix();
	glShadeModel(GL_FLAT);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, skyFormat);
	glFrontFace(GL_CW);
	glRotatef(worldRotation, 0.0f, 0.5f, 0.0f);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT,0, faceLightingNormals);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, trangleForCubeVertexData);
	//   glTexCoordPointer(2, GL_FLOAT, 0, textureCoords);
	glTexCoordPointer(2, GL_FLOAT, 0, gtextureCoordsForSkyFormat);
	// draw a cube - type - start number - number of vertices to draw (so 3 for single triangle)
	glDrawArrays(GL_TRIANGLES, 0, 36);
	worldRotation += 0.1f;//speed of the world rotation

	if (worldRotation > 360.0f)
		worldRotation = 0.0f;
	// deactivate vertex arrays after drawing
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glFrontFace(GL_CCW);
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

}

GLfloat wallDistance = 20, wallLeft = 12, wallRight = -12, wallHeight = 7;

void createWalls() {


	glShadeModel(GL_SMOOTH);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, wallFormat);
	GLfloat diffuseColor[3] = { 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, diffuseColor);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f);   // coords for the texture
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(wallLeft, 0, wallDistance);

	glTexCoord2f(0.0f, 0.0f);  // coords for the texture
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(wallRight, 0, wallDistance);

	glTexCoord2f(0.0f, 1.0f);  // coords for the texture
	glNormal3f(0.0f, 0.0f, -1.0f);

	glVertex3f(wallRight, wallHeight, wallDistance);

	glTexCoord2f(1.0f, 1.0f);  // coords for the texture
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(wallLeft, wallHeight, wallDistance);

	//right wall
	glTexCoord2f(1.0f, 0.0f);   // coords for the texture
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(wallRight, 0, -wallDistance);

	glTexCoord2f(1.0f, 1.0f);  // coords for the texture
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(wallRight, wallHeight, -wallDistance);

	glTexCoord2f(0.0f, 1.0f);  // coords for the texture
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(wallRight, wallHeight, wallDistance);

	glTexCoord2f(0.0f, 0.0f);  // coords for the texture
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(wallRight, 0, wallDistance);

	//left wall
	glTexCoord2f(0.0f, 0.0f);   // coords for the texture
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(wallLeft, 0, -wallDistance);

	glTexCoord2f(1.0f, 0.0f);  // coords for the texture
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(wallLeft, 0, wallDistance);

	glTexCoord2f(1.0f, 1.0f);  // coords for the texture
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(wallLeft, wallHeight, wallDistance);

	glTexCoord2f(0.0f, 1.0f);  // coords for the texture
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(wallLeft, wallHeight, -wallDistance);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}

void createBall() {
	glShadeModel(GL_SMOOTH);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, ballFormat);
	glTranslatef(ballPossition[0], ballPossition[1], ballPossition[2]);
	glRotatef(ballRotation + 120, 1.0f, 0.0f, 0.0f);
	GLfloat diffuseColor[3] = { 0.8f,0.8f,0.8f };
	GLfloat specularColor[3] = { 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularColor);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10);
	glBegin(GL_LINE_LOOP);
	GLUquadricObj * quadric;// create the rendering tool
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluQuadricTexture(quadric, GL_TRUE);
	gluSphere(quadric, ballDiameter / 2, 36, 18);
	gluDeleteQuadric(quadric);
	glEnd();

	glPopMatrix();


	glShadeModel(GL_SMOOTH);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
	//draw the ball shadow
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	GLfloat targetPossions[3];
	//red targets
	glBindTexture(GL_TEXTURE_2D, targetFormat);
	glColor3f(1, 1, 1);

	targetPossions[0] = ballPossition[0] - ballDiameter*0.25f;
	targetPossions[1] = 0.05f;
	targetPossions[2] = ballPossition[2] + ballDiameter*0.25f;

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);   // glTexCoord for the format
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(targetPossions[0] + ballDiameter / 2, targetPossions[1], targetPossions[2] - ballDiameter / 2);

	glTexCoord2f(1.0f, 0.0f);  // glTexCoord for the format
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(targetPossions[0] - ballDiameter / 2, targetPossions[1], targetPossions[2] - ballDiameter / 2);

	glTexCoord2f(1.0f, 1.0f);  // glTexCoord for the format
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(targetPossions[0] - ballDiameter / 2, targetPossions[1], targetPossions[2] + ballDiameter / 2);

	glTexCoord2f(0.0f, 1.0f);  // glTexCoord for the format
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(targetPossions[0] + ballDiameter / 2, targetPossions[1], targetPossions[2] + ballDiameter / 2);
	glEnd();

	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);


	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}

void createGrass() {
	glShadeModel(GL_SMOOTH);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, grassFormat);
	GLfloat diffuseColor[3] = { 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, diffuseColor);

	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f);   // glTexCoord for the format
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-30, 0, 30);

	glTexCoord2f(0.0f, 0.0f);  // glTexCoord for the format
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(30, 0, 30);

	glTexCoord2f(0.0f, 1.0f);  // glTexCoord for the format
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(30, 0, -30);

	glTexCoord2f(1.0f, 1.0f);  // glTexCoord for the format
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-30, 0, -30);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}

void createBackground() {
	glShadeModel(GL_SMOOTH);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	GLfloat targetDeltas[3];	//the -0.1 is fixed to the target be visible, delta from bottom left
	float palmWidth, palmHeight;

	//palms
	glBindTexture(GL_TEXTURE_2D, palmBranchFormat);
	glColor3f(1, 1, 1);

	palmWidth = 2.5;
	palmHeight = wallHeight - 1.5;

	//palms in left side
	targetDeltas[0] = wallDistance;
	targetDeltas[1] = palmHeight;//this deltas will be used in the left wall
	targetDeltas[2] = -0.01;
	glBegin(GL_QUADS);
	for (int j = 0; j < 5; j++) {
		targetDeltas[0] -= (palmWidth + 1);
		glTexCoord2f(0.0f, 0.0f);   // glTexCoord for the format
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(wallLeft + targetDeltas[2], targetDeltas[1] - palmHeight, targetDeltas[0]);

		glTexCoord2f(1.0f, 0.0f);  // glTexCoord for the format
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(wallLeft + targetDeltas[2], targetDeltas[1] - palmHeight, targetDeltas[0] + palmWidth);

		glTexCoord2f(1.0f, 1.0f);  // glTexCoord for the format
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(wallLeft + targetDeltas[2], targetDeltas[1], targetDeltas[0] + palmWidth);

		glTexCoord2f(0.0f, 1.0f);  // glTexCoord for the format
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(wallLeft + targetDeltas[2], targetDeltas[1], targetDeltas[0]);
	}
	glEnd();

	//palms in right side
	targetDeltas[0] = wallDistance;
	targetDeltas[1] = palmHeight;//this deltas will be used in the right wall
	targetDeltas[2] = 0.1;
	glBegin(GL_QUADS);
	for (int j = 0; j < 5; j++) {
		targetDeltas[0] -= (palmWidth + 1);
		glTexCoord2f(0.0f, 1.0f);  // glTexCoord for the format
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(wallRight + targetDeltas[2], targetDeltas[1], targetDeltas[0]);

		glTexCoord2f(1.0f, 1.0f);  // glTexCoord for the format
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(wallRight + targetDeltas[2], targetDeltas[1], targetDeltas[0] + palmWidth);

		glTexCoord2f(1.0f, 0.0f);  // glTexCoord for the format
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(wallRight + targetDeltas[2], targetDeltas[1] - palmHeight, targetDeltas[0] + palmWidth);

		glTexCoord2f(0.0f, 0.0f);   // glTexCoord for the format
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(wallRight + targetDeltas[2], targetDeltas[1] - palmHeight, targetDeltas[0]);
	}
	glEnd();

	//flowers
	palmHeight = 1;
	palmWidth = 0.7;

	//orange color flowers
	glBindTexture(GL_TEXTURE_2D, orangeFlowerFormat);
	glColor3f(1, 1, 1);
	targetDeltas[0] = 0;
	targetDeltas[1] = 0;//this deltas will be used in the left wall
	targetDeltas[2] = -0.1;
	glBegin(GL_QUADS);
	for (int j = 0; j < 10; j++) {
		targetDeltas[0] += (palmWidth * 5);
		glTexCoord2f(0.0f, 0.0f);   // glTexCoord for the format
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(wallLeft - targetDeltas[0], targetDeltas[1], wallDistance + targetDeltas[2]);

		glTexCoord2f(1.0f, 0.0f);  // glTexCoord for the format
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(wallLeft - targetDeltas[0] - palmWidth, targetDeltas[1], wallDistance + targetDeltas[2]);

		glTexCoord2f(1.0f, 1.0f);  // glTexCoord for the format
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(wallLeft - targetDeltas[0] - palmWidth, targetDeltas[1] + palmHeight, wallDistance + targetDeltas[2]);

		glTexCoord2f(0.0f, 1.0f);  // glTexCoord for the format
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(wallLeft - targetDeltas[0], targetDeltas[1] + palmHeight, wallDistance + targetDeltas[2]);
	}
	glEnd();

	//yellow color flowers
	glBindTexture(GL_TEXTURE_2D, yellowFlowerFormat);
	glColor3f(1, 1, 1);
	targetDeltas[0] = 1.25;
	targetDeltas[1] = 0;//this deltas will be used in the left wall
	targetDeltas[2] = -0.2;
	glBegin(GL_QUADS);
	for (int j = 0; j < 7; j++) {
		glTexCoord2f(0.0f, 0.0f);   // glTexCoord for the format
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(wallLeft - targetDeltas[0], targetDeltas[1], wallDistance + targetDeltas[2]);

		glTexCoord2f(1.0f, 0.0f);  // glTexCoord for the format
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(wallLeft - targetDeltas[0] - palmWidth, targetDeltas[1], wallDistance + targetDeltas[2]);

		glTexCoord2f(1.0f, 1.0f);  // glTexCoord for the format
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(wallLeft - targetDeltas[0] - palmWidth, targetDeltas[1] + palmHeight, wallDistance + targetDeltas[2]);

		glTexCoord2f(0.0f, 1.0f);  // glTexCoord for the format
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(wallLeft - targetDeltas[0], targetDeltas[1] + palmHeight, wallDistance + targetDeltas[2]);
		targetDeltas[0] += (palmWidth  + 3);
	}
	glEnd();

	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}

void createScore() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glLoadIdentity();
	int x = windowWidth - 280, y = windowHeight - 48;
	glColor3f(1, 1, 1);
	char text[256];
	sprintf_s(text, "SCORE  %3d", score);
	for (int j = 0; j < strlen(text); j++) {
		glRasterPos2i(x, y);
		GLvoid *font_style1 = GLUT_BITMAP_TIMES_ROMAN_24;
		glutBitmapCharacter(font_style1, text[j]);
		x += 24;
	}
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

}

int hSlitherWidth, vSlitherHeight = 25;
int horizontalSlitherPossition, verticleSlitherPossition = 100;

void createSlithers() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glLoadIdentity();

	//positions in the slithers
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(50 + horizontalSlitherPossition - (hSlitherWidth / 2), windowHeight - 70);
	glVertex2f(50 + horizontalSlitherPossition + (hSlitherWidth / 2), windowHeight - 70);
	glVertex2f(50 + horizontalSlitherPossition + (hSlitherWidth / 2), windowHeight - 40);
	glVertex2f(50 + horizontalSlitherPossition - (hSlitherWidth / 2), windowHeight - 40);
	glEnd();
	glColor3f(0.8, 0.6, 0.2);
	glBegin(GL_QUADS);
	glVertex2f(50 + horizontalSlitherPossition - (hSlitherWidth / 2), windowHeight - 70);
	glVertex2f(50 + horizontalSlitherPossition + (hSlitherWidth / 2), windowHeight - 70);
	glVertex2f(50 + horizontalSlitherPossition + (hSlitherWidth / 2), windowHeight - 40);
	glVertex2f(50 + horizontalSlitherPossition - (hSlitherWidth / 2), windowHeight - 40);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(windowWidth - 80, 70 + verticleSlitherPossition - (vSlitherHeight / 2));
	glVertex2f(windowWidth - 50, 70 + verticleSlitherPossition - (vSlitherHeight / 2));
	glVertex2f(windowWidth - 50, 70 + verticleSlitherPossition + (vSlitherHeight / 2));
	glVertex2f(windowWidth - 80, 70 + verticleSlitherPossition + (vSlitherHeight / 2));
	glEnd();
	glColor3f(0.1, 0.8, 0.2);
	glBegin(GL_QUADS);
	glVertex2f(windowWidth - 80, 70 + verticleSlitherPossition - (vSlitherHeight / 2));
	glVertex2f(windowWidth - 50, 70 + verticleSlitherPossition - (vSlitherHeight / 2));
	glVertex2f(windowWidth - 50, 70 + verticleSlitherPossition + (vSlitherHeight / 2));
	glVertex2f(windowWidth - 80, 70 + verticleSlitherPossition + (vSlitherHeight / 2));
	glEnd();

	//arrows
	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_QUADS);
	glVertex2f(54, windowHeight - 30);
	glVertex2f(246, windowHeight - 30);
	glVertex2f(246, windowHeight - 28);
	glVertex2f(54, windowHeight - 28);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(246, windowHeight - 26);
	glVertex2f(246, windowHeight - 32);
	glVertex2f(250, windowHeight - 29);

	glVertex2f(54, windowHeight - 26);
	glVertex2f(50, windowHeight - 29);
	glVertex2f(54, windowHeight - 32);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(windowWidth - 92, 74);
	glVertex2f(windowWidth - 90, 74);
	glVertex2f(windowWidth - 90, 266);
	glVertex2f(windowWidth - 92, 266);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(windowWidth - 91, 270);
	glVertex2f(windowWidth - 94, 264);
	glVertex2f(windowWidth - 88, 264);
	glEnd();

	int x = windowWidth - 280, y = windowHeight - 48;
	glColor3f(1, 1, 1);

	glShadeModel(GL_SMOOTH);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, slitherHorizontalFormat);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);   // glTexCoord for the format
	glVertex2f(50, windowHeight - 70);

	glTexCoord2f(1.0f, 0.0f);  // glTexCoord for the format
	glVertex2f(250, windowHeight - 70);

	glTexCoord2f(1.0f, 1.0f);  // glTexCoord for the format
	glVertex2f(250, windowHeight - 40);

	glTexCoord2f(0.0f, 1.0f);  // glTexCoord for the format
	glVertex2f(50, windowHeight - 40);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, slitherVerticleFormat);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);   // glTexCoord for the format
	glVertex2f(windowWidth - 80, 70);

	glTexCoord2f(1.0f, 0.0f);  // glTexCoord for the format
	glVertex2f(windowWidth - 50, 70);

	glTexCoord2f(1.0f, 1.0f);  // glTexCoord for the format
	glVertex2f(windowWidth - 50, 270);

	glTexCoord2f(0.0f, 1.0f);  // glTexCoord for the format
	glVertex2f(windowWidth - 80, 270);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

}

typedef struct targetSTR {
	GLfloat position[3];
	float sizeMultiplier;
	GLuint texture;
	int points;
}Target;

std::vector<Target> targets;//An accessor for a pointer to the vector of pointers to Targets in the bundle. 

void createTargets() {
	glShadeModel(GL_SMOOTH);

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	GLfloat targetPossitions[3];	//the targetPossitions[2] is fixed to visibility of the deltas from left bottom
	float sizeMulti;
	
	//red targets
	for (std::vector<Target>::iterator iterator = targets.begin(); iterator != targets.end(); ++iterator) {
		Target target = (*iterator);
		glBindTexture(GL_TEXTURE_2D, target.texture);
		glColor3f(1, 1, 1);

		targetPossitions[0] = target.position[0];
		targetPossitions[1] = target.position[1];
		targetPossitions[2] = target.position[2];
		sizeMulti = target.sizeMultiplier;

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);   // glTexCoord for the format
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(wallLeft - targetPossitions[0], targetPossitions[1] - ballDiameter*sizeMulti, wallDistance + targetPossitions[2]);

		glTexCoord2f(1.0f, 0.0f);  // glTexCoord for the format
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(wallLeft - targetPossitions[0] - ballDiameter*sizeMulti, targetPossitions[1] - ballDiameter*sizeMulti, wallDistance + targetPossitions[2]);

		glTexCoord2f(1.0f, 1.0f);  // glTexCoord for the format
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(wallLeft - targetPossitions[0] - ballDiameter*sizeMulti, targetPossitions[1], wallDistance + targetPossitions[2]);

		glTexCoord2f(0.0f, 1.0f);  // glTexCoord for the format
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(wallLeft - targetPossitions[0], targetPossitions[1], wallDistance + targetPossitions[2]);
		glEnd();
	}

	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}





void initFormat(void) {
	GLbyte*pBytes1;

	//ball format
	glGenTextures(1, &ballFormat);
	glBindTexture(GL_TEXTURE_2D, ballFormat);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//setting the tga image file to the texture
	pBytes1 = gltLoadTGA("textures/FootballCompleteMap.tga", &imageWidth, &imageHeight, &imageComponents, &eFormat);

	//GLint gluBuild2DMipmaps(	GLenum target,GLint internalFormat,GLsizei width,GLsizei height,GLenum format,GLenum type,const void * data);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, imageWidth, imageHeight, eFormat, GL_UNSIGNED_BYTE, pBytes1);
	free(pBytes1);

	//ball shadow
	glGenTextures(1, &targetFormat);
	glBindTexture(GL_TEXTURE_2D, targetFormat);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//setting the tga image file to the texture
	pBytes1 = gltLoadTGA("textures/targetDull.tga", &imageWidth, &imageHeight, &imageComponents, &eFormat);

	//GLint gluBuild2DMipmaps(	GLenum target,GLint internalFormat,GLsizei width,GLsizei height,GLenum format,GLenum type,const void * data);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, imageWidth, imageHeight, eFormat, GL_UNSIGNED_BYTE, pBytes1);
	free(pBytes1);

	//sky format
	glGenTextures(1, &skyFormat);
	glBindTexture(GL_TEXTURE_2D, skyFormat);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//setting the tga image file to the texture
	pBytes1 = gltLoadTGA("textures/stormydays_large.tga", &imageWidth, &imageHeight, &imageComponents, &eFormat);

	//GLint gluBuild2DMipmaps(	GLenum target,GLint internalFormat,GLsizei width,GLsizei height,GLenum format,GLenum type,const void * data);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, imageWidth, imageHeight, eFormat, GL_UNSIGNED_BYTE, pBytes1);
	free(pBytes1);

	//grass format
	glGenTextures(1, &grassFormat);
	glBindTexture(GL_TEXTURE_2D, grassFormat);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//setting the tga image file to the texture
	pBytes1 = gltLoadTGA("textures/grass.tga", &imageWidth, &imageHeight, &imageComponents, &eFormat);

	//GLint gluBuild2DMipmaps(	GLenum target,GLint internalFormat,GLsizei width,GLsizei height,GLenum format,GLenum type,const void * data);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, imageWidth, imageHeight, eFormat, GL_UNSIGNED_BYTE, pBytes1);
	free(pBytes1);

	//wall format
	glGenTextures(1, &wallFormat);
	glBindTexture(GL_TEXTURE_2D, wallFormat);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//setting the tga image file to the texture
	pBytes1 = gltLoadTGA("textures/bricks.tga", &imageWidth, &imageHeight, &imageComponents, &eFormat);

	//GLint gluBuild2DMipmaps(	GLenum target,GLint internalFormat,GLsizei width,GLsizei height,GLenum format,GLenum type,const void * data);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, imageWidth, imageHeight, eFormat, GL_UNSIGNED_BYTE, pBytes1);
	free(pBytes1);

	//target format
	//red
	glGenTextures(1, &redTargetFormat);
	glBindTexture(GL_TEXTURE_2D, redTargetFormat);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//setting the tga image file to the texture
	pBytes1 = gltLoadTGA("textures/targetRed.tga", &imageWidth, &imageHeight, &imageComponents, &eFormat);

	//GLint gluBuild2DMipmaps(	GLenum target,GLint internalFormat,GLsizei width,GLsizei height,GLenum format,GLenum type,const void * data);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, imageWidth, imageHeight, eFormat, GL_UNSIGNED_BYTE, pBytes1);
	free(pBytes1);
	//green
	glGenTextures(1, &greenTargetFormat);
	glBindTexture(GL_TEXTURE_2D, greenTargetFormat);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//setting the tga image file to the texture
	pBytes1 = gltLoadTGA("textures/targetGreen.tga", &imageWidth, &imageHeight, &imageComponents, &eFormat);

	//GLint gluBuild2DMipmaps(	GLenum target,GLint internalFormat,GLsizei width,GLsizei height,GLenum format,GLenum type,const void * data);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, imageWidth, imageHeight, eFormat, GL_UNSIGNED_BYTE, pBytes1);
	free(pBytes1);

	//blue
	glGenTextures(1, &blueTargetFormat);
	glBindTexture(GL_TEXTURE_2D, blueTargetFormat);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//setting the tga image file to the texture
	pBytes1 = gltLoadTGA("textures/targetBlue.tga", &imageWidth, &imageHeight, &imageComponents, &eFormat);

	//GLint gluBuild2DMipmaps(	GLenum target,GLint internalFormat,GLsizei width,GLsizei height,GLenum format,GLenum type,const void * data);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, imageWidth, imageHeight, eFormat, GL_UNSIGNED_BYTE, pBytes1);
	free(pBytes1);

	//flowers
	glGenTextures(1, &orangeFlowerFormat);
	glBindTexture(GL_TEXTURE_2D, orangeFlowerFormat);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//setting the tga image file to the texture
	pBytes1 = gltLoadTGA("textures/orangeFlowerFinal5.tga", &imageWidth, &imageHeight, &imageComponents, &eFormat);

	//GLint gluBuild2DMipmaps(	GLenum target,GLint internalFormat,GLsizei width,GLsizei height,GLenum format,GLenum type,const void * data);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, imageWidth, imageHeight, eFormat, GL_UNSIGNED_BYTE, pBytes1);
	free(pBytes1);

	//flowers
	glGenTextures(1, &yellowFlowerFormat);
	glBindTexture(GL_TEXTURE_2D, yellowFlowerFormat);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//setting the tga image file to the texture
	pBytes1 = gltLoadTGA("textures/yellowFlowerFinal.tga", &imageWidth, &imageHeight, &imageComponents, &eFormat);

	//GLint gluBuild2DMipmaps(	GLenum target,GLint internalFormat,GLsizei width,GLsizei height,GLenum format,GLenum type,const void * data);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, imageWidth, imageHeight, eFormat, GL_UNSIGNED_BYTE, pBytes1);
	free(pBytes1);

	//palm branch
	glGenTextures(1, &palmBranchFormat);
	glBindTexture(GL_TEXTURE_2D, palmBranchFormat);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//setting the tga image file to the texture
	pBytes1 = gltLoadTGA("textures/palmBranchA.tga", &imageWidth, &imageHeight, &imageComponents, &eFormat);

	//GLint gluBuild2DMipmaps(	GLenum target,GLint internalFormat,GLsizei width,GLsizei height,GLenum format,GLenum type,const void * data);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, imageWidth, imageHeight, eFormat, GL_UNSIGNED_BYTE, pBytes1);
	free(pBytes1);

	//sliders
	//slider horizontal
	glGenTextures(1, &slitherHorizontalFormat);
	glBindTexture(GL_TEXTURE_2D, slitherHorizontalFormat);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//setting the tga image file to the texture
	pBytes1 = gltLoadTGA("textures/fillBarHorizontal.tga", &imageWidth, &imageHeight, &imageComponents, &eFormat);

	//GLint gluBuild2DMipmaps(	GLenum target,GLint internalFormat,GLsizei width,GLsizei height,GLenum format,GLenum type,const void * data);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, imageWidth, imageHeight, eFormat, GL_UNSIGNED_BYTE, pBytes1);
	free(pBytes1);

	//slider vertical
	glGenTextures(1, &slitherVerticleFormat);
	glBindTexture(GL_TEXTURE_2D, slitherVerticleFormat);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//setting the tga image file to the texture
	pBytes1 = gltLoadTGA("textures/fillBarVerticalR.tga", &imageWidth, &imageHeight, &imageComponents, &eFormat);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, imageWidth, imageHeight, eFormat, GL_UNSIGNED_BYTE, pBytes1);
	free(pBytes1);

}

void render(void) {
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Save the matrix state and do the rotations
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glPushMatrix();


	//glTranslatef(0.0f, 0.0f, -1.0f);
	updateCameraAndLight();
	createSky();
	createGrass();
	createWalls();
	createBall();
	createTargets();
	createBackground();

	//2d drawing
	createScore();
	createSlithers();


	//glPopMatrix();

	glutSwapBuffers();

}

void initBall() {
	ballPossition[0] = 0.0f;
	ballPossition[1] = 0.5f;
	ballPossition[2] = 0.0f;
	ballRotation = 0.0f;
}

void checkBallColision() {
	printf("checking in collision : %f %f %f\n", ballPossition[0], ballPossition[1], ballPossition[2]);
	for (std::vector<Target>::iterator iterator = targets.begin(); iterator != targets.end(); ++iterator) {
		Target target = (*iterator);

		if (ballPossition[0] < wallLeft - target.position[0] - ballDiameter / 4
			&& ballPossition[0] > wallLeft - target.position[0] - ballDiameter*target.sizeMultiplier + ballDiameter / 4
			&& ballPossition[1] < target.position[1] - ballDiameter / 4
			&& ballPossition[1] > target.position[1] - ballDiameter*target.sizeMultiplier + ballDiameter / 4)
		{
			iterator->texture = targetFormat;
			score += target.points;
			iterator->points = 0;
		}
	}
}

int shooting = 0;
float ballDirectionVector[3] = { 0,0,0 };

void TimerFunc(int x)
{
	if (shooting) {
		ballPossition[0] += ballDirectionVector[0];
		ballPossition[1] += ballDirectionVector[1];
		ballPossition[2] += ballDirectionVector[2];
		ballRotation += 7.2;
		if (ballPossition[2] > wallDistance - ballDiameter / 2) {
			checkBallColision();
			initBall();
			shooting = 0;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(25, TimerFunc, 1);
}

void initLight() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	//GLfloat light_ambient[] = { backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3] };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 0.0, 10.0, 0.0, 1.0 };
	GLfloat light_direction[] = { 0.0, -1.0, 0.0, 1.0 };

	//glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);

	//GLfloat light_ambient1[] = { backgr0undColor[0], backgr0undColor[1], backgroundColor[2], backgr0undColor[3] };
	GLfloat light_diffuse1[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular1[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position1[] = { ballPossition[0], ballPossition[1], ballPossition[2] - 10, 1.0 };
	GLfloat light_direction1[] = { 0.0, 0.0, 1.0, 1.0 };

	//glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_direction1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 15.0f);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 200.0f);
}

void initTargets() {
	targets.clear();
	Target targt;

	//red = points 30 will be added
	targt.points = 30;
	targt.sizeMultiplier = 1.0f;

	targt.position[0] = 0.5f;
	targt.position[1] = 1.5f;
	targt.position[2] = -0.1f;
	targt.texture = redTargetFormat;
	targets.push_back(targt);

	targt.position[0] = 5.7f;
	targt.position[1] = 4.8f;
	targets.push_back(targt);

	targt.position[0] = 13.7f;
	targt.position[1] = 2.0f;
	targets.push_back(targt);

	targt.position[0] = 21.0f;
	targt.position[1] = 5.6f;
	targets.push_back(targt);

	targt.position[0] = 8.0f;
	targt.position[1] = 7.0f;
	targets.push_back(targt);

	//blue = points 20 will be added
	targt.points = 20;
	targt.sizeMultiplier = 1.5f;
	targt.texture = blueTargetFormat;

	targt.position[0] = 8.0f;
	targt.position[1] = 3.3f;
	targets.push_back(targt);

	targt.position[0] = 12.1f;
	targt.position[1] = 5.9f;
	targets.push_back(targt);

	//green = points 10 will be added
	targt.points = 10;
	targt.sizeMultiplier = 2.0f;
	targt.texture = greenTargetFormat;

	targt.position[0] = 1.1f;
	targt.position[1] = 6.1f;
	targets.push_back(targt);

	targt.position[0] = 16.8f;
	targt.position[1] = 3.6f;
	targets.push_back(targt);
}

void calculateDirection() {
	
	float directionZ = 20.0f; //always foward

	float directionX = horizontalSlitherPossition - hSlitherWidth / 2; // map 0 to 200(size of the slither) - hSlitherWidth - 4;
	directionX = directionX / (200 - hSlitherWidth - 4);	//map to 0 to 1.0;
	directionX = directionX * (24 - ballDiameter); //map to 0 to distance between (wall-the ball);
	directionX = directionX - wallLeft + ballDiameter / 2; // always map between the 2 walls
	directionX = directionX * -1;
	float directionY = verticleSlitherPossition - vSlitherHeight / 2;
	directionY = directionY / (200 - vSlitherHeight - 4);
	directionY = directionY * (wallHeight - ballDiameter);
	directionY = directionY + ballDiameter / 2;

	printf("direction vector : [%f, %f, %f]\n", directionX, directionY, directionZ);

	double norm = (directionX * directionX + directionY * directionY + directionZ * directionZ) / 4;
	directionX /= norm;
	directionY /= norm;
	directionZ /= norm;
	printf("normalized direction vector : [%f, %f, %f]\n", directionX, directionY, directionZ);

	ballDirectionVector[0] = directionX;
	ballDirectionVector[1] = directionY;
	ballDirectionVector[2] = directionZ;

}

void restartGame() {
	score = 0;
	attemps = 0;
	shooting = 0;

	initBall();

	initTargets();

	hSlitherWidth = 25;
	horizontalSlitherPossition = 100;

	vSlitherHeight = 25;
	verticleSlitherPossition = 100;
}

//adding 10 marks for on successfull shoot
void ballShoot() {
	if (attemps < 20) {
		attemps++;
		calculateDirection();
		shooting = 1;
	}
}

void onKeyDown(unsigned char key, int x, int y) {
	//keyboard commands
	if (!shooting) {
		switch (key) {
		case 'R':
		case 'r':
			restartGame();	// restarts the game.
			break;
		case ' ':
		case 'z':
		case 'Z':
			ballShoot();//shooting the ball to the back wall
			break;
		}
	}
}

void onKeyDownSpecial(int key, int x, int y) {
	//size of slider : 200
	if (attemps < 10) {
		switch (key) {
		case GLUT_KEY_UP:
			if (verticleSlitherPossition < 200 - vSlitherHeight / 2 - 4)
				verticleSlitherPossition++;
			break;
		case GLUT_KEY_DOWN:
			if (verticleSlitherPossition > vSlitherHeight / 2)
				verticleSlitherPossition--;
			break;
		case GLUT_KEY_LEFT:
			if (horizontalSlitherPossition > hSlitherWidth / 2)
				horizontalSlitherPossition--;
			break;
		case GLUT_KEY_RIGHT:
			if (horizontalSlitherPossition < 200 - hSlitherWidth / 2 - 4)
				horizontalSlitherPossition++;
			break;
		}
	}
}


void mainInit() {
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	setWindow();
	setViewport(0, windowWidth, 0, windowHeight);

	// enables hidden faces

	glFrontFace(GL_CCW);

	glEnable(GL_CULL_FACE);

	// enabled z-buffer
	glEnable(GL_DEPTH_TEST);

	//trangleForCubeVertexData[108]
	for (int j = 0; j < 108; j++) {
		trangleForCubeVertexData[j] *= 50;
	}
	
	initFormat();
	initLight();
	initTargets();
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("3D Football Game");
	glutDisplayFunc(render);

	//keyboard functions
	glutKeyboardFunc(onKeyDown);
	glutSpecialFunc(onKeyDownSpecial);

	mainInit();
	glutTimerFunc(25, TimerFunc, 1);
	//glutIdleFunc(TimerFunc);
	glutMainLoop();
	return 0;

}


