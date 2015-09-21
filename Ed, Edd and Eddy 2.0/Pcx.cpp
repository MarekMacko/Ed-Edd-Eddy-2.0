//
//	pcx.cpp - source file / freeware
//
//	David Henry - tfc_duke@hotmail.com
//

#include "stdafx.h"
//#include	<fstream>
//#include	"pcx.h"


CPCX::CPCX()
{
	Reset();
}

CPCX::CPCX(char * _file)
{
	Reset();
//	LoadPCX(_file);
}

CPCX::~CPCX()
{
	if (data) {
		delete[] data;
	}
}

//bool CPCX::LoadPCX(const char *filename)
//{
//	bool flipvert = false;
//	std::ifstream		file;			// file stream
//	PCXHEADER			*header;		// header PCX
//	unsigned char		*uncompData;	// uncompressed paletted image data
//	unsigned char		*ptr;			// pointer to pixels data
//	unsigned char		c;				// temporary variable
//	char				*buffer;		// buffer storing the entire file
//	int					idx = 0;		// temporary variable
//	int					numRepeat;		// temporary variable
//	int					i, j;			// temporary variables
//
//	file.open(filename, std::ios::in | std::ios::binary);
//
//	if (file.fail())
//		return false;
//	
//	file.seekg(0, std::ios::end);
//	long flen = file.tellg();
//	file.seekg(0, std::ios::beg);
//
//	buffer = new char[flen + 1];
//	file.read(buffer, flen);
//	char *pBuff = buffer;
//
//	file.close();
//
//	header = (PCXHEADER *)pBuff;
//
//	if ((header->manufacturer != 10) ||
//		(header->version != 5) ||
//		(header->encoding != 1) ||
//		(header->bitsPerPixel != 8))
//	{
//		return false;
//	}
//
//
//	header->width = header->width - header->x + 1;
//	header->height = header->height - header->y + 1;
//
//
//	 allocate memory for image data
//	uncompData = new unsigned char[header->width * header->height];
//
//	pBuff = (char *)&buffer[128];
//
//	 uncode compressed image (RLE)
//	while (idx < (header->width * header->height))
//	{
//		if ((c = *(pBuff++)) > 0xbf)
//		{
//			numRepeat = 0x3f & c;
//			c = *(pBuff++);
//
//			for (i = 0; i < numRepeat; i++)
//				uncompData[idx++] = c;
//		}
//		else
//			uncompData[idx++] = c;
//	}
//
//
//	 the palette is located at the 769th last byte of the file
//	pBuff = &buffer[flen - 769];
//
//	 verify the palette; first char must be equal to 12
//	if (*(pBuff++) != 12)
//	{
//		delete[] buffer;
//		delete[] uncompData;
//		return false;
//	}
//
//	 read the palette
//	header->palette = (unsigned char *)pBuff;
//
//	 allocate memory for 32 bits pixel data
//	data = new unsigned char[header->width * header->height * 4];
//
//	ptr = &(data)[0];
//
//	 convert from paletted to 32 bits rgba pixels
//	for (j = header->height - 1; j > 0; j--)
//	{
//		if (flipvert)
//			ptr = &(data)[j * header->width * 4];
//
//		for (i = 0; i < header->width; i++, ptr += 4)
//		{
//			int color = 3 * uncompData[j * header->width + i];
//
//			ptr[0] = (unsigned char)header->palette[color + 0];
//			ptr[1] = (unsigned char)header->palette[color + 1];
//			ptr[2] = (unsigned char)header->palette[color + 2];
//			ptr[3] = (unsigned char)255;
//		}
//	}
//
//	 free memory
//	delete[] uncompData;
//	delete[] buffer;
//	
//	 return success
//	return true;
//}

void CPCX::Reset(void) {
	data = 0;
	loaded = false;
//	error = "";
}

