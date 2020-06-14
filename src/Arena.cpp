#include "Arena.h"
#include <iostream>
#include <ngl/Image.h>
#include <ngl/Transformation.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include "RenderGlobals.h"
#include "Player.h"

#include "SDL.h"


//#include "ngl/Text.h"


const static char* Player1 = "Player1";
const static char* Fruit1 = "Fruit1";
const static char* Wall = "Wall";
const static char* Empty = "Empty";
int score = 0;
int level = 1;


Arena::Arena(unsigned int _w, unsigned int _h)
{
	m_width = _w;
	m_height = _h;
	m_items.resize(m_width*m_height);
	m_items2.resize(m_width*m_height);
	createDefaultObjects();
}


Arena::Arena(const std::string& _filename, const std::string& _filename2)
{
	ngl::Image img(_filename); //for Wall
	m_width = img.width();
	m_height = img.height();
	m_items.resize(m_width*m_height);
	createDefaultObjects();
	for (unsigned int y = 0; y < m_height; ++y)
	{
		for (unsigned int x = 0; x < m_width; ++x)
		{
			if (img.getColour(x, y) == ngl::Vec4::zero())
			{
				setItem(x, y, ItemType::Wall,m_objects[Wall]);
			}
			else
			{
				setItem(x, y, ItemType::Empty, m_objects[Empty]);
			}
		}
	}

	ngl::Image img2(_filename2); //for Fruit
	m_width = img2.width();
	m_height = img2.height();
	m_items2.resize(m_width*m_height);

	for (unsigned int y = 0; y < m_height; ++y)
	{
		for (unsigned int x = 0; x < m_width; ++x)
		{
			if (img2.getColour(x, y) == ngl::Vec4::zero())
			{
				setItem(x, y, ItemType::Fruit, m_objects[Fruit1]);
			}
		}
	}

	ngl::VAOPrimitives::instance()->createTrianglePlane("floor", m_width, m_height, 1.0f, 1.0f, ngl::Vec3::up());

}


void Arena::createDefaultObjects()
{
	m_objects[Wall] = new GameObject();
	m_objects[Empty] = new GameObject();
	m_objects[Fruit1] = new GameObject();
	m_objects[Player1] = new Player(Vec2(chaPosX, chaPosY), m_width, m_height); // set Player Position
}

void Arena::keyEvent(int _x, int _y)
{
	std::cout << _x << ' ' << _y << '\n';
	//if (_x > 0) 
	//{
	//	std::cout << "xPositive";
	//	//tx.rotate(0, 90, 0);
	//}
	//	
	//if (_x < 0)
	//	std::cout << "xNegative";
	m_objects[Player1]->moveEvent(Vec2(_x, _y));
}

void Arena::draw() const
{
	auto shader = ngl::ShaderLib::instance();
	shader->use(ngl::nglDiffuseShader);

#ifdef WIN32
	system("cls");
#else
	system("clear");
#endif // _WIN32_

	//shader->setUniform("Colour", 1.0f, 1.0f, 0.0f, 0.0f); //wall & fruit colours

	size_t index = 0;
	for (size_t y = 0; y < m_height; ++y)
	{
		for (size_t x = 0; x < m_width; ++x)
		{
			if (m_items[index].type == ItemType::Empty) {
				std::cout << ' ';
			}
			else if (m_items[index].type == ItemType::Player) {
				std::cout << 'P';
			}
			else if (m_items[index].type == ItemType::Fruit) {
				std::cout << 'F';
				drawFruit(x, y);
			}
			else if (m_items[index].type == ItemType::Wall) {
				std::cout << 'W';
				drawWall(x, y);
			}
			index++;
		}
		std::cout << '\n';
	}

	for (auto& o : m_objects)
	{
		o.second->draw();
	}
	shader->use(ngl::nglCheckerShader);
	ngl::Transformation tx;
	tx.setPosition(0.0f, -0.6f, 0.0f);
	shader->setUniform("MVP", RenderGlobals::getVPMatrix() * tx.getMatrix());
	ngl::VAOPrimitives::instance()->draw("floor");
}

