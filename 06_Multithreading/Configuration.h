#pragma once
#include "ResourceManager.h"
#include "ActionMap.h"

#include <SFML/Graphics.hpp>

namespace book
{
	class Configuration
	{
	public:
		Configuration() = delete;
		Configuration(const Configuration&) = delete;
		Configuration& operator=(const Configuration&) = delete;

		enum Fonts : int {Gui};
		static ResourceManager<sf::Font, int> fonts;

		enum PlayerInputs : int
		{
			TurnLeft,
			TurnRight,
			MoveLeft,
			MoveRight,
			HardDrop
		};
		static ActionMap<int> playerInputs;

		enum GuiInputs : int {Escape};
		static ActionMap<int> guiInputs;

		enum Sounds : int 
		{
			Spawn,
			Explosion,
			LevelUp
		};
		static ResourceManager<sf::SoundBuffer, int> sounds;

		enum Musics : int {Theme};
		static ResourceManager<sf::Music, int> musics;

		static void initialize();

	private:
		static void initTextures();
		static void initFonts();
		static void initSounds();
		static void initMusics();

		static void initPlayerInputs();
		static void initGuiInputs();
	};
}