unsigned char * CPCX::LoadPCXFile(const char *_file, PCXHEADER * pcxHeader)
{
	int idx = 0;		// licznik indeksu
	int c;				// pobiera znak z pliku
	int i;				// licznik indeksu
	int numRepeat;
	FILE *filePtr;		// wskaŸnik pliku
	//int width;			// szrerokoœæ obrazka PCX
	//int height;			// wysokoœæ obrazka PCX
	unsigned char * pixelData;	 // dane obrazka PCX
	unsigned char * paletteData; // dane paley PCX
	
	// otwiera plik PCX
	filePtr = fopen(_file, "rb");
	if (!filePtr)
		return NULL;

	// pobiera pierwszy znak z pliku, który powinien mieæ wartoœæ 10
	c = getc(filePtr);
	if (c != 10) {
		fclose(filePtr);
		return NULL;
	}

	// pobiera nastêpny znak, który powinien mieæ wartoœæ 5
	c = getc(filePtr);
	if (c != 5 ){
		fclose(filePtr);
		return NULL;
	}

	// ustawia wskaŸnik pliku na jego pocz¹tek
	rewind(filePtr);

	// pomija pierwsze 4 znaki
	fgetc(filePtr);
	fgetc(filePtr);
	fgetc(filePtr);
	fgetc(filePtr);

	// pobiera wspó³rzêdn¹ x lewej krawêdzi obrazka PCX
	pcxHeader->xMin = fgetc(filePtr);		// mniej znacz¹ce s³owo
	pcxHeader->xMin |= fgetc(filePtr) << 8; // bardziej znacz¹ce s³owo

	// pobiera wspó³rzêdn¹ y dolnej krawêdzi obrazka PCX
	pcxHeader->yMin = fgetc(filePtr);		// mniej znacz¹ce s³owo
	pcxHeader->yMin |= fgetc(filePtr) << 8; // bardziej znacz¹ce s³owo

	// pobiera wspó³rzêdn¹ x prawej krawêdzi obrazka PCX
	pcxHeader->xMax = fgetc(filePtr);		// mniej znacz¹ce s³owo
	pcxHeader->xMax |= fgetc(filePtr) << 8; // bardziej znacz¹ce s³owo

	// pobiera wspó³rzêdn¹ y górnej krawêdzi obrazka PCX
	pcxHeader->yMax = fgetc(filePtr);		// mniej znacz¹ce s³owo
	pcxHeader->yMax |= fgetc(filePtr) << 8; // bardziej znacz¹ce s³owo

	// oblicza szerkoœæ i wysokoœæ obrazka PCX
	width = pcxHeader->xMax - pcxHeader->xMin + 1;
	height = pcxHeader->yMax - pcxHeader->yMin + 1;

	// przydziela pamiêc na dane obrazka PCX
	pixelData = (unsigned char *)malloc(width*height);

	// ustawia wskaŸnik pliku na 128 bajt, gdzie zaczynaj¹ siê dane obrazka
	fseek(filePtr, 128, SEEK_SET);

	// dekoduje i przechowuje piksele obrazka
	while (idx < (width*height))
	{
		c = getc(filePtr);
		if (c > 0xbf)
		{
			numRepeat = 0x3f & c;
			c = getc(filePtr);

			for (i = 0; i < numRepeat; i++)
			{
				pixelData[idx++] = c;
			}
		}
		else 
			pixelData[idx++] = c;

		fflush(stdout);
	}

	// przydziela pamiêæ na paletê obrazka PCX
	paletteData = (unsigned char *)malloc(768);

	// paleta zajmuje 769 koñcowych bajtów pliku PCX
	fseek(filePtr, -769, SEEK_END);

	// weryfikuje paletê, pierwszy znak powinien mieæ wartoœæ 12
	c = getc(filePtr);
	if (c != 12)
	{
		fclose(filePtr);
		return NULL;
	}

	// wczytuje paletê
	for (i = 0; i < 768; i++) {
		c = getc(filePtr);
		paletteData[i] = c;
	}

	// zamyka plik i umieszcza wskaŸnik palety w nag³ówku
	fclose(filePtr);
	pcxHeader->palette = paletteData;

	// zwraca wskaŸnik do danych obrazka 
	return pixelData;
}

bool CPCX::LoadPCXTexture(char *_file)
{
	PCXHEADER texInfo;
	unsigned char * unscaledData;
	int i;
	int j;

	data = LoadPCXFile(_file, &texInfo);
	if (!data)
		return false;

	palette = texInfo.palette;
	
	unscaledData = (unsigned char *)malloc(width*height * 4);

	for (j = 0; j < height; j++)
	{
		for (i = 0; i < width; i++)
		{
			unscaledData[4 * (j*width + i) + 0] = (unsigned char)palette[3 * data[j*width + i] + 0];
			unscaledData[4 * (j*width + i) + 1] = (unsigned char)palette[3 * data[j*width + i] + 1];
			unscaledData[4 * (j*width + i) + 2] = (unsigned char)palette[3 * data[j*width + i] + 2];
			unscaledData[4 * (j*width + i) + 3] = (unsigned char)255;
		}
	}

	int tmpWidth = width;
	int tmpHeight = height;

	i = 0;
	while (tmpWidth) {
		tmpWidth /= 2;
		i++;
	}
	scaledWidth = (long)pow(2.0, i - 1);

	i = 0;
	while (tmpHeight) {
		tmpHeight /= 2;
		i++;
	}
	scaledHeight = (long)pow(2.0, i - 1);

	free(data);
	data = NULL;

	data = (unsigned char *)malloc(scaledWidth*scaledHeight * 4);

	gluScaleImage(GL_RGBA, width, height, GL_UNSIGNED_BYTE, unscaledData, scaledWidth, scaledHeight, GL_UNSIGNED_BYTE, data);

	return true;
}