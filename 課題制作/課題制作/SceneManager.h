#pragma once
class SceneManager
{
private:
	enum scene {
		title,
		play,
		result
	};
	int isEnd;
	enum scene sc;
public:
	SceneManager();
	
	void change(char keys[255],char oldkeys[255]);
};

