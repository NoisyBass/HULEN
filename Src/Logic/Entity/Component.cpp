#include "Component.h"

#include <cassert>

namespace Logic 
{
	IComponent::IComponent() 
		: _entity(nullptr), _gameObject(nullptr), _active(true)
	{

	} // IComponent

	//IComponent::~IComponent()
	//{
	//	~CCommunicationPort();
	//	_entity = nullptr;
	//	_gameObject = nullptr;

	//} // ~IComponent

	bool IComponent::spawn(const std::string& name, CEntity *entity, CMap *map, const Map::CEntity *entityInfo)
	{
		_name = name;
		_entity = entity;
		return true;

	} // spawn

	bool IComponent::spawn(const std::string& name, CGameObject* gameObject, CMap *map, const Map::CEntity *entityInfo)
	{
		_name = name;
		_gameObject = gameObject;
		return true;
	}
	
	//---------------------------------------------------------

	void IComponent::tick(unsigned int msecs)
	{
		processMessages();

	} // tick

	CEntity* IComponent::getEntity() const
	{ 
		assert(_entity && "El componente no esta asignado a una entidad");
		return _entity; 

	} // getEntity

	CGameObject* IComponent::getGameObject() const
	{ 
		assert(_gameObject && "El componente no esta asignado a un game object");
		return _gameObject; 

	} // getGameObject

	void IComponent::setEntity(CEntity* entity) 
	{ 
		_entity = entity; 

	} // setEntity

	void IComponent::setGameObject(CGameObject* gameObject) 
	{ 
		_gameObject = gameObject; 

	} // setGAmeObject

} // namespace Logic
