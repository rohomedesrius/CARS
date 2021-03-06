#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

int x = 0;

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(3, 1, 5);
	car.chassis_offset.Set(0, 1, 0);
	car.mass = 500.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 3000.0f;
	car.fuel = 3500.0f;

	//Car Camera
	distCamera = { -20.0f, 8.0f, -15.0f };

	// Wheel properties ---------------------------------------
	float connection_height = 1.4f;
	float wheel_radius1 = 0.5f;
	float wheel_radius2 = 0.8f;
	float wheel_width1 = 0.5f;
	float wheel_width2 = 1.0f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width1, connection_height, half_length - wheel_radius1);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius1;
	car.wheels[0].width = wheel_width1;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width1, connection_height, half_length - wheel_radius1);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius1;
	car.wheels[1].width = wheel_width1;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width1, connection_height, -half_length + wheel_radius1);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius1;
	car.wheels[2].width = wheel_width1;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width1, connection_height, -half_length + wheel_radius1);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius1;
	car.wheels[3].width = wheel_width1;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 0, 0);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

void ModulePlayer::Refill(){
	vehicle->info.fuel = vehicle->info.fuel + 750;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	//CAMERA-------------------------------------------------------------------------------
	int speedCam = 1;
	vec3 p = vehicle->getPos();
	btVector3 vehicle_vector = vehicle->vehicle->getForwardVector();
	vec3 f(vehicle_vector.getX(), vehicle_vector.getY(), vehicle_vector.getZ());

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN){
		distCamera = { 20.0f, 8.0f, 15.0f };
	}

	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN){
		distCamera = { -20.0f, 8.0f, -15.0f };
	}

	vec3 camera_new_position = { p.x + (f.x * distCamera.x), p.y + f.y + distCamera.y, p.z + (f.z * distCamera.z) };
	vec3 speed_camera = camera_new_position - App->camera->Position;
	vec3 reference(p.x, p.y, p.z);

	App->camera->Look(App->camera->Position + (speedCam * speed_camera), reference);
	//----------------------------------------------------------------------------------
	//Restart
	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN){
		vehicle->Stop();
		vehicle->SetRotation(0, 0, 0);
		vehicle->SetPos(0, 0, 0);
		App->scene_intro->laps = 0;
		App->scene_intro->lapTimes.clear();
		vehicle->info.fuel = 3500.0f;
		App->scene_intro->crono.Start();
	}
	
	turn = acceleration = brake = 0.0f;

	if (vehicle->info.fuel > 0 && App->scene_intro->laps <= 3){
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		{
			acceleration = MAX_ACCELERATION;
			vehicle->info.fuel = vehicle->info.fuel - 1.0f;
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			if (turn < TURN_DEGREES)
				turn += TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			if (turn > -TURN_DEGREES)
				turn -= TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		{
			acceleration = -MAX_ACCELERATION;
			vehicle->info.fuel = vehicle->info.fuel - 0.3f;
		}

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
		{
			brake = BRAKE_POWER;
		}

		if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		{
			vehicle->SetPos(vehicle->getPos().x, vehicle->getPos().y + 3, vehicle->getPos().z);

		}
		char title[80];
		sprintf_s(title, "%.1f Km/h, %.1f L of fuel, %.1is current time", vehicle->GetKmh(), vehicle->info.fuel, App->scene_intro->crono.Read() / 1000);
		App->window->SetTitle(title);
	}
	else if (vehicle->info.fuel <= 0){
			brake = BRAKE_POWER;
			char title[80];
			sprintf_s(title, "YOU HAVE RUN OUT OF FUEL, SORRY");
			App->window->SetTitle(title);
	}
	else if (App->scene_intro->laps >= 3){
		brake = BRAKE_POWER;
		char title[80];
		sprintf_s(title, "YOU HAVE COMPLETED THE RACE, BEST TIME %.1is", App->scene_intro->getBestLap() / 1000);
		App->window->SetTitle(title);
	}

	if (x == 100){
		App->scene_intro->sensorObjective = true;
		x = 0;
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();

	x++;

	return UPDATE_CONTINUE;
}



