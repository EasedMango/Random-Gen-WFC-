#pragma once
#include <vector>
#include <random>
#include <SDL.h>
#include <SDL_image.h>
#include "Scene.h"
#include "Body.h"

// The goal of this task is to create balls on the screen based on keyboard and mouse input.
// When the (R, G, or B) button is clicked, a (red, green, or blue) ball gets created on the 
// screen at a random location. When a mouse clicks anywhere in the window, a yellow ball 
// should be created at where it was clicked.

class SceneUsingVec : public Scene {

	SDL_Window* window;
	SDL_Renderer* screenRenderer;

	int window_h;
	int window_w; 

	std::vector <Body*> balls; // {redBall1, yellowBall1, redBall2, ...}
	SDL_Texture* redBallTexture;
	SDL_Texture* greenBallTexture;
	SDL_Texture* blueBallTexture;
	SDL_Texture* yellowBallTexture;

	// keep track of (attributes):
	// - the balls we created
	// - texture of the balls



	/// <summary>
	/// Load an image into a texture object.
	/// </summary>
	/// <param name="textureFile">image file</param>
	/// <returns>The SDL texture of this image</returns>
	SDL_Texture* loadImage(const char* textureFile);

	/// <summary>
	/// Generate a rectangle that will encompass a scaled version of the image.
	/// </summary>
	/// <param name="objectTexture">Texture object of the image</param>
	/// <param name="start_x">The new x location of the image's upper left corner</param>
	/// <param name="start_y">The new y location of the image's upper left corner</param>
	/// <param name="scale">The new scale of the image (must be 
	/// bwteen 0.0 and 1.0)) </param>
	/// <returns>A rectangle that the image will be rendered inside</returns>
	SDL_Rect scale(SDL_Texture* objectTexture, 
					int start_x = 0, int start_y = 0, float scale = 1.0f);

public:

	/// <summary>
	/// Initiate a new scene.
	/// </summary>
	/// <param name="sdlWindow">The window which this scene will be rendered in.</param>
	SceneUsingVec(SDL_Window* sdlWindow);

	/// <summary>
	/// Create the renderer and load the bodies's textures.
	/// </summary>
	/// <returns> Whether this scene has been created.</returns>
	bool OnCreate();

	//bool loadTexture(const char* textureFile, SDL_Texture* gTexture);

	/// <summary>
	/// Update this scene's obejects. 
	/// </summary>
	/// <param name="time">The current time</param>
	void Update(const float time);

	/// <summary>
	/// Render this scene on the window. 
	/// </summary>
	void Render();

	/// <summary>
	/// Destroy this scene.
	/// </summary>
	void OnDestroy();

	/// <summary>
	/// Destructor. Delete all pointer attributes in this class
	/// then delete this object.
	/// </summary>
	~SceneUsingVec();

	/// <summary>
	/// Handle incoming events from the user and update the scene accordingly
	/// </summary>
	/// <param name="sdlEvent"></param>
	void HandleEvents(const SDL_Event& sdlEvent);
};


