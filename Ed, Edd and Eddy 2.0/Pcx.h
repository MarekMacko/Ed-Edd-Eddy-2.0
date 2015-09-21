#pragma once






// --------------------------------------------
// PCXHEADER - pcx header structure.
// --------------------------------------------
//#pragma pack(1)
//typedef struct tagPCXHEADER
//{
//	unsigned char	manufacturer;		// manufacturer
//	unsigned char	version;			// version
//	unsigned char	encoding;			// encoding type
//	unsigned char	bitsPerPixel;		// number of bits per pixel
//
//	unsigned short	x, y;				// ...
//	unsigned short	width, height;		// dimensions
//	unsigned short	horzRes, vertRes;	// horisontal and vertical screen resolutions
//
//	unsigned char	*palette;			// color palette
//	unsigned char	reserved;			// reserved
//	unsigned char	numColorPlanes;		// number of planes
//
//	unsigned short	bytesPerScanLine;	// byte per line
//	unsigned short	paletteType;		// palette type
//	unsigned short	horzSize, vertSize;	// ...
//
//	unsigned char	padding[54];		// ...
//
//} PCXHEADER, *PPCXHEADER;
//#pragma pack(4)

typedef struct
{
	unsigned char manufacturer;
	unsigned char version;
	unsigned char encoding;
	unsigned char bits;
	unsigned char xMin;
	unsigned char yMin;
	unsigned char xMax;
	unsigned char yMax;
	unsigned char *palette;
} PCXHEADER;

class CPCX
{
public:	
	bool loaded;
	int width, height;
	unsigned char * data;
	unsigned char * palette;
	long int scaledHeight;
	long int scaledWidth;
	//string error;

	CPCX(void);
	CPCX(char *);//
	~CPCX();
	bool CPCX::LoadPCXTexture(char *_file);
	
private:
	void Reset(void);
	unsigned char * LoadPCXFile(const char *filename, PCXHEADER *pcxHeader);
};

