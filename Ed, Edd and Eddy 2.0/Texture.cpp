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
	unsigned char * tmp_data = 0;
	Bitmap *texb = new Bitmap();
	CPCX * texp = new CPCX();
	if (strstr(_file, ".bmp") || strstr(_file, ".BMP")) {	
		
		if (!texb->LoadBMP(_file)) {
			cout << "ERROR: Cannot read texture file \"" << _file << "\"." << endl;;
			cout << "ERROR INFO: " << texb->error << endl;
			return false;
		}
		width = texb->width;
		height = texb->height;
		tmp_data = texb->data;
		type = 'B';
//		delete tex;
	}
	else if (strstr(_file, ".pcx") || strstr(_file, ".PCX")) {
		
		if (!texp->LoadPCXTexture(_file)) {
			cout << "ERROR: Cannot read texture file \"" << _file << "\"." << endl;;
			//cout << "ERROR INFO: " << tex->error << endl;
			return false;
		}
		width = texp->width;
		height = texp->height;
		tmp_data = texp->data;
		type = 'P';
	//	delete tex;
	}
	/*	if (!tex->LoadBMP(_file)) {
			cout << "ERROR: Cannot read texture file \"" << _file << "\"." << endl;;
			cout << "ERROR INFO: " << tex->error << endl;
			return false;
		}*/
		
		glGenTextures(1, &_id);
		glBindTexture(GL_TEXTURE_2D, _id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _magFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _minFilter);
	

		switch (type)
		{
		case 'B':
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, tmp_data);
			break;
		case 'P':
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, tmp_data);
			break;
		default:
			break;
		}
		//if (_minFilter == GL_LINEAR_MIPMAP_LINEAR || _minFilter == GL_LINEAR_MIPMAP_NEAREST) {
		//	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGB, GL_UNSIGNED_BYTE, tmp_data);
		//}
		//else {
		//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tmp_data);
		//}
		delete tmp_data;

		IsLoaded = true;

		return true;
}

GLuint CTexture::GetID(void) {
	if (!IsLoaded) {
		return NULL; //Load();
	}
	else
		return _id;
}

int CTexture::GetWidth(void) {
	return width;
}
int CTexture::GetHeight(void) {
	return height;
}

