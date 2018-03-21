#pragma once
#include "Sprite.h"
#include "Music.h"
#include <iostream>

class State
{
	public:
		State(void);
		~State(void);
		bool QuitRequested(void);
        void LoadAssets(void);
		void Update(float dt);
		void Render(void);

	private:
		Sprite *bg;
        Music *music;
		bool quitRequested;
};

