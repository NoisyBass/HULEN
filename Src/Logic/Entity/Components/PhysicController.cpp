/**
@file PhysicController.cpp

Contiene la implementaci�n del componente que se utiliza para representar jugadores y enemigos en
el mundo f�sico usando character controllers.

@see Logic::CPhysicController
@see Logic::CPhysicEntity
@see Logic::IPhysics

@author Antonio S�nchez Ruiz-Granados
@date Noviembre, 2012
*/

#include "PhysicController.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Entity/Components/AvatarController.h"
#include "Map/MapEntity.h"
#include "Physics/Server.h"
#include "Physics/Conversions.h"

#include <PxPhysicsAPI.h>

using namespace Logic;
using namespace Physics;
using namespace physx; 

IMP_FACTORY(CPhysicController);

//---------------------------------------------------------

CPhysicController::CPhysicController() : IPhysics(), _controller(NULL), 
_movement(0, 0, 0), _falling(false), _fsm(nullptr)
{
	_server = CServer::getSingletonPtr();
}

//---------------------------------------------------------

CPhysicController::~CPhysicController() 
{
	if (_controller) {
		_controller->release();
		_controller = NULL;
	}

	_server = NULL;
} 

//---------------------------------------------------------

bool CPhysicController::spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo)
{
	// Invocar al m�todo de la clase padre
	if(!IComponent::spawn(name, entity,map,entityInfo))
		return false;

	// Crear el character controller asociado al componente
	_controller = createController(entityInfo);

	return true;
}

bool CPhysicController::activate()
{
	// Si tenemos un componente responsable del agente de IA tendremos que actualizar su informaci�n
	_fsm = (Logic::CFSMEntity*)(_entity->getComponent("CFSMEntity"));

	if (_fsm)
	{
		_fsm->setValue<bool>("touching_entity", false);
	}

	return true;
}

void CPhysicController::deactivate(bool isDeletingMap)
{

}

//---------------------------------------------------------

bool CPhysicController::accept(const TMessage &message)
{
	return message._type == Message::AVATAR_WALK;
} 

//---------------------------------------------------------

void CPhysicController::process(const TMessage &message)
{
	TMessage m;
	Vector3 receiverPosition, senderPosition;
	switch(message._type)
	{
	case Message::AVATAR_WALK:
		// Anotamos el vector de desplazamiento para usarlo posteriormente en 
		// el m�todo tick. De esa forma, si recibimos varios mensajes AVATAR_WALK
		// en el mismo ciclo s�lo tendremos en cuenta el �ltimo.
		_movement = message.getArg<Vector3>("movement");
		break;
	}

}

void CPhysicController::setMovement(const Vector3& movement)
{
	_movement = movement;
}

void CPhysicController::sendState(CPhysicController* receiver)
{
	//std::cout << "PhysicController mandando estado..." << std::endl;
	receiver->_movement = _movement;
	receiver->_falling = _falling;
	receiver->_controller->setPosition(PxExtendedVec3(_controller->getPosition().x,
													  _controller->getPosition().y,
													  receiver->_controller->getPosition().z)); // La z no cambia
}

//---------------------------------------------------------

void CPhysicController::tick(float msecs)
{
	// Llamar al m�todo de la clase padre (IMPORTANTE).
	IComponent::tick(msecs);

	// Actualizar la posici�n y orientaci�n de la entidad l�gica usando la 
	// informaci�n proporcionada por el motor de f�sica	
	_entity->setPosition(_server->getControllerPosition(_controller), this);

	// Si estamos cayendo modificar el vector de desplazamiento para simular el 
	// efecto de la gravedad. Lo hacemos de manera sencilla y pero poco realista.
	//_movement += msecs * Vector3(0.0f, -1.0f, 0.0f);

	// Intentamos mover el controller a la posici�n recibida en el �ltimo mensaje 
	// de tipo AVATAR_WALK. 
	unsigned flags = _server->moveController(_controller, _movement, msecs);

	// Actualizamos el flag que indica si estamos cayendo
	_falling = !(flags & PxControllerFlag::eCOLLISION_DOWN);

	if (flags & PxControllerFlag::eCOLLISION_UP)
	{
		CAvatarController* controller = (CAvatarController*)(_entity->getComponent("CAvatarController"));
		controller->_jump = false;
		controller->_currentHeight = 0.0f;
	}

	// Ponemos el movimiento a cero
	_movement = Vector3::ZERO;
}

