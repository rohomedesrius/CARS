#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "Bullet\src\btBulletDynamicsCommon.h"

// ----------------------------------------------------------------------------
VehicleInfo::~VehicleInfo()
{
	//if(wheels != NULL)
		//delete wheels;
}

// ----------------------------------------------------------------------------
PhysVehicle3D::PhysVehicle3D(btRigidBody* body, btRaycastVehicle* vehicle, const VehicleInfo& info) : PhysBody3D(body), vehicle(vehicle), info(info)
{
}

// ----------------------------------------------------------------------------
PhysVehicle3D::~PhysVehicle3D()
{
	delete vehicle;
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Render()
{
	Cylinder wheel;

	wheel.color = Blue;

	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.radius = info.wheels[0].radius;
		wheel.height = info.wheels[0].width;

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);

		wheel.Render();
	}

	Cube chassis(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);
	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());

	chassis.transform.M[12] += offset.getX();
	chassis.transform.M[13] += offset.getY();
	chassis.transform.M[14] += offset.getZ();

	Cube frontchassis(info.chassis_size.x*0.30f, info.chassis_size.y, info.chassis_size.z*0.2f);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&frontchassis.transform);
	btQuaternion q2 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset2(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z + 3);
	offset2 = offset2.rotate(q2.getAxis(), q2.getAngle());

	frontchassis.transform.M[12] += offset2.getX();
	frontchassis.transform.M[13] += offset2.getY();
	frontchassis.transform.M[14] += offset2.getZ();

	Cube frontchassis2(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z*0.2f);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&frontchassis2.transform);
	btQuaternion q3 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset3(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z + 4);
	offset3 = offset3.rotate(q3.getAxis(), q3.getAngle());

	frontchassis2.transform.M[12] += offset3.getX();
	frontchassis2.transform.M[13] += offset3.getY();
	frontchassis2.transform.M[14] += offset3.getZ();

	Cube driver(info.chassis_size.x*0.30f, info.chassis_size.y, info.chassis_size.z*0.70f);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&driver.transform);
	btQuaternion q4 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset4(info.chassis_offset.x, info.chassis_offset.y + 0.65, info.chassis_offset.z - 1.5);
	offset4 = offset4.rotate(q4.getAxis(), q4.getAngle());

	driver.transform.M[12] += offset4.getX();
	driver.transform.M[13] += offset4.getY();
	driver.transform.M[14] += offset4.getZ();

	Cube aileron(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z*0.2f);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&aileron.transform);
	btQuaternion q5 = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset5(info.chassis_offset.x, info.chassis_offset.y + 1.65, info.chassis_offset.z - 2.75);
	offset5 = offset5.rotate(q5.getAxis(), q5.getAngle());

	aileron.transform.M[12] += offset5.getX();
	aileron.transform.M[13] += offset5.getY();
	aileron.transform.M[14] += offset5.getZ();

	chassis.color = Blue;
	frontchassis.color = Green;
	frontchassis2.color = Green;
	driver.color = Green;
	aileron.color = Blue;

	chassis.Render();
	frontchassis.Render();
	frontchassis2.Render();
	driver.Render();
	aileron.Render();

	
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::ApplyEngineForce(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].drive == true)
		{
			vehicle->applyEngineForce(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Brake(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Turn(float degrees)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].steering == true)
		{
			vehicle->setSteeringValue(degrees, i);
		}
	}
}

// ----------------------------------------------------------------------------
float PhysVehicle3D::GetKmh() const
{
	return vehicle->getCurrentSpeedKmHour();
}

vec3 PhysVehicle3D::getPos(){
	btTransform t = vehicle->getRigidBody()->getWorldTransform();
	btVector3 v = t.getOrigin();
	vec3 ret; ret.Set(v.getX(), v.getY(), v.getZ());
	return ret;
}