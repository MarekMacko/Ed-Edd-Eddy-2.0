
// nag��wek 
typedef struct
{
	int		ident;				// "IPD2" oznacza format MD2
	int		version;			// obecnie wersja 8
	int		skinwidth;			// szeroko�� textury
	int		skinheight;			// wysoko�� of the textury
	int		framesize;			// rozmiar klatki (w bajtach)
	int		numSkins;			// liczba tekstur
	int		numXYZ;				// liczba punkt�w
	int		numST;				// liczba wsp�rz�dnych tekstury
	int		numTris;			// liczba tr�jk�t�w
	int		numGLcmds;			// liczba komend OpenGL
	int		numFrames;			// ca�kowita liczba klatek
	int		offsetSkins;		// po�o�enie (w pliku) nazw tekstur (ka�da po 64 bajty)
	int		offsetSt;			// po�o�enie (w pliku) wsp�rzednych tekstury
	int		offsetTris;			// po�o�enie (w pliku) siatki tr�jk�t�w
	int		offsetFrames;		// po�o�enie (w pliku) danych klatki (punkt�w)
	int		offsetGLcmds;		// typ u�ywanych polece� OpenGL
	int		offsetEnd;			// koniec pliku
} modelHeader_t;

// wsp�rz�dna tekstury
typedef struct {
	float s;	// wsp�rz�dna s
	float t;	// wsp�rz�dna t
} texCoord_t;

// indeks wsp�rz�dnej tekstury
typedef struct {
	short s;
	short t;
} stIndex_t;

// pojedynczy punkt klatki animacji
typedef struct {
	unsigned char v[3];			// informacja o punkcie
	unsigned char normalIndex;  // pole to nie b�dzie u�ywane
} framePoint_t;

// informacja o pojedynczej klatce animacji
typedef struct {
	float scale[3];		// skalowanie wierzcho�k�w klatki
	float translate[3];	// przesuni�cie wierzcho�k�w klatki
	char name[16];		// nazwa modelu
	framePoint_t fp[1]; // pocz�tek listy wierzcho�k�w klatki
} frame_t;

// dane opisuj�ce pojedynczy tr�jk�t
typedef struct {
	unsigned short meshIndex[3]; // indeksy wierzcho�k�w
	unsigned short stIndex[3];	 // indeksy wsp�rz�dnych tekstury
} mesh_t;

enum texTypes_t {
	PCX,
	BMP,
	TGA
};

typedef struct {

	texTypes_t textureType; // typ pliku tekstury

	int width;				// szerko�� tekstury
	int height;				// wysoko�� tekstury
	long int scaledWidth;
	long int scaledHeight;

	unsigned int texID;		// identyfikator obiektu tekstury
	unsigned char *data;	// dane tekstury
	unsigned char *palette;	// paleta tekstury (je�li istnieje)
} texture_t;

typedef struct
{
	int		first_frame;			// pierwsza klatka animacji
	int		last_frame;				// ostatnia klatka animacji
	int		fps;					// ilo�� klatek na sekund�

} anim_t;

// animation list
typedef enum {
	STAND,
	RUN,
	ATTACK,
	PAIN_A,
	PAIN_B,
	PAIN_C,
	JUMP,
	FLIP,
	SALUTE,
	FALLBACK,
	WAVE,
	POINTX,
	CROUCH_STAND,
	CROUCH_WALK,
	CROUCH_ATTACK,
	CROUCH_PAIN,
	CROUCH_DEATH,
	DEATH_FALLBACK,
	DEATH_FALLFORWARD,
	DEATH_FALLBACKSLOW,
	BOOM,

	MAX_ANIMATIONS

} modelState_t;