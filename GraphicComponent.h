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
	GraphicComponent()
	{
		m_positionOrigin = Point::ZERO;
	}
	virtual ~GraphicComponent(){};

	virtual void Update(ManagerComponent& i_manager) = 0;

	virtual void ShowMenu()
	{
		Point _positionWarriorMenu = Point(m_positionOriginWithVisible.x + (m_rectOriginWithVisible.size.width / 2),
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
		Point _positionWarrior = Point(m_positionOriginWithVisible.x, m_positionOriginWithVisible.y - (m_rectOriginWithVisible.size.height / 2));
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
		Point _positionOrigin = this->getParent()->getPosition();
		_positionOrigin.x *= (-1);
		_positionOrigin.y *= (-1);

		i_locationTouch += _positionOrigin;
	}

	virtual void LoadProperties(Point i_positionVisible, Point i_positionOrigin)
	{
		m_positionVisible = i_positionVisible;
		m_positionOrigin = i_positionOrigin;
		
		if (m_positionOrigin.x < 0)
		{
			m_positionOrigin.x *= (-1);
		}
		if (m_positionOrigin.y < 0)
		{
			m_positionOrigin.y *= (-1);

		}
		
		m_locationTouch = Point::ZERO;

		Rect _box = this->getBoundingBox();

		// calculate RectOrigin(system coordinate all MapLayer)
		m_rectOrigin = Rect(this->getBoundingBox().getMinX() + m_positionOrigin.x, this->getBoundingBox().getMinY() + m_positionOrigin.y,
			this->getBoundingBox().size.width, this->getBoundingBox().size.height);
		// calculate RectVisible(system coordinate visible MapLayer)
		m_rectVisible = Rect(this->getBoundingBox().getMinX() + m_positionVisible.x, this->getBoundingBox().getMinY() + m_positionVisible.y,
			this->getBoundingBox().size.width, this->getBoundingBox().size.height);

		m_rectOriginWithVisible = Rect(this->getBoundingBox().getMinX() + m_positionOrigin.x + m_positionVisible.x,
			this->getBoundingBox().getMinY() + m_positionOrigin.y + m_positionVisible.y,
			this->getBoundingBox().size.width, this->getBoundingBox().size.height
			);

		m_numberComplete = 0;

		m_positionOriginWithVisible = m_positionOrigin + m_positionVisible;
		this->setPosition(m_positionOriginWithVisible);
	}

	virtual std::chrono::time_point<std::chrono::system_clock> GetTime()
	{
		std::chrono::time_point<std::chrono::system_clock> _time = std::chrono::system_clock::now();

		return _time;
	}

protected:
	std::chrono::time_point<std::chrono::system_clock> m_startSecond;
	int					m_timeForComplete;
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

	Point				m_locationTouch;
};

#endif