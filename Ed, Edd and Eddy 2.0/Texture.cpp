#include "stdafx.h"

CTexture::CTexture(char * file)
{
	IsLoaded = false;
	_id = -1;
	_file = file;
	_magFilter = GL_LINEAR;
	_minFilter = GL_LINEAR;
}

CTexture::CTexture(char * file, int magFilter, int minFilter)
{
	IsLoaded = false;
	_id = -1;
	_file = file;
	_magFilter = magFilter;
	_minFilter = minFilter;
}

CTexture::~CTexture(void)
{
}

bool CTexture::Load(void)
{
	Bitmap *tex = new Bitmap();
	if (!tex->loadBMP(_file)) {
		cout << "ERROR: Cannot read texture file \"" << _file << "\"." << endl;;
		cout << "ERROR INFO: " << tex->error << endl;
		return false;
	}

	width = tex->width;
	height = tex->height;

	glGenTextures(1, &_id);

	glBindTexture(GL_TEXTURE_2D, _id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _magFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _minFilter);

	if (_minFilter == GL_LINEAR_MIPMAP_LINEAR || _minFilter == GL_LINEAR_MIPMAP_NEAREST) {
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, tex->width, tex->height, GL_RGB, GL_UNSIGNED_BYTE, tex->data);
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->width, tex->height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->data);
	}

	delete tex;

	IsLoaded = true;

	return true;
}

GLuint CTexture::GetID(void)
{
	if (!IsLoaded) {
		Load();
	}
	return _id;
}

int CTexture::GetWidth(void) {
	return width;
}
int CTexture::GetHeight(void) {
	return height;
}

