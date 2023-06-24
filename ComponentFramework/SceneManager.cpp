#include <SDL.h>
#include "SceneManager.h"
#include "Timer.h"
#include "Window.h"
#include "Scene0.h"
#include "Scene0p.h"
#include "Scene1g.h"
#include "Scene1ga.h"
#include "Scene1ga2.h"
#include "Scene1p.h"
#include "Scene2g.h"
#include "Scene2ga.h"
#include "Scene2p.h"
#include "Scene3g.h"
#include "Scene3p.h"
#include "Scene4g.h"
#include "Scene4p.h"


SceneManager::SceneManager(): 
	currentScene{nullptr}, window{nullptr}, timer{nullptr},
	fps(60), isRunning{false}, fullScreen{false} {
	Debug::Info("Starting the SceneManager", __FILE__, __LINE__);
}

SceneManager::~SceneManager() {
	Debug::Info("Deleting the SceneManager", __FILE__, __LINE__);

	if (currentScene) {
		currentScene->OnDestroy();
		delete currentScene;
		currentScene = nullptr;
	}
	
	if (timer) {
		delete timer;
		timer = nullptr;
	}

	if (window) {
		delete window;
		window = nullptr;
	}
	
}

bool SceneManager::Initialize(std::string name_, int width_, int height_) {

	window = new Window();
	if (!window->OnCreate(name_, width_, height_)) {
		Debug::FatalError("Failed to initialize Window object", __FILE__, __LINE__);
		return false;
	}

	timer = new Timer();
	if (timer == nullptr) {
		Debug::FatalError("Failed to initialize Timer object", __FILE__, __LINE__);
		return false;
	}

	/********************************   Default first scene   ***********************/
	BuildNewScene(SCENE_NUMBER::SCENE4G);
	/********************************************************************************/
	return true;
}

/// This is the whole game
void SceneManager::Run() {
	timer->Start();
	isRunning = true;
	while (isRunning) {
		HandleEvents();
		timer->UpdateFrameTicks();
		currentScene->Update(timer->GetDeltaTime());
		currentScene->Render();
		
		SDL_GL_SwapWindow(window->getWindow());
		SDL_Delay(timer->GetSleepTime(fps));
	}
}

void SceneManager::HandleEvents() {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) { /// Loop over all events in the SDL queue
		if (sdlEvent.type == SDL_EventType::SDL_QUIT) {
			isRunning = false;
			return;
		}
		else if (sdlEvent.type == SDL_KEYDOWN) {
			switch (sdlEvent.key.keysym.scancode) {
			[[fallthrough]]; /// C17 Prevents switch/case fallthrough warnings
			case SDL_SCANCODE_ESCAPE:
			//case SDL_SCANCODE_Q:
				isRunning = false;
				return;
				

			case SDL_SCANCODE_F1:
				break;
			case SDL_SCANCODE_F2:
			case SDL_SCANCODE_F3:
			case SDL_SCANCODE_F4:
			case SDL_SCANCODE_F5:
		
				BuildNewScene(SCENE_NUMBER::SCENE0);
				break;

			default:
				break;
			}
		}
		if (currentScene == nullptr) { /// Just to be careful
			Debug::FatalError("No currentScene", __FILE__, __LINE__);
			isRunning = false;
			return;
		}
		currentScene->HandleEvents(sdlEvent);
	}
}

bool SceneManager::BuildNewScene(SCENE_NUMBER scene) {
	bool status; 

	if (currentScene != nullptr) {
		currentScene->OnDestroy();
		delete currentScene;
		currentScene = nullptr;
	}

	switch (scene) {
	case SCENE_NUMBER::SCENE0:
		currentScene = new Scene0();
		status = currentScene->OnCreate();
		break;
	case SCENE_NUMBER::SCENE0P:
		currentScene = new Scene0p();
		status = currentScene->OnCreate();
		break;

	case SCENE_NUMBER::SCENE1P:
		currentScene = new Scene1p();
		status = currentScene->OnCreate();
		break;

	case SCENE_NUMBER::SCENE1G:
		currentScene = new Scene1g();
		status = currentScene->OnCreate();
		break;

	case SCENE_NUMBER::SCENE1GA:
		currentScene = new Scene1ga();
		status = currentScene->OnCreate();
		break;

	case SCENE_NUMBER::SCENE1GA2:
		currentScene = new Scene1ga2();
		status = currentScene->OnCreate();
		break;

	case SCENE_NUMBER::SCENE2G:
		currentScene = new Scene2g();
		status = currentScene->OnCreate();
		break;

	case SCENE_NUMBER::SCENE2GA:
		currentScene = new Scene2ga();
		status = currentScene->OnCreate();
		break;

	case SCENE_NUMBER::SCENE2P:
		currentScene = new Scene2p();
		status = currentScene->OnCreate();
		break;

	case SCENE_NUMBER::SCENE3G:
		currentScene = new Scene3g();
		status = currentScene->OnCreate();
		break;

	case SCENE_NUMBER::SCENE3P:
		currentScene = new Scene3p();
		status = currentScene->OnCreate();
		break;

	case SCENE_NUMBER::SCENE4G:
		currentScene = new Scene4g();
		status = currentScene->OnCreate();
		break;

	case SCENE_NUMBER::SCENE4P:
		currentScene = new Scene4p();
		status = currentScene->OnCreate();
		break;

	default:
		Debug::Error("Incorrect scene number assigned in the manager", __FILE__, __LINE__);
		currentScene = nullptr;
		return false;
	}
	return true;
}


