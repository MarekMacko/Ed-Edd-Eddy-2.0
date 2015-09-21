#include "stdafx.h"

CMD2Model::CMD2Model() 
{
	numFrames = 0;		// klatki		
	numVertices = 0;	// wierzcho³ki	
	numTriangles = 0;	// trójk¹ty
	numST = 0;			// wspó³rzêdne tekstury
	frameSize = 0;		// rozmiar klatki
	currentFrame = 0;	// bie¿¹ca klatka
	nextFrame = 1;		// nastêpna klatka
	interpol = 0.0;		// wspó³czynnik interpolacji			
	triIndex = NULL;	// indeksy wspó³rzêdnych tekstury		
	vertexList = NULL;	// lista wierzcho³ków
	modelTex = NULL;	// tekstura
	modelState = STAND;
}

CMD2Model::~CMD2Model() 
{
	Unload();
}

void CMD2Model::SetupSkin(texture_t *thisTexture)
{	
	// konfiguruje teksturê modelu MD2
	glGenTextures(1, &thisTexture->texID);
	glBindTexture(GL_TEXTURE_2D, thisTexture->texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	switch (thisTexture->textureType)
	{
	case BMP:
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, thisTexture->width, 
						  thisTexture->height, GL_RGB, GL_UNSIGNED_BYTE, 
						  thisTexture->data);
		break;

	case PCX:
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, thisTexture->width,
						  thisTexture->height, GL_RGBA, GL_UNSIGNED_BYTE,
						  thisTexture->data);
		break;

	case TGA:
		break;

	default:
		break;
	}
}

int CMD2Model::LoadModel(char *modelFile)
{
	FILE *filePtr;				// wskaŸnik pliku
	int fileLen;				// d³ugoœæ pliku
	char *buffer;				// bufor pliku

	modelHeader_t *modelHeader; // nag³ówek modelu

	stIndex_t *stPtr;			// dane tekstury
	frame_t *frame;				// dane klatki
	vec3 *vertexListPtr;		// zmienna indeksu
	mesh_t *bufIndexPtr;		// zmienna indeksu
	int i, j;					// zmienna indeksu

	// otwiera plik modelu
	filePtr = fopen(modelFile, "rb");
	if (filePtr == NULL)
		return FALSE;

	// ustala d³ugoœæ pliku
	fseek(filePtr, 0, SEEK_END);
	fileLen = ftell(filePtr);
	fseek(filePtr, 0, SEEK_SET);

	// wczytuje ca³y plik bufora
	buffer = new char[fileLen + 1];
	fread(buffer, sizeof(char), fileLen, filePtr);

	// wyodrêbnia nag³ówek
	modelHeader = (modelHeader_t*)buffer;

	vertexList = new vec3[modelHeader->numXYZ * modelHeader->numFrames];

	numVertices = modelHeader->numXYZ;
	numFrames = modelHeader->numFrames;
	frameSize = modelHeader->framesize;

	for (j = 0; j < numFrames; j++)
	{
		frame = (frame_t*)&buffer[modelHeader->offsetFrames + frameSize * j];

		vertexListPtr = (vec3*)&vertexList[numVertices * j];
		for (i = 0; i < numVertices; i++)
		{
			vertexListPtr[i].x = frame->scale[0] * frame->fp[i].v[0] + frame->translate[0];
			vertexListPtr[i].y = frame->scale[1] * frame->fp[i].v[1] + frame->translate[1];
			vertexListPtr[i].z = frame->scale[2] * frame->fp[i].v[2] + frame->translate[2];
		}
	}

	numST = modelHeader->numST;
	st = new texCoord_t[numST];

	stPtr = (stIndex_t*)&buffer[modelHeader->offsetSt];
	for (i = 0; i < numST; i++)
	{
		st[i].s = 0;
		st[i].t = 0;
	}

	numTriangles = modelHeader->numTris;
	triIndex = new mesh_t[numTriangles];

	// tymczasowy wskaŸnik bufora trójk¹tów
	bufIndexPtr = (mesh_t*)&buffer[modelHeader->offsetTris];

	// wype³nia listê trójk¹tów
	for (j = 0; j < numFrames; j++)
	{
		// dla wszystkich trójk¹tów danej klatki
		for (i = 0; i < numTriangles; i++)
		{
			triIndex[i].meshIndex[0] = bufIndexPtr[i].meshIndex[0];
			triIndex[i].meshIndex[1] = bufIndexPtr[i].meshIndex[1];
			triIndex[i].meshIndex[2] = bufIndexPtr[i].meshIndex[2];
			triIndex[i].stIndex[0] = bufIndexPtr[i].stIndex[0];
			triIndex[i].stIndex[1] = bufIndexPtr[i].stIndex[1];
			triIndex[i].stIndex[2] = bufIndexPtr[i].stIndex[2];
		}
	}

	// zamyka plik i zwalnia jego bufor
	fclose(filePtr);
	free(buffer);

	modelTex = NULL;
	currentFrame = 0;
	nextFrame = 1;
	interpol = 0.0;

	return 0;
}

