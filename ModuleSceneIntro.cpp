#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	//circuit
	//rect_one--------------
	Cube rect_1(1, 2, 70);
	rect_1.SetPos(10,0.9f,0);
	walls.add(rect_1);
	//front----------------------
	Cube rect_1f(1, 2, 70);
	rect_1f.SetPos(-5,0.9f,0);
	walls.add(rect_1f);
	//curve_one-----------
	Cube curve_1(1, 2, 7);
	curve_1.SetPos(8.5,0.9f,37.5);
	curve_1.SetRotation(-30, vec3(0,1, 0));
	walls.add(curve_1);
	//------------------------
	Cube curve_2(1, 2, 7);
	curve_2.SetPos(5.7, 0.9f, 42.5);
	curve_2.SetRotation(-30, vec3(0, 1, 0));
	walls.add(curve_2);
	//------------------------
	Cube curve_3(1, 2, 8);
	curve_3.SetPos(7, 0.9f, 47.3);
	curve_3.SetRotation(60, vec3(0, 1, 0));
	walls.add(curve_3);
	//------------------------
	Cube curve_4(1, 2, 8);
	curve_4.SetPos(12, 0.9f, 50.3);
	curve_4.SetRotation(59, vec3(0, 1, 0));
	walls.add(curve_4);
	//------------------------
	Cube curve_5(1, 2, 13);
	curve_5.SetPos(18.2, 0.9f, 57.3);
	curve_5.SetRotation(30, vec3(0, 1, 0));
	walls.add(curve_5);
	//------------------------
	Cube curve_6(1, 2, 10);
	curve_6.SetPos(22.5, 0.9f, 67.3);
	curve_6.SetRotation(15, vec3(0, 1, 0));
	walls.add(curve_6);
	//------------------------
	Cube curve_7(1, 2, 10);
	curve_7.SetPos(23.9, 0.9f, 76.5);
	walls.add(curve_7);
	//------------------------
	Cube curve_8(1, 2, 10);
	curve_8.SetPos(22.9, 0.9f, 85.3);
	curve_8.SetRotation(-15, vec3(0, 1, 0));
	walls.add(curve_8);
	//------------------------
	Cube curve_9(1, 2, 13);
	curve_9.SetPos(19.9, 0.9f, 96.2);
	curve_9.SetRotation(-15, vec3(0, 1, 0));
	walls.add(curve_9);

    //front------------------------
	Cube curve_1f(1, 2, 13);
	curve_1f.SetPos(-8.2, 0.9f,40.4);
	curve_1f.SetRotation(-30, vec3(0, 1, 0));
	walls.add(curve_1f);
	//------------------------
	Cube curve_2f(1, 2, 6);
	curve_2f.SetPos(-11.5, 0.9f, 49);
	walls.add(curve_2f);
	//------------------------
	Cube curve_3f(1, 2, 13);
	curve_3f.SetPos(-5.7, 0.9f, 55);
	curve_3f.SetRotation(60, vec3(0,1,0));
	walls.add(curve_3f);
	//------------------------
	Cube curve_4f(1, 2, 8);
	curve_4f.SetPos(-0.4, 0.9f, 58);
	curve_4f.SetRotation(60, vec3(0, 1, 0));
	walls.add(curve_4f);
    //------------------------
	Cube curve_5f(1, 2, 10);
	curve_5f.SetPos(5.4, 0.9f, 64.1);
	curve_5f.SetRotation(30, vec3(0, 1, 0));
	walls.add(curve_5f);
    //------------------------
	Cube curve_6f(1, 2, 9);
	curve_6f.SetPos(9, 0.9f, 72.5);
	curve_6f.SetRotation(15, vec3(0, 1, 0));
	walls.add(curve_6f);
	//------------------------
	Cube curve_7f(1, 2, 5);
	curve_7f.SetPos(10.2, 0.9f, 79.2);
	walls.add(curve_7f);
	//------------------------
	Cube curve_8f(1, 2, 6);
	curve_8f.SetPos(9.5, 0.9f, 84.5);
	curve_8f.SetRotation(-15, vec3(0, 1, 0));
	walls.add(curve_8f);
	//-------------------------
	Cube curve_9f(1, 2, 7);
	curve_9f.SetPos(7.9, 0.9f, 90.5);
	curve_9f.SetRotation(-15, vec3(0, 1, 0));
	walls.add(curve_9f);
	//rect_two-----------------
	Cube rect_2(1, 2, 32);
	rect_2.SetPos( 5.6, 0.9f, 109.9);
	rect_2.SetRotation(-60, vec3(0, 1, 0));
	walls.add(rect_2);
	//-------------------------
	Cube rect_2f(1, 2, 30);
	rect_2f.SetPos(-5.7, 0.9f, 100.9);
	rect_2f.SetRotation(-60, vec3(0, 1, 0));
	walls.add(rect_2f);


	//colisionador-----------------------------
	p2List_item<Cube>* item = walls.getFirst();
	while (item != NULL) {
		App->physics->AddBody(item->data, 0.0f);
		item = item->next;
	}
	
	//Sensor Meta
	s.size = vec3(15, 3, 1);
	s.SetPos(2.5, 2, 0);
	sensor = App->physics->AddBody(s, 0.0f);
	sensor->SetAsSensor(true);
	sensor->collision_listeners.add(this);
	sensor->type = SensorType::objective;

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	
	sensor->GetTransform(&s.transform);

	p2List_item<Cube>* item = walls.getFirst();
	while (item != NULL)
	{
		item->data.Render();
		item = item->next;
    }

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	LOG("Hit!");
}

