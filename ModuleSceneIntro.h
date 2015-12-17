#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	Uint32 getBestLap();

public:
	Cube s;
	Cube s2;
	p2List<Cube> walls;

	PhysBody3D* sensor;
	PhysBody3D* sensor2;

	Timer crono;
	int laps;
	p2List<Uint32> lapTimes;
	Uint32 bestLap;

	bool sensorObjective = true;
	bool sensorRefill = true;
};