void Arena::update(float _dt)
	{
		std::cout <<"update \n";
		std::cout << score;
		std::cout << " score \n";

		for (auto &o : m_objects)
		{
			o.second->update(_dt);
		}

		Player* p = static_cast<Player *>(m_objects[Player1]);
		auto pos = p->getPos();
		auto dir = p->getDir();
		Vec2 newPos = pos;


		auto getItem = [=](unsigned int _x, unsigned int _y)
		{
			size_t index = _y * m_width + _x;
			return m_items[index].type;
		};

		if (dir.x != 0 && dir.x < 2) // ROTATE PERSON TO WHEN CLICK LEFT BUTTON
		{
			std::cout << dir.x << "L dirX \n";
			p->rY = 90;
		}

		if (dir.x != 0 && dir.x > 2) // ROTATE PERSON TO WHEN CLICK RIGHT BUTTON
		{
			std::cout << dir.x << "R dirX \n";
			p->rY = -90;
		}

		if (dir.y != 0 && dir.y > 2)
		{
			std::cout << dir.x << "BACK dirY \n"; // ROTATE PERSON TO WHEN CLICK BOTTOM BUTTON
			p->rY = 180;
		}

		if (dir.y != 0 && dir.y < 2)
		{
			std::cout << dir.x << "GO dirY \n"; // ROTATE PERSON TO WHEN CLICK UP BUTTON
			p->rY = 0;
		}

		

		if (dir.x != 0 && getItem(pos.x + dir.x, pos.y + dir.y) == ItemType::Fruit) // FRUIT GONE WHEN HIT X
		{
			score++;
			std::cout << " score \n";
			std::cout << "colliding X \n";

			for (unsigned int y = 0; y < m_height; ++y)
			{
				for (unsigned int x = 0; x < m_width; ++x)
				{
					if (dir.x < 2)
					{
						setItem(pos.x + 1, pos.y, ItemType::Empty, m_objects[Fruit1]);
					}
					if (dir.x > 2)
					{
						setItem(pos.x - 1, pos.y, ItemType::Empty, m_objects[Fruit1]);
					}

				}
			}

			
		}

		if (dir.y != 0 && getItem(pos.x + dir.x, pos.y + dir.y) == ItemType::Fruit) // FRUIT GONE WHEN HIT Y
		{
			score++;
			std::cout << " score \n";
			std::cout << " colliding Y \n";
		
			//setItem(15,10, ItemType::Empty, m_objects[Fruit1]);
			for (unsigned int y = 0; y < m_height; ++y)
			{
				for (unsigned int x = 0; x < m_width; ++x)
				{
					if (dir.y < 2)
					{
						setItem(pos.x, pos.y + 1, ItemType::Empty, m_objects[Fruit1]);
					}
					if (dir.y > 2)
					{
						setItem(pos.x, pos.y - 1, ItemType::Empty, m_objects[Fruit1]);
					}
				}
			}


		}

		if (dir.x != 0 && getItem(pos.x + dir.x, pos.y + dir.y) == ItemType::Empty)
		{
			newPos.x = pos.x + dir.x;
		}

		if (dir.y != 0 && getItem(pos.x + dir.x, pos.y + dir.y) == ItemType::Empty)
		{
			newPos.y = pos.y + dir.y;
		}

		if (dir.x != 0 && getItem(pos.x + dir.x, pos.y + dir.y) == ItemType::Wall)
		{
			std::cout << "HIT WALL X \n";
			
		}

		if (dir.y != 0 && getItem(pos.x + dir.x, pos.y + dir.y) == ItemType::Wall)
		{
			std::cout << "HIT WALL Y \n";
			
		}


		p->setPos(newPos);

		setItem(pos.x, pos.y, ItemType::Empty, m_objects[Empty]);

		setItem(newPos.x, newPos.y, ItemType::Player, m_objects[Player1]);

		
		//RESETING PLAYER POS - WIP
		/*if (score > 1)
		{
			std::cout << "NEXT LEVEL 2 \n";
			setItem(4, 4, ItemType::Player, m_objects[Player1]);
			p->setPos(Vec2(chaPosX, chaPosY));

			for (auto &o : m_objects)
			{
				o.second->update(_dt);
			}

			Player* p = static_cast<Player *>(m_objects[Player1]);
			auto pos = p->getPos();
			auto dir = p->getDir();
			Vec2 newPos = pos;

			auto getItem = [=](unsigned int _x, unsigned int _y)
			{
				size_t index = _y * m_width + _x;
				return m_items[index].type;
			};

			p->setPos(newPos);
			setItem(pos.x, pos.y, ItemType::Empty, m_objects[Empty]);
			setItem(newPos.x, newPos.y, ItemType::Player, m_objects[Player1]);
		}*/
		
		

		

		if (score==2)
		{
			std::cout << "test ";
			int maps = rand()%2;
			switch (maps)
			{
			case 0:
				std::cout << "1 \n";
				break;
			case 1:
				std::cout << "2 \n";
				break;
			default:
				std::cout << "default";
				break;
			}
			return;
		}


		//LEVEL 2
		if (score == 8)
		{	
			ngl::Image img("maps/map2.png"); //for Wall
			m_width = img.width();
			m_height = img.height();
			m_items.resize(m_width*m_height);
			//createDefaultObjects();
			for (unsigned int y = 0; y < m_height; ++y)
			{
				for (unsigned int x = 0; x < m_width; ++x)
				{
					if (img.getColour(x, y) == ngl::Vec4::zero())
					{
						setItem(x, y, ItemType::Wall, m_objects[Wall]);
					}
					else
					{
						setItem(x, y, ItemType::Empty, m_objects[Empty]);
					}
				}
			}

			ngl::Image img2("maps/fruit2.png"); //for Fruit
			m_width = img2.width();
			m_height = img2.height();
			m_items2.resize(m_width*m_height);
			for (unsigned int y = 0; y < m_height; ++y)
			{
				for (unsigned int x = 0; x < m_width; ++x)
				{
					if (img2.getColour(x, y) == ngl::Vec4::zero())
					{
						setItem(x, y, ItemType::Fruit, m_objects[Fruit1]);
					}
				}
			}
		}

		//LEVEL 3
		if (score == 13)
		{
			level++;
			std::cout << "LEVEL" << level << "\n";
			ngl::Image img("maps/map3.png"); //for Wall
			m_width = img.width();
			m_height = img.height();
			m_items.resize(m_width*m_height);
			//createDefaultObjects();
			for (unsigned int y = 0; y < m_height; ++y)
			{
				for (unsigned int x = 0; x < m_width; ++x)
				{
					if (img.getColour(x, y) == ngl::Vec4::zero())
					{
						setItem(x, y, ItemType::Wall, m_objects[Wall]);
					}
					else
					{
						setItem(x, y, ItemType::Empty, m_objects[Empty]);
					}
				}
			}

			ngl::Image img2("maps/fruit3.png"); //for Fruit
			m_width = img2.width();
			m_height = img2.height();
			m_items2.resize(m_width*m_height);
			for (unsigned int y = 0; y < m_height; ++y)
			{
				for (unsigned int x = 0; x < m_width; ++x)
				{
					if (img2.getColour(x, y) == ngl::Vec4::zero())
					{
						setItem(x, y, ItemType::Fruit, m_objects[Fruit1]);
					}
				}
			}
			
		}
			

	}