//---------------------------------------------------------

PxCapsuleController* CPhysicController::createController(const Map::CEntity *entityInfo)
{
	// Obtenemos la posici�n de la entidad. Inicialmente colocaremos el controller
	// un poco por encima del suelo, porque si lo ponemos justo en el suelo a veces
	// lo atraviesa en el primer ciclo de simulaci�n.
	Vector3 position = _entity->getPosition() + Vector3(0, 0.5f, 0);
	
	// Leer el volumen de colisi�n del controller. Por ahora s�lo admitimos c�psulas.
	std::string shape = "capsule";
	if (entityInfo->hasAttribute("physic_shape")) {
		shape = entityInfo->getStringAttribute("physic_shape");
		assert(shape == "capsule");
	}

	// Leer el radio de la c�psula
	assert(entityInfo->hasAttribute("physic_radius"));
	float radius = entityInfo->getFloatAttribute("physic_radius");

	// Leer la altura de la c�psula
	assert(entityInfo->hasAttribute("physic_height"));
	float height = entityInfo->getFloatAttribute("physic_height");

	// Crear el controller de tipo c�psula
	return _server->createCapsuleController(position, radius, height, this);
} 

//---------------------------------------------------------

void CPhysicController::onTrigger(IPhysics *otherComponent, bool enter)
{

}

void CPhysicController::onContact(IPhysics *otherComponent)
{

}

//---------------------------------------------------------

void CPhysicController::onShapeHit (const PxControllerShapeHit &hit)
{
	// Si chocamos contra una entidad est�tica no hacemos nada
	//PxRigidDynamic* actor = hit.shape->getActor()->isRigidDynamic();
	PxRigidActor* actor = hit.shape->getActor();

	if(!actor)
		return;

	IPhysics *otherComponent = (IPhysics *)actor->userData;

	if (_fsm && otherComponent->getEntity()->getBlueprint() != "World")
	{
		_fsm->setValue<bool>("touching_entity", true);
		_fsm->setValue<std::string>("touched_entity_bp", otherComponent->getEntity()->getBlueprint());
		_fsm->setValue<std::string>("touched_go_name", otherComponent->getEntity()->getGameObject()->getName());
	}


	// Si chocamos contra una entidad cinem�tica mandamos
	// un mensaje a la entidad contra la que nos hemos
	// chocado
	PxRigidDynamic* dynamicActor = actor->isRigidDynamic();
	if (dynamicActor && _server->isKinematic(dynamicActor)){
		TMessage msg;
		msg._type = Message::SHAPE_HIT;
		otherComponent->getEntity()->emitMessage(msg);
		return;
	}
	
	// Aplicar una fuerza a la entidad en la direcci�n del movimiento
	//actor->addForce(hit.dir * hit.length * 1000.0f);
}

//---------------------------------------------------------

void CPhysicController::onControllerHit (const PxControllersHit &hit)
{
	IPhysics *otherComponent = (IPhysics *)hit.other->getActor()->userData;

	if (_fsm && otherComponent->getEntity()->isActivated())
	{
		_fsm->setValue<bool>("touching_entity", true);
		_fsm->setValue<std::string>("touched_entity_bp", otherComponent->getEntity()->getBlueprint());
		_fsm->setValue<std::string>("touched_go_name", otherComponent->getEntity()->getGameObject()->getName());
	}
}