#pragma once

// Scena - Jest to podstawowy element organizuj¹cy hierarchiê obiektów w grze.
// Z za³o¿enia, w danym momencie powinna istnieæ tylko jedna scena.
// W sytuacji gdy scen mo¿e byæ wiêcej, dobrze jest utworzyæ klasy dziedzicz¹ce po tej.
class CScene
{
public:

	CScene();
	~CScene();
	void Initialize(void);
	void Update(void);
	void Render(void);

private:

};

