#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <ctime>
#include <mutex>
#include <string>
#include <random>
#include <chrono>
#include <vector>
#include <memory>
#include <thread> 
#include <cassert>
#include <sstream>
#include <fstream>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <exception>
#include <functional> 
#include <unordered_map> 

#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


#define TEXT_INPUT ""
#define OK_BUTTON "OK"
#define GAME_TEXT "GAME"
#define QUIT_BUTTON "Quit"
#define PLAY_BUTTON "Play"
#define TITLE_TEXT "Memory"
#define PLAYER_TEXT "Player: "
#define REPEAT_BUTTON "Try again"
#define END_TEXT "CONGRATULATIONS"


typedef const std::string cStr;


template <typename T>
using sPtr = std::shared_ptr<T>;


inline double PI()
{
	return std::acos(-1);
}


namespace Screen
{
	extern sf::RenderWindow window;

	extern unsigned int screenWidth;
	extern unsigned int screenHeight;

	extern float cardWidht;
	extern float cardHeight;
}


namespace Filename
{
	// Fonts:
	extern cStr font1;
	extern cStr font2;

	// Textures:
	extern cStr menu;
	extern cStr paper;
	extern cStr sound;
	extern cStr noSound;
	extern cStr backCard;
	extern cStr background;

	// Audio:
	extern cStr cardFlip;
	extern cStr clickSound;
	extern cStr matchedSound;
	extern cStr musicFilename;
	extern cStr unmatchedSound;
}


