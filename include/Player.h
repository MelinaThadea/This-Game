#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"

#include <ngl/Transformation.h>

class Player : public GameObject
{
public:
	Player(const Vec2 & _p, unsigned int _w, unsigned int _h);
	virtual void update(float _dt) override;
	virtual void draw() const override;
	virtual void moveEvent(const Vec2& _m) override;
	Vec2 getPos() const { return m_pos; }
	Vec2 getDir() const { return m_dir; }

	
	void setPos(const Vec2 &_p) { m_pos = _p; }

	int rY;


	
	

private:
	Vec2 m_pos; // position of player
	Vec2 m_dir; // direction player go
	
	

	unsigned int m_width;
	unsigned int m_height;
};

#endif // PLAYER_H_
