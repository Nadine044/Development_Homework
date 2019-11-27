#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "UIElement.h"
#include "j1Gui.h"
#include "SDL/include/SDL_rect.h"
#include "SDL\include\SDL.h"

class Button : public UIObject
{
public:
	Button();
	~Button();

	bool PreUpdate() override;
	bool Update(float dt) override;
	bool PostUpdate() override;
	bool CleanUp() override;

public:
	SDL_Rect		rect;
	SDL_Texture*	text = nullptr;

	UIObjectTYPE	type;

};



#endif // !_BUTTON_H_
