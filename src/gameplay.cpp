/* Copyright: (c) Kayne Ruse 2013, 2014
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 * 
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 
 * 3. This notice may not be removed or altered from any source
 * distribution.
*/
#include "gameplay.hpp"

//-------------------------
//Global functions
//-------------------------

int setPixel(SDL_Surface* const dest, int x, int y, int colour) {
	return *(static_cast<int*>(dest->pixels) + dest->w * y + x) = colour;
}

int getPixel(SDL_Surface* const dest, int x, int y) {
	return *(static_cast<int*>(dest->pixels) + dest->w * y + x);
}

//-------------------------
//Public access members
//-------------------------

Gameplay::Gameplay() {
	shipField.CreateSurface(GetScreen()->w, GetScreen()->h);
	droneField.CreateSurface(GetScreen()->w, GetScreen()->h);
	for (int i = 0; i < 100; i++) {
		droneList.push_back({i*3, i*3});
	}
}

Gameplay::~Gameplay() {
	//
}

//-------------------------
//Frame loop
//-------------------------

void Gameplay::FrameStart() {
	//
}

void Gameplay::Update() {
	//
}

void Gameplay::FrameEnd() {
	//
}

void Gameplay::Render(SDL_Surface* const screen) {
	//clear the fields
	SDL_FillRect(shipField.GetSurface(), 0, SDL_MapRGB(shipField.GetSurface()->format, 0,  0, 0));
	SDL_FillRect(droneField.GetSurface(), 0, SDL_MapRGB(droneField.GetSurface()->format, 0,  64, 128));

	//draw the ships (fog of war)
	for(std::list<Ship>::iterator it = shipList.begin(); it != shipList.end(); it++) {
		SDL_Rect box = {it->x, it->y, (Uint16)32, (Uint16)32};
		SDL_FillRect(shipField.GetSurface(), &box, SDL_MapRGB(shipField.GetSurface()->format, 255, 255, 255));
	}

	//draw the drones
	for(std::list<Drone>::iterator it = droneList.begin(); it != droneList.end(); it++) {
		setPixel(droneField.GetSurface(), it->x, it->y, SDL_MapRGB(droneField.GetSurface()->format, 255, 0, 0));
	}

	//draw to the screen
	for (int i = 0; i < screen->w; i++) {
		for (int j = 0; j < screen->h; j++) {
			setPixel(screen, i, j, getPixel(shipField.GetSurface(), i, j) & getPixel(droneField.GetSurface(), i, j));
		}
	}
}

//-------------------------
//Event handlers
//-------------------------

void Gameplay::MouseMotion(SDL_MouseMotionEvent const& motion) {
	//
}

void Gameplay::MouseButtonDown(SDL_MouseButtonEvent const& button) {
	shipList.push_back({button.x, button.y});
}

void Gameplay::MouseButtonUp(SDL_MouseButtonEvent const& button) {
	//
}

void Gameplay::KeyDown(SDL_KeyboardEvent const& key) {
	//hotkeys
	switch(key.keysym.sym) {
		case SDLK_ESCAPE:
			QuitEvent();
		break;
	}
}

void Gameplay::KeyUp(SDL_KeyboardEvent const& key) {
	//
}
