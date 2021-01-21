#include "SceneManager.h"
#include "DxLib.h"

SceneManager::SceneManager() {
	sc = title;
	isEnd = 0;
}

void SceneManager::change(char keys[255], char oldkeys[255]) {
	if (isEnd == 0) {
		switch (sc) {
		case title:
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
				sc = play;
			}
			break;
		case play:
			/*if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
				Scene = 3;
			}*/
			break;
		case result:
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
				isEnd = 1;
			}
			break;
		}
	}
}