int CMD2Model::Load(char *modelFile, char *skinFile) 
{
	FILE *filePtr;				// wskaŸnik pliku
	int fileLen;				// d³ugoœæ pliku
	char *buffer;				// bufor pliku

	modelHeader_t *modelHeader; // nag³ówek modelu

	stIndex_t *stPtr;			// dane tekstury
	frame_t *frame;				// dane klatki
	vec3 *vertexListPtr;		// zmienna indeksu
	mesh_t *bufIndexPtr;		// zmienna indeksu
	int i, j;					// zmienna indeksu

	// otwiera plik modelu
	filePtr = fopen(modelFile, "rb");
	if (filePtr == NULL)
		return FALSE;

	// ustala d³ugoœæ pliku
	fseek(filePtr, 0, SEEK_END);
	fileLen = ftell(filePtr);
	fseek(filePtr, 0, SEEK_SET);

	// wczytuje ca³y plik bufora
	buffer = new char[fileLen + 1];
	fread(buffer, sizeof(char), fileLen, filePtr);

	// wyodrêbnia nag³ówek
	modelHeader = (modelHeader_t*)buffer;

	vertexList = new vec3[modelHeader->numXYZ * modelHeader->numFrames];

	numVertices = modelHeader->numXYZ;
	numFrames = modelHeader->numFrames;
	frameSize = modelHeader->framesize;
	
	for (j = 0; j < numFrames; j++)
	{
		frame = (frame_t*)&buffer[modelHeader->offsetFrames + frameSize * j];

		vertexListPtr = (vec3*)&vertexList[numVertices * j];
		for (i = 0; i < numVertices; i++)
		{
			vertexListPtr[i].x = frame->scale[0] * frame->fp[i].v[0] + frame->translate[0];
			vertexListPtr[i].y = frame->scale[1] * frame->fp[i].v[1] + frame->translate[1];
			vertexListPtr[i].z = frame->scale[2] * frame->fp[i].v[2] + frame->translate[2];
		}
	}

	tex = new CTexture(skinFile, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	if(!tex->Load())
		return false;
		
	//modelTex = NULL; //LoadTexture(skinFile);
	//if (modelTex != NULL)
	//	SetupSkin(modelTex);
	//else
	//	return FALSE;

	numST = modelHeader->numST;
	st = new texCoord_t[numST];

	stPtr = (stIndex_t*)&buffer[modelHeader->offsetSt];
	for (i = 0; i < numST; i++)
	{
		st[i].s = (float)stPtr[i].s / (float)tex->GetWidth();//(float)modelTex->width;
		st[i].t = (float)stPtr[i].t / (float)tex->GetHeight();//(float)modelTex->height;
	}

	numTriangles = modelHeader->numTris;
	triIndex = new mesh_t[numTriangles];

	// tymczasowy wskaŸnik bufora trójk¹tów
	bufIndexPtr = (mesh_t*)&buffer[modelHeader->offsetTris];

	// wype³nia listê trójk¹tów
	for (j = 0; j < numFrames; j++)
	{
		// dla wszystkich trójk¹tów danej klatki
		for (i = 0; i < numTriangles; i++)
		{
			triIndex[i].meshIndex[0] = bufIndexPtr[i].meshIndex[0];
			triIndex[i].meshIndex[1] = bufIndexPtr[i].meshIndex[1];
			triIndex[i].meshIndex[2] = bufIndexPtr[i].meshIndex[2];
			triIndex[i].stIndex[0] = bufIndexPtr[i].stIndex[0];
			triIndex[i].stIndex[1] = bufIndexPtr[i].stIndex[1];
			triIndex[i].stIndex[2] = bufIndexPtr[i].stIndex[2];
		}
	}

	// zamyka plik i zwalnia jego bufor
	fclose(filePtr);
	free(buffer);

	currentFrame = 0;
	nextFrame = 1;
	interpol = 0.0;

	return TRUE;
}

int CMD2Model::SetTexture(texture_t *texture)
{
	int i;

	if (texture != NULL) {
		free(modelTex);
		modelTex = texture;
	}
	else {
		return -1;
	}

	SetupSkin(modelTex);

	for (i = 0; i < numST; i++)
	{
		st[i].s /= (float)modelTex->width;
		st[i].t /= (float)modelTex->height;
	}

	return 0;
}

void CMD2Model::CalculateNormal(vec3 *p1, vec3 *p2, vec3 *p3)
{
	float a[3], b[3], result[3];
	float length;

	a[0] = p1->x - p2->x;
	a[1] = p1->y - p2->y;
	a[2] = p1->z - p2->z;

	b[0] = p1->x - p3->x;
	b[1] = p1->y - p3->y;
	b[2] = p1->z - p3->z;

	result[0] = a[1] * b[2] - b[1] * a[2];
	result[1] = b[0] * a[2] - a[0] * b[2];
	result[2] = a[0] * b[1] - b[0] * a[1];

	// wyznacza d³ugoœc wektora normalnego
	length = (float)sqrt(result[0] * result[0] + result[1] * result[1] + result[2] * result[2]);

	// i normalizuje go
	glNormal3f(result[0] / length, result[1] / length, result[2] / length);
}

int CMD2Model::Animate(int startFrame, int endFrame, float percent)
{
	vec3 *vList;		// wierzcho³ki bie¿¹cej klatki
	vec3 *nextVList;	// wierzcho³ki nastêpnej klatki
	int i;				// zmienna indeksu
	float x1, y1, z1;	// wspó³rzêdne wierzcholka bie¿¹cej klatki
	float x2, y2, z2;	// wspó³rzêdne wierzcholka nsatêpnej klatki

	vec3 vertex[3];

	if (startFrame > currentFrame)
		currentFrame = startFrame;

	if ((startFrame < 0) || (currentFrame < 0))
		return -1;

	if ((startFrame >= numFrames) || (endFrame >= numFrames))
		return -1;

	if (interpol >= 1.0)
	{
		interpol = 0.0f;
		currentFrame++;
		if (currentFrame >= endFrame)
			currentFrame = startFrame;
		
		nextFrame = currentFrame + 1;

		if (nextFrame >= endFrame)
			nextFrame = startFrame;
	}

	vList = &vertexList[numVertices*currentFrame];
	nextVList = &vertexList[numVertices*nextFrame];

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex->GetID());
	glBegin(GL_TRIANGLES);
		for (i = 0; i < numTriangles; i++)
		{
			// wspó³rzêdne pierwszego wierzcho³ka trójkata w obu kluczowych klatkach
			x1 = vList[triIndex[i].meshIndex[0]].x;
			y1 = vList[triIndex[i].meshIndex[0]].y;
			z1 = vList[triIndex[i].meshIndex[0]].z;
			x2 = nextVList[triIndex[i].meshIndex[0]].x;
			y2 = nextVList[triIndex[i].meshIndex[0]].y;
			z2 = nextVList[triIndex[i].meshIndex[0]].z;

			// interpolowane wspó³rzêdne pierwszego wierzcho³ka
			vertex[0].x = x1 + interpol * (x2 - x1);
			vertex[0].y = y1 + interpol * (y2 - y1);
			vertex[0].z = z1 + interpol * (z2 - z1);

			// wspó³rzêdne drugiego wierzcho³ka trójkata
			x1 = vList[triIndex[i].meshIndex[2]].x;
			y1 = vList[triIndex[i].meshIndex[2]].y;
			z1 = vList[triIndex[i].meshIndex[2]].z;
			x2 = nextVList[triIndex[i].meshIndex[2]].x;
			y2 = nextVList[triIndex[i].meshIndex[2]].y;
			z2 = nextVList[triIndex[i].meshIndex[2]].z;

			// interpolowane wspó³rzêdne drugiego wierzcho³ka
			vertex[2].x = x1 + interpol * (x2 - x1);
			vertex[2].y = y1 + interpol * (y2 - y1);
			vertex[2].z = z1 + interpol * (z2 - z1);

			// wspó³rzêdne trzeciego wierzcho³ka trójkata
			x1 = vList[triIndex[i].meshIndex[1]].x;
			y1 = vList[triIndex[i].meshIndex[1]].y;
			z1 = vList[triIndex[i].meshIndex[1]].z;
			x2 = nextVList[triIndex[i].meshIndex[1]].x;
			y2 = nextVList[triIndex[i].meshIndex[1]].y;
			z2 = nextVList[triIndex[i].meshIndex[1]].z;

			// interpolowane wspó³rzêdne trzeciego wierzcho³ka
			vertex[1].x = x1 + interpol * (x2 - x1);
			vertex[1].y = y1 + interpol * (y2 - y1);
			vertex[1].z = z1 + interpol * (z2 - z1);

			// wektor normalny do trójk¹ta
			CalculateNormal(&vertex[0], &vertex[2], &vertex[1]);

			// rysuje trójk¹t pokryty tekstur¹
			glTexCoord2f(st[triIndex[i].stIndex[0]].s, st[triIndex[i].stIndex[0]].t);			
			glVertex3fv((const GLfloat*)&vertex[0]);

			glTexCoord2f(st[triIndex[i].stIndex[2]].s, st[triIndex[i].stIndex[2]].t);
			glVertex3fv((const GLfloat*)&vertex[2]);

			glTexCoord2f(st[triIndex[i].stIndex[1]].s, st[triIndex[i].stIndex[1]].t);
			glVertex3fv((const GLfloat*)&vertex[1]);
		}
		glEnd();
		glDisable(GL_TEXTURE_2D);
		interpol += percent; // zwiêksza wpsó³czynnik interpolacji
		
		return 0;
}

