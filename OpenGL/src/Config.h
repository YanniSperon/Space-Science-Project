#pragma once
#include <string>

class Config {
private:
	bool fullscreen;
	int initialWidth;
	int initialHeight;
	float mouseSensitivity;
	float FOV;
public:
	Config(std::string name);
	Config(std::string dir, std::string name);
	~Config();
	void LoadConfig(std::string dir, std::string name);
	bool getFullscreenPreference();
	int getInitialWidthPreference();
	int getInitialHeightPreference();
	float getMouseSensitivityPreference();
	float getFOVPreference();
};