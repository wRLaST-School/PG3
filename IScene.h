#pragma once
class IScene
{
public:
	virtual void Load() = 0;
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual ~IScene() {	};
};

