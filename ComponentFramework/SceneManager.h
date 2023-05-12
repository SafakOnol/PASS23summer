#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <string>
class SceneManager  {
public:
	
	SceneManager();
	~SceneManager();
	void Run();
	bool Initialize(std::string name_, int width_, int height_);
	void HandleEvents();
	
	
private:
	enum class SCENE_NUMBER {
		SCENE0 = 0,
		SCENE1G,
		SCENE1P,
		SCENE2G,
		SCENE2P,
		SCENE3G,
		SCENE3P,
		SCENE4G,
		SCENE4P,
		SCENE5G,
		SCENE5P,
		SCENE6G,
		SCENE6P
	};

	class Scene* currentScene;
	class Timer* timer;
	class Window* window;

	unsigned int fps;
	bool isRunning;
	bool fullScreen;
	bool BuildNewScene(SCENE_NUMBER scene_);
};


#endif // SCENEMANAGER_H