int CMD2Model::RenderFrame(int keyFrame)
{
	vec3 *vList;
	int i;

	// wskaŸnik wyœwietlanej klatki
	vList = &vertexList[numVertices * keyFrame];

	// wybiera teksturê
	glBindTexture(GL_TEXTURE_2D, tex->GetID());

	// wyœwietla klatkê modelu
	glBegin(GL_TRIANGLES);
		for (i = 0; i < numTriangles; i++)
		{
			CalculateNormal(&vList[triIndex[i].meshIndex[0]],
							&vList[triIndex[i].meshIndex[2]],
							&vList[triIndex[i].meshIndex[1]]);

			glTexCoord2f(st[triIndex[i].stIndex[0]].s, 
						 st[triIndex[i].stIndex[0]].t);
			glVertex3fv((const GLfloat*)&vList[triIndex[i].meshIndex[0]]);

			glTexCoord2f(st[triIndex[i].stIndex[2]].s,
						 st[triIndex[i].stIndex[2]].t);
			glVertex3fv((const GLfloat*)&vList[triIndex[i].meshIndex[2]]);

			glTexCoord2f(st[triIndex[i].stIndex[1]].s,
						 st[triIndex[i].stIndex[1]].t);
			glVertex3fv((const GLfloat*)&vList[triIndex[i].meshIndex[1]]);
		}
	glEnd();

	return 0;
}

