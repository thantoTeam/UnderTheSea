/*
 * Window.cpp
 *
 *  Created on: 29 oct. 2018
 *      Author: antonin
 */

#include "Window.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

#include "../General.h"
#include "Panel.h"
#include "Widget/Dimention.h"

namespace ta
{

Window::Window(Panel *panel) :
        RenderWindow(sf::VideoMode(250, 250), "An application"), m_textureLoader(
                new TextureLoader)
{
    changePanel(panel);

    m_view = getView();
    setFramerateLimit(FRAMERATE_LIMIT);
}

Window::Window(sf::VideoMode mode, sf::String title, Panel *panel) :
        RenderWindow(mode, title), m_textureLoader(new TextureLoader())
{
    changePanel(panel);

    m_view = getView(); // to correct resize
    setFramerateLimit(FRAMERATE_LIMIT);
}

Window::~Window()
{
    delete m_textureLoader;
    
    deleteCurrentPanel();
}

void Window::loadTexture()
{
    // load all texture need all time window is open
    
    
}

Panel * Window::currentPanel()
{
    return m_currentPanel;
}

void Window::changePanel(Panel* panel)
{
    deleteCurrentPanel();

    if (panel != 0) {
        m_currentPanel = panel;

        m_currentPanel->setup(this);

        m_currentPanel->setDimention(
                dimention(int(getDefaultView().getSize().x),
                        int(getDefaultView().getSize().y)));
    }
}

bool Window::deleteCurrentPanel()
{
    if (m_currentPanel != 0)
    { 
        delete m_currentPanel;
        m_currentPanel = 0;
        return true;
    }

    return false;
}

void Window::update()
{
    
    if (m_currentPanel == 0)
        return;
    
    clear();
    m_currentPanel->drawAllChild(this);
    display();
}

void Window::run()
{
    m_stopRun = false;
    
    ta::log::log("Window start updates");
    
    while (isOpen())
    {

        if (m_stopRun)
        {
            break;
        }
        
        sf::Event event;
        while (pollEvent(event))
        {
            testEvent(event);
        }

        update();
    }
    
    ta::log::log("Window stop updates");
}

void Window::testEvent(sf::Event event)
{
    switch (event.type)
    {
    case sf::Event::Closed:
        stopRun();
        break;
        
    case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Escape) stopRun();
        break;
    
    default:
        return;
    }
    
    // send event to all widgets
    
    if (m_currentPanel != 0) m_currentPanel->onEvent(event);
}

void Window::stopRun()
{
    m_stopRun = true;
}

TextureLoader* Window::textureLoader()
{
    return m_textureLoader;
}

} /* namespace ta */
