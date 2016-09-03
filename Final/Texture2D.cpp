#include "Texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

stbi_uc* _image;

Texture2D::Texture2D(char * filename)
{
	int comp;
	// Load the image
	_image = stbi_load(filename, &_width, &_height, &comp, STBI_rgb_alpha);
	if (_image == nullptr) throw "Failed to load texture";
	glGenTextures(1, &_id);
}

Texture2D::~Texture2D()
{
	if (_rescaledImageData)
		::free(_rescaledImageData);

	delete _image;
}

void Texture2D::Init()
{

	GLsizei xdim2, ydim2;
	void *imgp;

	xdim2 = 1;
	while (xdim2 <= _width)
		xdim2 *= 2;
	xdim2 /= 2;
	ydim2 = 1;
	while (ydim2 <= _height)
		ydim2 *= 2;
	ydim2 /= 2;

	// rescale it is not a 
	if ((_width != xdim2) || (_height != ydim2))
	{
		_rescaledImageData = (unsigned long *) ::realloc(_rescaledImageData,
			xdim2 * ydim2 * sizeof(unsigned long));
		gluScaleImage(GL_RGBA, _width, _height,
			GL_UNSIGNED_BYTE, _image, xdim2, ydim2,
			GL_UNSIGNED_BYTE, _rescaledImageData);
		imgp = _rescaledImageData;
	}
	else
		imgp = _image;

	glBindTexture(GL_TEXTURE_2D, _id);
	{
		// Set textre parameters
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, xdim2, ydim2, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, imgp);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

}

void Texture2D::Enable()
{
	glBindTexture(GL_TEXTURE_2D, _id);
	glEnable(GL_TEXTURE_2D);
}

void Texture2D::Disable()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}