int CMD2Model::Unload()
{
	if (triIndex != NULL)
		free(triIndex);
	if (vertexList != NULL)
		free(vertexList);
	if (st != NULL)
		free(st);

	return 0;
}

void CMD2Model::SetState(modelState_t state) {
	modelState = state;
}

modelState_t CMD2Model::GetState(void) {
	return modelState;
}



anim_t CMD2Model::animlist[21] =
{
	// first, last, fps

	{ 0,  39,  9 },		// STAND
	{ 40,  45, 10 },	// RUN
	{ 46,  53, 10 },	// ATTACK
	{ 54,  57,  7 },	// PAIN_A
	{ 58,  61,  7 },	// PAIN_B
	{ 62,  65,  7 },	// PAIN_C
	{ 66,  71,  7 },	// JUMP
	{ 72,  83,  7 },	// FLIP
	{ 84,  94,  7 },	// SALUTE
	{ 95, 111, 10 },	// FALLBACK
	{ 112, 122,  7 },	// WAVE
	{ 123, 134,  6 },	// POINT
	{ 135, 153, 10 },	// CROUCH_STAND
	{ 154, 159,  7 },	// CROUCH_WALK
	{ 160, 168, 10 },	// CROUCH_ATTACK
	{ 196, 172,  7 },	// CROUCH_PAIN
	{ 173, 177,  5 },	// CROUCH_DEATH
	{ 178, 183,  7 },	// DEATH_FALLBACK
	{ 184, 189,  7 },	// DEATH_FALLFORWARD
	{ 190, 197,  7 },	// DEATH_FALLBACKSLOW
	{ 198, 198,  5 },	// BOOM
};
