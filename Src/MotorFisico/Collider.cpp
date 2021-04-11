#include "Collider.h"
#include "PhysxEngine.h"
#include <PxRigidDynamic.h>
#include <PxRigidActor.h>
#include <PxShape.h>
#include <PxRigidDynamic.h>
#include <PxRigidStatic.h>
#include <PxPhysics.h>
#include <PxPhysicsAPI.h>
#include <PxRigidActor.h>

#define GetPhysx() PhysxEngine::getPxInstance()->getScene()->getPhysics()

Collider::Collider(bool isTrigger) :_isTrigger(isTrigger)
{
	//Hace falta meterle un material
	physx::PxMaterial* gMaterial = GetPhysx().createMaterial(0.5f, 0.5f, 0.5f);
	_mShape = PhysxEngine::getPxInstance()->getScene()->getPhysics().createShape(
		physx::PxSphereGeometry(1.0f), gMaterial, true);
	//_mActor->attachShape(PxBoxGeometry());
	position = new physx::PxVec3(0, 0, 0);
}

Collider::~Collider()
{
	if (position != nullptr) delete position;
}

void Collider::setBoxCollider(int x, int y, int z)
{
}

void Collider::setSphereCollider(int radius)
{
}

void Collider::setStatic()
{
}

void Collider::setDynamic()
{
}

void Collider::setKinematic()
{
	/* //Para generar un objeto de la escena kinematico
PxRigidDynamic* meshActor = getPhysics().createRigidDynamic(PxTransform(1.0f));
PxShape* meshShape;
if(meshActor)
{
	meshActor->setRigidDynamicFlag(PxRigidDynamicFlag::eKINEMATIC, true);

	PxTriangleMeshGeometry triGeom;
	triGeom.triangleMesh = triangleMesh;
	meshShape = PxRigidActorExt::createExclusiveShape(*meshActor,triGeom,
		defaultMaterial);
	getScene().addActor(*meshActor);
}
*/
}

void Collider::setColliderProperties()
{
}

void Collider::setTriggerProperties()
{
}

/*
Broad-Phase callback
Es el callback al que se va a llamar en caso de que alg�n elemento se salga de los l�mites del mundo
El usuario debe determinar lo que hacer con el callback y los objetos que se detecten que se han salido
*/

/* //Para que una shape pase o deje de participar en las colisiones de una escena
void disableShapeInContactTests(PxShape* shape)
{
	shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE,bool);
}
*/

/*  //Para activar/desactivar que la shape participe en scene query tests (raycasts)
void disableShapeInSceneQueryTests(PxShape* shape)
{
	shape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE,false);
}
*/

/*
//Para que el actor no participe en la simulacion (la simulaci�n no lo va a mover y solo se va a mover manualmente)
PxActorFlag::eDISABLE_SIMULATION).
*/