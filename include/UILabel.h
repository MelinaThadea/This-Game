#include "Arena.h"
#include "Player.h"
#include "GameItem.h"
#include "GameObject.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class UILabel 
{
public:
	UILabel(int xpos, int ypos, std::string text, std::string font, SDL_Color& colour):
		labelText (text), labelFont(font), textColour(colour)
	{
		position.x = xpos;
		position.y = ypos;


	}

	~UILabel()
	{}

	void SetLabelText()
	{
		SDL_Surface* surf = TTF_RenderText_Blended(Arena::asset->, labelText.c_str(), textColour);

	
	}

	void draw() const
	{}




private:
	SDL_Rect position;
	std::string labelText;
	std::string labelFont;
	SDL_Color textColour;
	SDL_Texture* labelTexture;

};