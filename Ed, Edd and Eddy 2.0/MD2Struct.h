
// nag³ówek 
typedef struct
{
	int		ident;				// "IPD2" oznacza format MD2
	int		version;			// obecnie wersja 8
	int		skinwidth;			// szerokoœæ textury
	int		skinheight;			// wysokoœæ of the textury
	int		framesize;			// rozmiar klatki (w bajtach)
	int		numSkins;			// liczba tekstur
	int		numXYZ;				// liczba punktów
	int		numST;				// liczba wspó³rzêdnych tekstury
	int		numTris;			// liczba trójk¹tów
	int		numGLcmds;			// liczba komend OpenGL
	int		numFrames;			// ca³kowita liczba klatek
	int		offsetSkins;		// po³o¿enie (w pliku) nazw tekstur (ka¿da po 64 bajty)
	int		offsetSt;			// po³o¿enie (w pliku) wspó³rzednych tekstury
	int		offsetTris;			// po³o¿enie (w pliku) siatki trójk¹tów
	int		offsetFrames;		// po³o¿enie (w pliku) danych klatki (punktów)
	int		offsetGLcmds;		// typ u¿ywanych poleceñ OpenGL
	int		offsetEnd;			// koniec pliku
} modelHeader_t;

// wspó³rzêdna tekstury
typedef struct {
	float s;	// wspó³rzêdna s
	float t;	// wspó³rzêdna t
} texCoord_t;

// indeks wspó³rzêdnej tekstury
typedef struct {
	short s;
	short t;
} stIndex_t;

// pojedynczy punkt klatki animacji
typedef struct {
	unsigned char v[3];			// informacja o punkcie
	unsigned char normalIndex;  // pole to nie bêdzie u¿ywane
} framePoint_t;

// informacja o pojedynczej klatce animacji
typedef struct {
	float scale[3];		// skalowanie wierzcho³ków klatki
	float translate[3];	// przesuniêcie wierzcho³ków klatki
	char name[16];		// nazwa modelu
	framePoint_t fp[1]; // pocz¹tek listy wierzcho³ków klatki
} frame_t;

// dane opisuj¹ce pojedynczy trójk¹t
typedef struct {
	unsigned short meshIndex[3]; // indeksy wierzcho³ków
	unsigned short stIndex[3];	 // indeksy wspó³rzêdnych tekstury
} mesh_t;

enum texTypes_t {
	PCX,
	BMP,
	TGA
};

typedef struct {

	texTypes_t textureType; // typ pliku tekstury

	int width;				// szerkoœæ tekstury
	int height;				// wysokoœæ tekstury
	long int scaledWidth;
	long int scaledHeight;

	unsigned int texID;		// identyfikator obiektu tekstury
	unsigned char *data;	// dane tekstury
	unsigned char *palette;	// paleta tekstury (jeœli istnieje)
} texture_t;

typedef struct
{
	int		first_frame;			// pierwsza klatka animacji
	int		last_frame;				// ostatnia klatka animacji
	int		fps;					// iloœæ klatek na sekundê

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