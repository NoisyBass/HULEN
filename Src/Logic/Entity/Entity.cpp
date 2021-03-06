#include "Entity.h"

#include <cassert>

namespace Logic 
{
	CEntity::CEntity() 
		: _gameObject(nullptr), _blueprint(""), _name(""), _type("Body"),
		_position(Vector3::ZERO), _activated(false), _direction(ENTITY_DIRECTION::RIGHT)
	{

	} // CEntity
	
	//---------------------------------------------------------

	CEntity::~CEntity()
	{
		destroyAllComponents();
		_gameObject = nullptr;

	} // ~CEntity
	
	//---------------------------------------------------------

	bool CEntity::spawn(CGameObject* gameObject, CMap *map, const Map::CEntity *entityInfo)
	{
		// Common properties
		_blueprint = entityInfo->getBlueprint();

		assert(entityInfo->hasAttribute("name") && "An entity has to have a name!!");
		_name = entityInfo->getStringAttribute("name");

		assert(entityInfo->hasAttribute("type") && "An entity has to have a type!!");
		_type = entityInfo->getStringAttribute("type");

		_gameObject = gameObject;

		if(entityInfo->hasAttribute("position"))
		{
			_position = entityInfo->getVector3Attribute("position");
		}

		if (entityInfo->hasAttribute("rollRotate"))
		{
			rollNode(entityInfo->getFloatAttribute("rollRotate"));
		}

		if (entityInfo->hasAttribute("direction"))
		{
			std::string direction = entityInfo->getStringAttribute("direction");
			if (direction == "right")
			{
				_direction = ENTITY_DIRECTION::RIGHT;
			}
			else if (direction == "left")
			{
				_direction = ENTITY_DIRECTION::LEFT;
				TMessage msg;
				msg._type = Message::ROLL_ENTITY_NODE;
				msg.setArg<int>(("degrees"), 180);
				emitMessage(msg);
			}
		}

		// Entity components spawn
		TComponentMap::const_iterator it;

		bool correct = true;
		for (it = _components.begin(); it != _components.end() && correct; ++it){
			correct = it->second->spawn(it->first, this, map, entityInfo) && correct;
		}
			

		return correct;

	} // spawn

	void CEntity::init(CGameObject* gameObject, CMap *map, const Map::CEntity *entityInfo)
	{
		// Entity components spawn
		TComponentMap::const_iterator it;

		for (it = _components.begin(); it != _components.end(); ++it){
			it->second->init(it->first, this, map, entityInfo);
		}

	}

	//---------------------------------------------------------

	void CEntity::rollNode(float degrees){
		TMessage msg;
		msg._type = Message::ROLL_ENTITY_NODE;
		msg.setArg<int>(("degrees"), degrees);
		emitMessage(msg);
	} // rotateNode

	bool CEntity::activate() 
	{	
		// Activamos los componentes
		TComponentMap::const_iterator it;

		// Solo si se activan todos los componentes correctamente nos
		// consideraremos activados.
		_activated = true;

		for (it = _components.begin(); it != _components.end(); ++it)
		{
				_activated = it->second->activate() && _activated;
		}

		return _activated;

	} // activate

	//---------------------------------------------------------

	void CEntity::deactivate(bool isDeletingMap)
	{
		TComponentMap::const_iterator it;

		// Desactivamos los componentes
		for (it = _components.begin(); it != _components.end(); ++it)
		{
			it->second->deactivate(isDeletingMap);
		}

		_activated = false;

	} // deactivate

	//---------------------------------------------------------

	void CEntity::tick(float msecs)
	{
		TComponentMap::const_iterator it;

		for( it = _components.begin(); it != _components.end(); ++it )
			it->second->tick(msecs);

	} // tick

	//---------------------------------------------------------

	void CEntity::addComponent(const std::string& name, IComponent* component)
	{
		_components.emplace(name, component);
		component->setEntity(this);

	} // addComponent

	//---------------------------------------------------------

	bool CEntity::removeComponent(const std::string& name)
	{
		TComponentMap::const_iterator it = _components.find(name);
		IComponent* c;

		if (it != _components.end())
		{
			c = it->second;
			_components.erase(name);
			delete c;

			return true;
		}

		return false;

	} // removeComponent

	//---------------------------------------------------------

	void CEntity::destroyAllComponents()
	{
		IComponent* c;
		for (auto it = _components.begin(); it != _components.end(); ++it)
		{
			c = it->second;
			delete c;
		}
			
		_components.clear();
		
	} // destroyAllComponents

	//---------------------------------------------------------

	bool CEntity::emitMessage(const TMessage &message, IComponent* emitter)
	{
		// Interceptamos los mensajes que adem�s de al resto de los
		// componentes, interesan a la propia entidad.
		TMessage m;
		Vector3 receiverPosition, senderPosition;
		switch(message._type)
		{
		case Message::SET_POSITION:
			_position = message.getArg<Vector3>("newPosition");
			break;
		}

		TComponentMap::const_iterator it;
		// Para saber si alguien quiso el mensaje.
		bool anyReceiver = false;
		for( it = _components.begin(); it != _components.end(); ++it )
		{
			// Al emisor no se le envia el mensaje.
			if( emitter != it->second )
				anyReceiver = it->second->set(message) || anyReceiver;
		}
		return anyReceiver;

	} // emitMessage

	//---------------------------------------------------------

	void CEntity::setPosition(const Vector3 &position, IComponent* invoker)  
	{
		_position = position;

		// Avisamos a los componentes del cambio.
		TMessage message;
		message._type = Message::SET_POSITION;
		message.setArg<Vector3>(std::string("newPosition"), position);

		emitMessage(message,invoker);

	} // setPosition

	//---------------------------------------------------------

	CGameObject* CEntity::getGameObject() const
	{
		return _gameObject;

	} // getGameObject

	//---------------------------------------------------------

	IComponent* CEntity::getComponent(const std::string& name)
	{
		TComponentMap::const_iterator it = _components.find(name);

		if (it != _components.end())
			return it->second;

		return nullptr;
	}

} // namespace Logic
