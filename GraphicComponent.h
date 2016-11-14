#ifndef __GRAPHIC_COMPONENT_H__
#define __GRAPHIC_COMPONENT_H__

#include "cocos2d.h"
#include "GameScene.h"

USING_NS_CC;

class ManagerComponent;
class MapLayer;

class GraphicComponent : public Sprite
{
public:
	GraphicComponent(){}
	virtual ~GraphicComponent(){};

	virtual void Update(ManagerComponent& i_manager) = 0;
	
	void ShowMenu()
	{
		Point _positionWarriorMenu = Point(m_positionOriginWithVisible.x + (m_rectVisible.size.width / 2),
			m_positionOriginWithVisible.y);
		for (int i = 0; i < m_vecSprites.size(); i++)
		{
			m_vecSprites[i]->setPosition(_positionWarriorMenu);
			m_vecSprites[i]->setVisible(true);
			m_rectForSprites.push_back(m_vecSprites[i]->getBoundingBox());

			_positionWarriorMenu.y -= m_vecSprites[i]->getBoundingBox().size.height / 2;
		}
	}

	void HideMenu()
	{
		for (int i = 0; i < m_vecSprites.size(); i++)
		{
			m_vecSprites[i]->setVisible(false);
		}
	}

	bool isComplete()
	{
		if ((int)std::chrono::duration<double>(GraphicComponent::GetTime() - m_startSecond).count() == m_timeForComplete)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void LoadPosition()
	{
		Point _positionWarrior = Point(m_positionOriginWithVisible.x, m_positionOriginWithVisible.y - (m_rectVisible.size.height / 2));
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				m_vecPosition.push_back(_positionWarrior);
				_positionWarrior.x += 60;
			}
			_positionWarrior.y += 60;
		}
	}

	void LoadSprites()
	{
		float _positionY = GameScene::m_visibleSize.height / 2;
		for (int i = 0; i < m_vecNameForSprites.size(); i++)
		{
			m_vecSprites.push_back(Sprite::create(m_vecNameForSprites[i]));
			m_vecSprites[i]->setScale(GameScene::m_visibleSize.width / m_vecSprites[i]->getContentSize().width / 15,
				GameScene::m_visibleSize.height / m_vecSprites[i]->getContentSize().height / 15);
			m_vecSprites[i]->setVisible(false);
			this->getParent()->addChild(m_vecSprites[i]);
		}
	}

	void ConvertToOrigin(Point& i_locationTouch)
	{
		Point m_positionMap = this->getParent()->getPosition();
		m_locationTouch = i_locationTouch;
		Point _positionOrigin = this->getParent()->getPosition();
		_positionOrigin.x *= (-1);
		_positionOrigin.y *= (-1);

		m_locationTouch += _positionOrigin;
	}

	virtual std::chrono::time_point<std::chrono::system_clock> GetTime()
	{
		std::chrono::time_point<std::chrono::system_clock> _time = std::chrono::system_clock::now();

		return _time;
	}

protected:
	std::chrono::time_point<std::chrono::system_clock> m_startSecond;
	int					m_timeForComplete;
	Vec2				m_locationTouch;
	Rect				m_rectOrigin;
	Rect				m_rectVisible;
	Rect				m_rectOriginWithVisible;

	std::vector<std::string>	m_vecNameForSprites;
	std::vector<Sprite*>		m_vecSprites;
	std::vector<Rect>			m_rectForSprites;

	std::vector<Point>	m_vecPosition;
	int					m_numberComplete;
	Point				m_positionOrigin;
	Point				m_positionVisible;
	Point				m_positionOriginWithVisible;


};

#endif