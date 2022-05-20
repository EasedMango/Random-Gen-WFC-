#include "Scene0.h"
using namespace std; 


Scene0::Scene0(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	screenRenderer = NULL;
	background = new Body(Vec3(), Vec3(), Vec3(), 
						0.0f, "textures/bluemoon.png");
	balloon = new Body(Vec3(200, 100, 5), Vec3(), Vec3(), 
						0.0f, "textures/balloon.png");
	backgroundTexture = NULL;
	balloonTexture = NULL; 
}

bool Scene0::OnCreate() {
	//Create renderer for window
	screenRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!screenRenderer) {
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	//Initialize renderer color (black)
	SDL_SetRenderDrawColor(screenRenderer, 0, 0, 0, 255);

	// Initialize PNG image loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "SDL_image Error: " << IMG_GetError() << std::endl;
		return false;
	}

	// Load the bodies's textures
	backgroundTexture = loadImage(background->GetTextureFile());
	balloonTexture = loadImage(balloon->GetTextureFile());

	return true;
}


void Scene0::HandleEvents(const SDL_Event& sdlEvent) {

}

void Scene0::Update(const float deltaTime) {
	balloon->Update(deltaTime);
}

void Scene0::Render() {
	// Clear the screen
	SDL_RenderClear(screenRenderer);

	// Render the background to the window.
	SDL_RenderCopy(screenRenderer, backgroundTexture, NULL, NULL);

	// Render the balloon. We first need to scale it. If we do not scale 
	// the balloon texture, it will stretch out to the whole window.
	// Try it out!
	SDL_Rect dest = scale(balloonTexture, balloon->getPos().x, balloon->getPos().y, 0.5f);
	SDL_RenderCopy(screenRenderer, balloonTexture, NULL, &dest);

	// Update screen
	SDL_RenderPresent(screenRenderer);

}

SDL_Texture* Scene0::loadImage(const char* textureFile)
{
	// The following is a typical chunk of code for creating 
	// a texture in SDL
	
	// The final texture
	SDL_Texture* newTexture = NULL;

	// Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(textureFile);
	if (!loadedSurface)
	{
		cout << "Unable to load image " << textureFile <<
			"! SDL_image Error: " << IMG_GetError() << endl;
	}
	else
	{
		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(screenRenderer, loadedSurface);
		if (!newTexture)
		{
			cout << "Unable to create texture " << textureFile <<
				"! SDL Error: " << SDL_GetError() << endl;
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

SDL_Rect Scene0::scale(SDL_Texture* objectTexture, int start_x, int start_y, float scale) {

	// Get the size of the input texture
	SDL_Point size;
	SDL_QueryTexture(objectTexture, NULL, NULL, &size.x, &size.y);
	SDL_Rect dest = { start_x, start_y, size.x * scale, size.y * scale };
	return dest;
}

void Scene0::OnDestroy() {
	// Free loaded images.
	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyTexture(balloonTexture);
	backgroundTexture = NULL;
	balloonTexture = NULL; 

	// Destroy the renderer.
	if (screenRenderer) {
		SDL_DestroyRenderer(screenRenderer);
		screenRenderer = NULL;
	}
}

Scene0::~Scene0() {
	cout << "deleting child class: Scene1." << endl;
	delete background;
	delete balloon; 
}