void Arena::setItem(unsigned int _x, unsigned int _y, ItemType _type, GameObject * _obj)
{
	size_t index = _y * m_width + _x;
	m_items[index].type = _type;
	m_items[index].obj = _obj;
}

void Arena::drawFruit(unsigned int _x, unsigned int _y) const
{
	float halfZ = -(m_height / 2.0f);
	float halfX = -(m_width / 2.0f);
	ngl::Transformation tx;
	tx.setPosition(halfX + _x, 0.0f, halfZ + _y);
	tx.setScale(0.25, 0.25, 0.25);
	auto shader = ngl::ShaderLib::instance();
	shader->setUniform("MVP", RenderGlobals::getVPMatrix() *tx.getMatrix());

	shader->setUniform("Colour", 1.0f, 0.0f, 0.0f, 0.0f); //fruit colours
	ngl::VAOPrimitives::instance()->draw(ngl::football);
}

void Arena::drawWall(unsigned int _x, unsigned int _y) const
{
	float halfZ = -(m_height / 2.0f);
	float halfX = -(m_width / 2.0f);
	ngl::Transformation tx;
	tx.setPosition(halfX + _x, 0.0f, halfZ + _y);
	//tx.setScale(1, 2, 1);

	auto shader = ngl::ShaderLib::instance();
	shader->setUniform("MVP", RenderGlobals::getVPMatrix() *tx.getMatrix());

	shader->setUniform("Colour", 1.0f, 1.0f, 0.0f, 0.0f); //wall colours
	ngl::VAOPrimitives::instance()->draw(ngl::cube);

}