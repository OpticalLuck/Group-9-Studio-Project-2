#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:
	Scene() { isInit = false; }
	~Scene() {}

	virtual void Init() = 0;
	virtual void InitGL() = 0;
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;

	virtual void UpdateMousePos(double xoffset, double yoffset) = 0;

	bool isInit;
};

#endif