/*
 * Widget.h
 *
 *  Created on: 23 oct. 2018
 *      Author: PyJaC++
 */
#ifndef WIDGET_H_
#define WIDGET_H_

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

#include "Dimention.h"


namespace sf
{
class RenderWindow;
} /* namespace sf */

namespace ta
{

class Widget
{
public:
	Widget(Widget *parent = 0);
	Widget(Dimention<int> dim, Widget *parent = 0);
	Widget(sf::Vector2<float> pos, Dimention<int> dim, Widget* parent = 0);
	virtual ~Widget();
	
	virtual void draw(sf::RenderWindow *win);

	virtual void onClick(const sf::Event::MouseButtonEvent& event);

	void drawAllChild(sf::RenderWindow *win);
	
	virtual bool setPosition(float x, float y);
	virtual bool setPosition(sf::Vector2<float>);
	virtual bool move(int x, int y);
	
	virtual void setDimention(int x, int y);
	virtual void setDimention(Dimention<int> dim);

	sf::Vector2<float> position() const;
	Dimention<int> dimention() const;

	void deleteWidget();

protected:
	
	void addChild(Widget*child);
	void removeChild(Widget *child);
	void deleteAllChilds();
		
	Widget * m_parent;
	std::vector<Widget*> m_listChild;
	
	sf::Vector2<float> m_position;	
	Dimention<int> m_dimention;
};

} /* namespace Thanto */

#endif /* WIDGET_H_ */
