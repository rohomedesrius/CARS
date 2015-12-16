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
	laps =  0;

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
	//-------------------------------------------
	Cube curve_2(1, 2, 7);
	curve_2.SetPos(5.7, 0.9f, 42.5);
	curve_2.SetRotation(-30, vec3(0, 1, 0));
	walls.add(curve_2);
	//-------------------------------------------
	Cube curve_3(1, 2, 8);
	curve_3.SetPos(7, 0.9f, 47.3);
	curve_3.SetRotation(60, vec3(0, 1, 0));
	walls.add(curve_3);
	//-------------------------------------------
	Cube curve_4(1, 2, 8);
	curve_4.SetPos(12, 0.9f, 50.3);
	curve_4.SetRotation(59, vec3(0, 1, 0));
	walls.add(curve_4);
	//-------------------------------------------
	Cube curve_5(1, 2, 13);
	curve_5.SetPos(18.2, 0.9f, 57.3);
	curve_5.SetRotation(30, vec3(0, 1, 0));
	walls.add(curve_5);
	//-------------------------------------------
	Cube curve_6(1, 2, 10);
	curve_6.SetPos(22.5, 0.9f, 67.3);
	curve_6.SetRotation(15, vec3(0, 1, 0));
	walls.add(curve_6);
	//-------------------------------------------
	Cube curve_7(1, 2, 10);
	curve_7.SetPos(23.9, 0.9f, 76.5);
	walls.add(curve_7);
	//-------------------------------------------
	Cube curve_8(1, 2, 10);
	curve_8.SetPos(22.9, 0.9f, 85.3);
	curve_8.SetRotation(-15, vec3(0, 1, 0));
	walls.add(curve_8);
	//-------------------------------------------
	Cube curve_9(1, 2, 13);
	curve_9.SetPos(19.9, 0.9f, 96.2);
	curve_9.SetRotation(-15, vec3(0, 1, 0));
	walls.add(curve_9);
    //front------------------------
	Cube curve_1f(1, 2, 13);
	curve_1f.SetPos(-8.2, 0.9f,40.4);
	curve_1f.SetRotation(-30, vec3(0, 1, 0));
	walls.add(curve_1f);
	//-------------------------------------------
	Cube curve_2f(1, 2, 6);
	curve_2f.SetPos(-11.5, 0.9f, 49);
	walls.add(curve_2f);
	//-------------------------------------------
	Cube curve_3f(1, 2, 13);
	curve_3f.SetPos(-5.7, 0.9f, 55);
	curve_3f.SetRotation(60, vec3(0,1,0));
	walls.add(curve_3f);
	//-------------------------------------------
	Cube curve_4f(1, 2, 8);
	curve_4f.SetPos(-0.4, 0.9f, 58);
	curve_4f.SetRotation(60, vec3(0, 1, 0));
	walls.add(curve_4f);
	//-------------------------------------------
	Cube curve_5f(1, 2, 10);
	curve_5f.SetPos(5.4, 0.9f, 64.1);
	curve_5f.SetRotation(30, vec3(0, 1, 0));
	walls.add(curve_5f);
	//-------------------------------------------
	Cube curve_6f(1, 2, 9);
	curve_6f.SetPos(9, 0.9f, 72.5);
	curve_6f.SetRotation(15, vec3(0, 1, 0));
	walls.add(curve_6f);
	//-------------------------------------------
	Cube curve_7f(1, 2, 5);
	curve_7f.SetPos(10.2, 0.9f, 79.2);
	walls.add(curve_7f);
	//-------------------------------------------
	Cube curve_8f(1, 2, 6);
	curve_8f.SetPos(9.5, 0.9f, 84.5);
	curve_8f.SetRotation(-15, vec3(0, 1, 0));
	walls.add(curve_8f);
	//-------------------------------------------
	Cube curve_9f(1, 2, 7);
	curve_9f.SetPos(7.9, 0.9f, 90.5);
	curve_9f.SetRotation(-15, vec3(0, 1, 0));
	walls.add(curve_9f);
	
	//rect_two-----------------
	Cube rect_2(1, 2, 32);
	rect_2.SetPos( 5.6, 0.9f, 109.9);
	rect_2.SetRotation(-60, vec3(0, 1, 0));
	walls.add(rect_2);
	//front-------------------------------------------
	Cube rect_2f(1, 2, 30);
	rect_2f.SetPos(-5.7, 0.9f, 100.9);
	rect_2f.SetRotation(-60, vec3(0, 1, 0));
	walls.add(rect_2f);

	//curve_2
	Cube curve_10(1, 2, 12);
	curve_10.SetPos(-11, 0.9f, 123);
	curve_10.SetRotation(-30, vec3(0, 1, 0));
	walls.add(curve_10);
	//front-------------------------------------------
	Cube curve_10f(1, 2, 13);
	curve_10f.SetPos(-21.9, 0.9f, 114);
	curve_10f.SetRotation(-30, vec3(0, 1, 0));
	walls.add(curve_10f);

	//rect_three---------------------------------
	Cube rect_3(1, 2, 19);
	rect_3.SetPos(-22, 0.9f, 133);
	rect_3.SetRotation(-60, vec3(0, 1, 0));
	walls.add(rect_3);
	//front-------------------------------------------
	Cube rect_3f(1, 2, 19);
	rect_3f.SetPos(-33, 0.9f, 124);
	rect_3f.SetRotation(-60, vec3(0, 1, 0));
	walls.add(rect_3f);

	//curve_three-------------------------------------
	Cube curve_11(1, 2, 20);
	curve_11.SetPos(-38.3, 0.9f,140);
	curve_11.SetRotation(-75, vec3(0, 1, 0));
	walls.add(curve_11);
	//------------------------------------------------
	Cube curve_12(1, 2, 7);
	curve_12.SetPos(-50.5, 0.9f, 142.5);
	curve_12.SetRotation(-90, vec3(0, 1, 0));
	walls.add(curve_12);
	//------------------------------------------------
	Cube curve_13(1, 2, 20);
	curve_13.SetPos(-63, 0.9f, 142.5);
	curve_13.SetRotation(-90, vec3(0, 1, 0));
	walls.add(curve_13);
	//------------------------------------------------
	Cube curve_14(1, 2, 20);
	curve_14.SetPos(-80, 0.9f, 138);
	curve_14.SetRotation(-120, vec3(0, 1, 0));
	walls.add(curve_14);
	//------------------------------------------------
	Cube curve_15(1, 2, 12);
	curve_15.SetPos(-89.7, 0.9f, 128.5);
	curve_15.SetRotation(-160, vec3(0, 1, 0));
	walls.add(curve_15);

	//front-------------------------------------------
	Cube curve_11f(1, 2, 12);
	curve_11f.SetPos(-46.4, 0.9f, 130);
	curve_11f.SetRotation(-75, vec3(0, 1, 0));
	walls.add(curve_11f);
	//------------------------------------------------
	Cube curve_12f(1, 2, 17);
	curve_12f.SetPos(-60, 0.9f, 131.4);
	curve_12f.SetRotation(-90, vec3(0, 1, 0));
	walls.add(curve_12f);
	//------------------------------------------------
	Cube curve_13f(1, 2, 12);
	curve_13f.SetPos(-73.5, 0.9f, 128.5);
	curve_13f.SetRotation(-120, vec3(0, 1, 0));
	walls.add(curve_13f);
	//------------------------------------------------
	Cube curve_14f(1, 2, 5);
	curve_14f.SetPos(-79.4, 0.9f, 123.5);
	curve_14f.SetRotation(-160, vec3(0, 1, 0));
	walls.add(curve_14f);

	//rect_four----------------------------------------
	Cube rect_4(1, 2, 65);
	rect_4.SetPos(-73.3, 0.9f, 95.9);
	rect_4.SetRotation(-215, vec3(0, 1, 0));
	walls.add(rect_4);
	//front--------------------------------------------
	Cube rect_4f(1, 2, 55);
	rect_4f.SetPos(-64.7, 0.9f, 98.9);
	rect_4f.SetRotation(-215, vec3(0, 1, 0));
	walls.add(rect_4f);

	//curve_four---------------------------------------
	Cube curve_16(1, 2, 13);
	curve_16.SetPos(-57.9, 0.9f,63.9);
	curve_16.SetRotation(30, vec3(0, 1, 0));
	walls.add(curve_16);
	//-------------------------------------------------
	Cube curve_17(1, 2, 10);
	curve_17.SetPos(-60.9, 0.9f, 54.9);
	walls.add(curve_17);
	//-------------------------------------------------
	Cube curve_18(1, 2, 10);
	curve_18.SetPos(-57, 0.9f, 48);
	curve_18.SetRotation(120, vec3(0, 1, 0));
	walls.add(curve_18);
	//front--------------------------------------------
	Cube curve_15f(1, 2, 10);
	curve_15f.SetPos(-47.2, 0.9f, 73.9);
	curve_15f.SetRotation(-215, vec3(0, 1, 0));
	walls.add(curve_15f);
	//-------------------------------------------------
	Cube curve_16f(1, 2, 15);
	curve_16f.SetPos(-47.9, 0.9f, 63);
	curve_16f.SetRotation(26, vec3(0, 1, 0));
	walls.add(curve_16f);
	//-------------------------------------------------
	Cube curve_17f(1, 2, 15);
	curve_17f.SetPos(-45, 0.9f, 53);
	curve_17f.SetRotation(120, vec3(0, 1, 0));
	walls.add(curve_17f);


	//rect_five---------------------------------------
	Cube rect_5(1, 2, 150);
	rect_5.SetPos(-53, 0.9f, -29.1);
	walls.add(rect_5);
	//front-------------------------------------------
	Cube rect_5f(1, 2, 150);
	rect_5f.SetPos(-39, 0.9f, -25);
	walls.add(rect_5f);

	
	//curve_five--------------------------------------
	Cube curve_19(1, 2, 15);
	curve_19.SetPos(-50.5, 0.9f, -110);
	curve_19.SetRotation(160, vec3(0, 1, 0));
	walls.add(curve_19);
	//-------------------------------------------------
	Cube curve_20(1, 2, 40);
	curve_20.SetPos(-45.1, 0.9f, -125);
	curve_20.SetRotation(160, vec3(0, 1, 0));
	walls.add(curve_20);
	//--------------------------------------------------
	Cube curve_21(1, 2, 40);
	curve_21.SetPos(-19.5, 0.9f, -137);
	curve_21.SetRotation(70, vec3(0, 1, 0));
	walls.add(curve_21);
	//--------------------------------------------------
	Cube curve_22(1, 2, 13);
	curve_22.SetPos(4, 0.9f, -128.5);
	curve_22.SetRotation(70, vec3(0, 1, 0));
	walls.add(curve_22);
	//front------------------------------------------------
	Cube curve_19f(1, 2, 10);
	curve_19f.SetPos(-37.3, 0.9f, -104.5);
	curve_19f.SetRotation(160, vec3(0, 1, 0));
	walls.add(curve_19f);
	//-------------------------------------------------------
	Cube curve_20f(1, 2, 15);
	curve_20f.SetPos(-33.1, 0.9f, -116);
	curve_20f.SetRotation(160, vec3(0, 1, 0));
	walls.add(curve_20f);
	//------------------------------------------------------
	Cube curve_21f(1, 2, 10);
	curve_21f.SetPos(-26.5, 0.9f, -121);
	curve_21f.SetRotation(70, vec3(0, 1, 0));
	walls.add(curve_21f);
	//------------------------------------------------------
	Cube curve_22f(1, 2, 6);
	curve_22f.SetPos(-7.5, 0.9f, -119);
	curve_22f.SetRotation(69, vec3(0, 1, 0));
	walls.add(curve_22f);


	//rect_6-----------------------------------------------
	Cube rect_6(1, 2, 100);
	rect_6.SetPos(10, 0.9f, -76);
	walls.add(rect_6);
	//-----------------------------------------------------
	Cube rect_6f(1, 2, 70);
	rect_6f.SetPos(-5, 0.9f, -83);
	walls.add(rect_6f);

	
	//----------------------------------------------------PIT-------------------------
	Cube pit_1(1, 2, 70);
	pit_1.SetPos(-22, 0.9f, -84.5);
	walls.add(pit_1);
	//---------------------------------------------------------------------------------
	Cube pit_2(1, 2, 23);
	pit_2.SetPos(-14, 0.9f, -41.9);
	pit_2.SetRotation(49, vec3(0, 1, 0));
	walls.add(pit_2);
	//front----------------------------------------------------------------------------
	Cube pit_1f(1, 2, 60);
	pit_1f.SetPos(-10.5, 0.9f, -90);
	walls.add(pit_1f);
	//---------------------------------------------------------------------------------
	Cube pit_2f(1, 2, 13);
	pit_2f.SetPos(-8, 0.9f, -54.9);
	pit_2f.SetRotation(25, vec3(0, 1, 0));
	walls.add(pit_2f);
	
	
	
	//colisionador-----------------------------
	p2List_item<Cube>* item = walls.getFirst();
	while (item != NULL) {
		App->physics->AddBody(item->data, 0.0f);
		item = item->next;
	}
	
	//Sensor Meta
	s.size = vec3(15, 3, 0);
	s.SetPos(2.5, 2, 10);
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

int ModuleSceneIntro::getBestLap(){
	return 0;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body1->type == SensorType::objective){
		if (laps != 3)
		crono.Start();
		laps++;
	}
}



