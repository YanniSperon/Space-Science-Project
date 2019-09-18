#include "Config.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

Config::Config(std::string name)
{
	LoadConfig("", name);
}

Config::Config(std::string dir, std::string name)
{
	LoadConfig(dir, name);
}

Config::~Config()
{
	
}

void Config::LoadConfig(std::string dir, std::string name)
{
	fullscreen = false;
	initialWidth = 1280;
	initialHeight = 720;
	mouseSensitivity = 0.01f;
	FOV = 60.0f;

	std::ifstream f(dir + name);

	if (!f.is_open()) {
		std::cout << "Config file: \"" << dir << name << "\" does not exist or could not be loaded.\n";
	}

	while (!f.eof())
	{
		std::string line;
		std::getline(f, line);

		if (line.find("fullscreen=") != std::string::npos) {
			std::string value = line.substr(11);
			if (value == "true") {
				fullscreen = true;
			}
			else {
				fullscreen = false;
			}
		}
		else if (line.find("initialWidth=") != std::string::npos) {
			std::string value = line.substr(13);
			initialWidth = std::stoi(value);
		}
		else if (line.find("initialHeight=") != std::string::npos) {
			std::string value = line.substr(14);
			initialHeight = std::stoi(value);
		}
		else if (line.find("mouseSensitivity=") != std::string::npos) {
			std::string value = line.substr(17);
			mouseSensitivity = std::stof(value);
		}
		else if (line.find("FOV=") != std::string::npos) {
			std::string value = line.substr(4);
			FOV = std::stof(value);
		}
	}
}

bool Config::getFullscreenPreference()
{
	return fullscreen;
}

int Config::getInitialWidthPreference()
{
	return initialWidth;
}

int Config::getInitialHeightPreference()
{
	return initialHeight;
}

float Config::getMouseSensitivityPreference()
{
	return mouseSensitivity;
}

float Config::getFOVPreference()
{
	return FOV;
}
