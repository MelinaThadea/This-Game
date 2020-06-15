#ifndef ARENA_H_
#define ARENA_H_

#include "GameItem.h"
#include <vector>
#include <string>
#include <unordered_map>
//#include <SDL_ttf.h>


class Arena
{
public:
	Arena() = default; 
	~Arena() = default;
	Arena(unsigned int _w, unsigned int _h);
	Arena(const std::string& _filename, const std::string& _filename2);

	void draw() const;
	void update(float _dt);
	void keyEvent(int _x, int _y);
	void setItem(unsigned int _x, unsigned int _y, ItemType _type, GameObject * _obj = nullptr);
	int chaPosX = 4;
	int chaPosY = 4;
	static GameItem* asset;

	//void AddFont(std::string id, std::string path, int fontSize);
	//TTF_Font* GetFont(std::string id);

private :
	void createDefaultObjects();
	void drawWall(unsigned int _x, unsigned int _y) const;
	void drawFruit(unsigned int _x, unsigned int _y) const;
	unsigned int m_width=0;
	unsigned int m_height=0;

	//void endGame();

	std::vector<GameItem> m_items;
	std::vector<GameItem> m_items2;

	std::unordered_map<std::string, GameObject *> m_objects;

	//std::unordered_map<std::string, TTF_Font*>fonts;

};


#endif // ARENA_H_
