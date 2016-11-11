#ifndef __FACTORY_H__
#define __FACTORY_H__

#include "cocos2d.h"
#include "GraphicComponent.h"
#include "GameScene.h"
#include "MapLayer.h"
#include "constants.h"

using namespace cocos2d;

class Factory : public GraphicComponent
{
public:
	Factory(){};
	Factory(Point i_positionVisible, MapLayer& i_mapLayer, std::string i_fileFactory)
	{
		i_mapLayer.addChild(this);

		m_positionVisible = i_positionVisible;

		m_positionOrigin = this->getParent()->getPosition();
		m_positionOrigin.x *= (-1);
		m_positionOrigin.y *= (-1);

		this->initWithFile(CNT_PATH_TO_RESOURCES + i_fileFactory);
		this->setScale(GameScene::m_visibleSize.width / this->getContentSize().width / 6,
			GameScene::m_visibleSize.height / this->getContentSize().height / 6);

		m_locationTouch = Point::ZERO;

		Rect _box = this->getBoundingBox();

		// calculate RectOrigin(system coordinate all MapLayer)
		m_rectFactoryOrigin = Rect(this->getBoundingBox().getMinX() + m_positionOrigin.x, this->getBoundingBox().getMinY() + m_positionOrigin.y,
			this->getBoundingBox().size.width, this->getBoundingBox().size.height);
		// calculate RectVisible(system coordinate visible MapLayer)
		m_rectFactoryVisible = Rect(this->getBoundingBox().getMinX() + m_positionVisible.x, this->getBoundingBox().getMinY() + m_positionVisible.y,
			this->getBoundingBox().size.width, this->getBoundingBox().size.height);

		m_rectFactoryOriginWithVisible = Rect(this->getBoundingBox().getMinX() + m_positionOrigin.x + m_positionVisible.x,
			this->getBoundingBox().getMinY() + m_positionOrigin.y + m_positionVisible.y,
			this->getBoundingBox().size.width, this->getBoundingBox().size.height
			);

		m_numberComplete = 0;

		m_positionOriginWithVisible = m_positionOrigin + m_positionVisible;
		this->setPosition(m_positionOriginWithVisible);

	}

	void ShowMenu()
	{
		Point _positionWarriorMenu = Point(m_positionOriginWithVisible.x + (m_rectFactoryVisible.size.width / 2),
			m_positionOriginWithVisible.y);
		for (int i = 0; i < m_vecSpritesForFactory.size(); i++)
		{
			m_vecSpritesForFactory[i]->setPosition(_positionWarriorMenu);
			m_vecSpritesForFactory[i]->setVisible(true);
			m_rectForSprites.push_back(m_vecSpritesForFactory[i]->getBoundingBox());

			_positionWarriorMenu.y -= m_vecSpritesForFactory[i]->getBoundingBox().size.height / 2;
		}
	}

	void HideMenu()
	{
		for (int i = 0; i < m_vecSpritesForFactory.size(); i++)
		{
			m_vecSpritesForFactory[i]->setVisible(false);
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
		Point _positionWarrior = Point(m_positionOriginWithVisible.x, m_positionOriginWithVisible.y - (m_rectFactoryVisible.size.height / 2));
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
			m_vecSpritesForFactory.push_back(Sprite::create(m_vecNameForSprites[i]));
			m_vecSpritesForFactory[i]->setScale(GameScene::m_visibleSize.width / m_vecSpritesForFactory[i]->getContentSize().width / 15,
				GameScene::m_visibleSize.height / m_vecSpritesForFactory[i]->getContentSize().height / 15);
			m_vecSpritesForFactory[i]->setVisible(false);
			this->getParent()->addChild(m_vecSpritesForFactory[i]);
		}
	}

	virtual void Update(ManagerComponent& i_manager) = 0;

	~Factory(){};

protected:
	std::chrono::time_point<std::chrono::system_clock> m_startSecond;
	int					m_timeForComplete;
	Vec2				m_locationTouch;
	Rect				m_rectFactoryOrigin;
	Rect				m_rectFactoryVisible;
	Rect				m_rectFactoryOriginWithVisible;

	std::vector<std::string>	m_vecNameForSprites;
	std::vector<Sprite*>		m_vecSpritesForFactory;
	std::vector<Rect>			m_rectForSprites;

	std::vector<Point>	m_vecPosition;
	int					m_numberComplete;
	Point				m_positionOrigin;
	Point				m_positionVisible;
	Point				m_positionOriginWithVisible;
};

#endif