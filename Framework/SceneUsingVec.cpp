#include "SceneUsingVec.h"


using namespace std; 

// The goal of this task is to create balls on the screen based on keyboard and mouse input.
// When the (R, G, or B) button is clicked, a (red, green, or blue) ball gets created on the 
// screen at a random location. When a mouse clicks anywhere in the window, a yellow ball 
// should be created at where it was clicked.

// if the user enters R, I'll create a red ball at location 1, 1

// - get the mouse location
// - keep track of all the objects that we create
// - we need to check the type of input that we get
// - get some random x, y
// - rendering of the all the object that we have at that point

// keep track of (attributes):
// - the balls we created
// - texture of the balls
//
// method/function
// - get random location for r, g, b balls. 
// - get mouse location for y ball
// - get the type of input

SceneUsingVec::SceneUsingVec(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	screenRenderer = NULL; //nullptr

	SDL_GetWindowSize(window, &window_w, &window_h);

	redBallTexture = NULL; 
	greenBallTexture = NULL;
	blueBallTexture = NULL;
	yellowBallTexture = NULL; 

}

bool SceneUsingVec::OnCreate() {
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
	redBallTexture = loadImage("textures/red_ball.png");
	greenBallTexture = loadImage("textures/green_ball.png");
	blueBallTexture = loadImage("textures/blue_ball.png");
	yellowBallTexture = loadImage("textures/yellow_ball.png");

	return true;
}

// if the user enters R, I'll create a red ball at 1, 1
// if the user enters R, I'll create a red ball at random location
// do it again for the green and blue balls
// get the mouse input and create a yellow ball
void SceneUsingVec::HandleEvents(const SDL_Event& sdlEvent) {
	if (sdlEvent.type == SDL_KEYDOWN) {
		int x = rand() % window_w; //345326653385
		int y = rand() % window_h;
		// 1, 2, 3, 4, [5], 6, 7, 8
		// window_w == 5
		// x = 7
		// x == 2
		// 7 % 5
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_R) {
			Body* ball_temp = new Body(Vec3(x, y, 1), Vec3(), Vec3(), 1.0f, "textures/red_ball.png");
			balls.push_back(ball_temp);
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_G) {
			Body* ball_temp = new Body(Vec3(x, y, 1), Vec3(), Vec3(), 1.0f, "textures/green_ball.png");
			balls.push_back(ball_temp);
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_B) {
			Body* ball_temp = new Body(Vec3(x, y, 1), Vec3(), Vec3(), 1.0f, "textures/blue_ball.png");
			balls.push_back(ball_temp);
		}
	}

	else if (sdlEvent.type == SDL_MOUSEBUTTONDOWN && sdlEvent.button.button == SDL_BUTTON_LEFT) {
		float mouse_x = sdlEvent.button.x;
		float mouse_y = sdlEvent.button.y;
		Body* ball_temp = new Body(Vec3(mouse_x, mouse_y, 1), Vec3(), Vec3(), 1.0f, "textures/yellow_ball.png");
		balls.push_back(ball_temp);

	}
}

void SceneUsingVec::Update(const float deltaTime) {
	
}

void SceneUsingVec::Render() {
	// Clear the screen
	SDL_RenderClear(screenRenderer);

	SDL_Rect dest;
	for (Body* item_ball : balls) {
		if (item_ball->GetTextureFile() == "textures/red_ball.png") {
			dest = scale(redBallTexture, item_ball->getPos().x, item_ball->getPos().y, 0.2f);
			SDL_RenderCopy(screenRenderer, redBallTexture, NULL, &dest);
		}
		else if (item_ball->GetTextureFile() == "textures/green_ball.png") {
			dest = scale(greenBallTexture, item_ball->getPos().x, item_ball->getPos().y, 0.2f);
			SDL_RenderCopy(screenRenderer, greenBallTexture, NULL, &dest);
		}
		else if (item_ball->GetTextureFile() == "textures/blue_ball.png") {
			dest = scale(blueBallTexture, item_ball->getPos().x, item_ball->getPos().y, 0.2f);
			SDL_RenderCopy(screenRenderer, blueBallTexture, NULL, &dest);
		}

		else if (item_ball->GetTextureFile() == "textures/yellow_ball.png") {
			dest = scale(yellowBallTexture, item_ball->getPos().x, item_ball->getPos().y, 0.2f);
			SDL_RenderCopy(screenRenderer, yellowBallTexture, NULL, &dest);
		}

	}

	// Update screen
	SDL_RenderPresent(screenRenderer);

}

SDL_Texture* SceneUsingVec::loadImage(const char* textureFile)
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

SDL_Rect SceneUsingVec::scale(SDL_Texture* objectTexture, int start_x, int start_y, float scale) {

	// Get the size of the input texture
	SDL_Point size;
	SDL_QueryTexture(objectTexture, NULL, NULL, &size.x, &size.y);
	SDL_Rect dest = { start_x, start_y, size.x * scale, size.y * scale };
	return dest;
}

void SceneUsingVec::OnDestroy() {
	// Free loaded images.
	SDL_DestroyTexture(redBallTexture);
	SDL_DestroyTexture(greenBallTexture);
	SDL_DestroyTexture(blueBallTexture);
	SDL_DestroyTexture(yellowBallTexture);

	redBallTexture = NULL;
	greenBallTexture = NULL;
	blueBallTexture = NULL;
	yellowBallTexture = NULL;

	// Destroy the renderer.
	if (screenRenderer) {
		SDL_DestroyRenderer(screenRenderer);
		screenRenderer = NULL;
	}
}

SceneUsingVec::~SceneUsingVec() {
	for (Body* item_ball : balls) {
		delete item_ball;
	}

	delete window;
}