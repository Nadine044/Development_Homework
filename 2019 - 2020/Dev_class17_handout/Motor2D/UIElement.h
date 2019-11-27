#ifndef _UI_ELEMENT_H_
#define _UI_ELEMENT_H_

#include "j1Gui.h"
#include "j1Module.h"
#include "SDL/include/SDL_rect.h"
#include "SDL\include\SDL.h"

class UIObject
{
public:
	UIObject();
	~UIObject();

	virtual bool PreUpdate();
	virtual bool Update(float dt);
	virtual bool PostUpdate();
	virtual bool CleanUp();

public:
	SDL_Rect		rect;
	SDL_Texture*	tex = nullptr;

	UIObjectTYPE	type;
};





#endif // !_UIELEMENT_H_
