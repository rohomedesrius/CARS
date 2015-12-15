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

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	//circuit
	//rect_one--------------
	Cube rect_1(1, 2, 70);
	rect_1.SetPos(5,0.9f,0);
	walls.add(rect_1);
	//front----------------------
	Cube rect_2(1, 2, 70);
	rect_2.SetPos(-5,0.9f,0);
	walls.add(rect_2);
	//curve_one-----------
	Cube curve_1(1, 2, 7);
	curve_1.SetPos(3.5,0.9f,37.5);
	curve_1.SetRotation(-30, vec3(0,1, 0));
	walls.add(curve_1);
	Cube curve_2(1, 2, 7);
	curve_2.SetPos(0.7, 0.9f, 42.5);
	curve_2.SetRotation(-30, vec3(0, 1, 0));
	walls.add(curve_2);
	Cube curve_3(1, 2, 8);
	curve_3.SetPos(2, 0.9f, 47.3);
	curve_3.SetRotation(60, vec3(0, 1, 0));
	walls.add(curve_3);
	Cube curve_3_1(1, 2, 8);
	curve_3_1.SetPos(7, 0.9f, 50.3);
	curve_3_1.SetRotation(59, vec3(0, 1, 0));
	walls.add(curve_3_1);
    //front------------------------
	Cube curve_4(1, 2, 13);
	curve_4.SetPos(-8.2, 0.9f,40.4);
	curve_4.SetRotation(-30, vec3(0, 1, 0));
	walls.add(curve_4);
	Cube curve_5(1, 2, 6);
	curve_5.SetPos(-11.5, 0.9f, 49);
	walls.add(curve_5);
	Cube curve_6(1, 2, 13);
	curve_6.SetPos(-5.7, 0.9f, 55);
	curve_6.SetRotation(60, vec3(0,1,0));
	walls.add(curve_6);
	Cube curve_6_1(1, 2, 8);
	curve_6_1.SetPos(-0.3, 0.9f, 58);
	curve_6_1.SetRotation(60, vec3(0, 1, 0));
	walls.add(curve_6_1);
   //------------------------


	//colisionador-----------------------------
	p2List_item<Cube>* item = walls.getFirst();
	while (item != NULL) {
		App->physics->AddBody(item->data, 0.0f);
		item = item->next;
	}






	

	s.size = vec3(5, 3, 1);
	s.SetPos(0, 2.5f, 20);

	sensor = App->physics->AddBody(s, 0.0f);
	sensor->SetAsSensor(true);
	sensor->collision_listeners.add(this);

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
	s.Render();

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

