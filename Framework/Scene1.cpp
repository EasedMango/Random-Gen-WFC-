#include "Scene1.h"
#include "WaveCollapse.h"
using namespace std;


Scene1::Scene1(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	screenRenderer = NULL;
	background = new Body(Vec3(), Vec3(), Vec3(),
		0.0f, "textures/bluemoon.png");
	balloon = new Body(Vec3(200, 100, 5), Vec3(), Vec3(),
		0.0f, "textures/balloon.png");
	backgroundTexture = NULL;
	balloonTexture = NULL;
	map.OnCreate();

	map.GetRules();
}

bool Scene1::OnCreate() {
	//Create renderer for window
	screenRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!screenRenderer) {
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	map.GetRules();

	//map.Print();
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

	int window_w, window_h;
	SDL_GetWindowSize(window, &window_w, &window_h);
	Matrix4 ndc = MMath::viewportNDC(window_w,window_h);
	Matrix4 ortho =MMath::orthographic(-30.0f, 30.0f, -15.0f, 15.0f, 0.0f, 1.0f);

	projectionMatrix = ndc * ortho;
	map.Generate();
	return true;
}


void Scene1::HandleEvents(const SDL_Event& sdlEvent) {

}

void Scene1::Update(const float deltaTime) {
	balloon->Update(deltaTime);
	static float time = 0;
	time += deltaTime;
	if (time >= 1) {
		//printf("abcd");

		time = 0;
	}
}

void Scene1::Render() {
	// Clear the screen
	SDL_RenderClear(screenRenderer);

	// Render the background to the window.
//	SDL_RenderCopy(screenRenderer, backgroundTexture, NULL, NULL);

	// Render the balloon. We first need to scale it. If we do not scale 
	// the balloon texture, it will stretch out to the whole window.
	// Try it out!


	RenderWave();
	// Update screen
	SDL_RenderPresent(screenRenderer);

}

SDL_Texture* Scene1::loadImage(const char* textureFile)
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

SDL_Rect Scene1::scale(SDL_Texture* objectTexture, int start_x, int start_y, float scale) {

	// Get the size of the input texture
	SDL_Point size;
	SDL_QueryTexture(objectTexture, NULL, NULL, &size.x, &size.y);
	SDL_Rect dest = { start_x, start_y, size.x * scale, size.y * scale };
	return dest;
}

void Scene1::OnDestroy() {
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

void Scene1::RenderWave()
{
	for (size_t i = 0; i < HEIGHT; i++)
	{
		for (size_t j = 0; j < WIDTH; j++)
		{
			SDL_Rect dest;
		//	std::cout << "I: " << i << " J: " << j << "\n";
			Vec3 coords(i, j, 0); 
			Vec3 projCoords=  projectionMatrix* (coords);
			dest.x = projCoords.x;
			dest.y = projCoords.y;

			dest.w = 10;
			dest.h = 10;
			Vec4 colour;
			switch (map.tiles[i][j]->type)
			{
			case 'm':
				colour = Vec4(89, 77, 59, 0);
				break;
			case 'l':
				colour = Vec4(56, 150, 59, 0);
				break;
			case 'c':
				colour = Vec4(240, 220, 120, 0);
				break;
			case 's':
				colour = Vec4(59, 161, 204, 0);
				break;
			case 'e':
				colour = Vec4(255, 255, 255, 0);
				break;
			default:
				break;
			}
			SDL_SetRenderDrawColor(screenRenderer, colour.x, colour.y, colour.z, 255);
			SDL_RenderDrawRect(screenRenderer, &dest);
			SDL_RenderFillRect(screenRenderer, &dest);
			SDL_SetRenderDrawColor(screenRenderer, 0, 0, 0, 255);
			//cout << map.tiles[i][j]->type << "\n";
		}
	}
}

Scene1::~Scene1() {
	cout << "deleting child class: Scene1." << endl;
	delete background;
	delete balloon;
}