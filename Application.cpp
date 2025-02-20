#include "Application.h"



Application::Application()
{
}

int Application::execute()
{
	while (Screen::window.isOpen())
	{
		Screen::window.clear();
		display();
		Screen::window.display();
		processEvents();
		update();
	}
	return EXIT_SUCCESS;
}

bool Application::initialize()
{
	Screen::window.setKeyRepeatEnabled(false);
	Screen::window.setFramerateLimit(60);

	pCard = nullptr;
	menu.initialize();
	deck.addCards();
	deck.shuffleCards();
	player.initialize();

	SoundManager::getInstance()->playMusic(Filename::musicFilename);

	return true;
}

void Application::update()
{
	menu.update(delta);
	if (gameState == GameState::PLAYER_INPUT)
	{
		delta = clock.restart();
	}
	else if (gameState == GameState::PLAYING)
	{
		updatePlaying();
	}
	else if (gameState == GameState::END)
	{
		updateEnd();
	}
}

void Application::display()
{
	menu.draw();
	switch (gameState)
	{
	case GameState::INTRO:
		menu.drawIntro();
		break;
	case GameState::PLAYER_INPUT: 
		player.draw();
		menu.drawInput();
		break;
	case GameState::PLAYING: 
		deck.draw();
		player.drawHud();
		break;
	case GameState::END: 
		menu.drawEnd();
		player.drawResult();
		break;
	}
}

void Application::updateEnd()
{
	SoundManager::getInstance()->stopMusic();
	player.rating();
	clock.restart();
	player.update(delta);
	if (menu.textClick() && !menu.quitRect())
	{ 
		SoundManager::getInstance()->playMusic(Filename::musicFilename);
	}
}

void Application::updatePlaying()
{
	delta = clock.getElapsedTime();
	player.update(delta); 
	deck.update(delta);  
}

void Application::processEvents()
{
	while (Screen::window.pollEvent(Event))
	{
		if ((Event.type == sf::Event::Closed) || (Event.type == sf::Event::KeyPressed)
		    && (Event.key.code == sf::Keyboard::Escape))
		{
			Screen::window.close();
		} 
		if ((Event.type == sf::Event::MouseButtonReleased))
		{
			pCard && gameState == GameState::PLAYING 
			? SoundManager::getInstance()->playSound(Resource::Sounds, Filename::cardFlip)
			: SoundManager::getInstance()->playSound(Resource::Sounds, Filename::clickSound);
			
			if (deck.checkMatching(player))
			{  
				if (player.allMatching())
				{
					gameState = GameState::END;
				}
			}  
		}
		if ((Event.type == sf::Event::MouseButtonPressed) && (Event.mouseButton.button == sf::Mouse::Left))
		{
			menu.musicSwitch();
			mouseScreenPosition = sf::Mouse::getPosition();
			mouseWorldPosition = Screen::window.mapPixelToCoords(sf::Mouse::getPosition());
			if (gameState == GameState::INTRO)
			{
				if (menu.textClick())
				{
					if (menu.quitRect())
					{
						Screen::window.close();
					}
					else 
					{
						gameState = GameState::PLAYER_INPUT;
					}
				} 
			} 
			else if (gameState == GameState::PLAYER_INPUT)
			{
				if (menu.textClick())
				{
					deck.initialize();
					gameState = GameState::PLAYING; 
				}
			}
			else if (gameState == GameState::PLAYING)
			{ 
				pCard = deck.clickCard(mouseWorldPosition);
				pCard && deck.pickCards(pCard, player);
			}
			else if (gameState == GameState::END)
			{
				if (menu.textClick())
				{
					if (menu.quitRect())
					{
						Screen::window.close();
					}
					else
					{
						gameState = GameState::PLAYER_INPUT;
						player.clearPlayerInput();
						menu.isMusicOn(true);
						player.resetScore();
						deck.resetCards();
					}
				}
			}
		} // End of mouse type event
		if (Event.type == sf::Event::TextEntered)
		{
			if (gameState == GameState::PLAYER_INPUT)
			{
				player.playerInput(Event);
			}
		}
	} 
}

Application::~Application()
{
}
