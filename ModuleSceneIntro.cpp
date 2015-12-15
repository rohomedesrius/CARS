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
	//------------------------
	Cube curve_2(1, 2, 7);
	curve_2.SetPos(0.7, 0.9f, 42.5);
	curve_2.SetRotation(-30, vec3(0, 1, 0));
	walls.add(curve_2);
	//------------------------
	Cube curve_3(1, 2, 8);
	curve_3.SetPos(2, 0.9f, 47.3);
	curve_3.SetRotation(60, vec3(0, 1, 0));
	walls.add(curve_3);
	//------------------------
	Cube curve_4(1, 2, 8);
	curve_4.SetPos(7, 0.9f, 50.3);
	curve_4.SetRotation(59, vec3(0, 1, 0));
	walls.add(curve_4);
	//------------------------
	Cube curve_5(1, 2, 13);
	curve_5.SetPos(13.2, 0.9f, 57.3);
	curve_5.SetRotation(30, vec3(0, 1, 0));
	walls.add(curve_5);
	//------------------------
	Cube curve_6(1, 2, 10);
	curve_6.SetPos(17.5, 0.9f, 67.3);
	curve_6.SetRotation(15, vec3(0, 1, 0));
	walls.add(curve_6);

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

