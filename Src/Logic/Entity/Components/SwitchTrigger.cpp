/**
@file SwitchTrigger.cpp

Contiene la declaraci�n del componente que envia un mensaje SWITCH a otra
entidad cuando recibe un mensaje TOUCHED / UNTOUCHED.
 
@see Logic::CSwitchTrigger
@see Logic::IComponent

@author David Llans�
@date Octubre, 2010
*/

#include "SwitchTrigger.h"

#include "Logic/Entity/Entity.h"
#include "Logic\Entity\GameObject.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

namespace Logic 
{
	IMP_FACTORY(CSwitchTrigger);
	
	//---------------------------------------------------------

	bool CSwitchTrigger::spawn(const std::string& name, CEntity *entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if(!IComponent::spawn(name, entity,map,entityInfo))
			return false;

		assert(entityInfo->hasAttribute("target") && "Hay que especificar el atributo target");

		_targetName = entityInfo->getStringAttribute("target");

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CSwitchTrigger::activate()
	{
		// Obtenemos la entidad objetivo a lanzar.
		// DUDA
		if (_targetName.length())
			_target = _entity->getGameObject()->getMap()->getGameObjectByName(_targetName)->getBody();
			//_target = _entity->getMap()->getEntityByName(_targetName);

		return true;

	} // activate
	
	//---------------------------------------------------------

	void CSwitchTrigger::deactivate(bool isDeletingMap)
	{
		_target = 0;

	} // deactivate
	
	//---------------------------------------------------------

	bool CSwitchTrigger::accept(const TMessage &message)
	{
		return message._type == Message::TOUCHED ||
			message._type == Message::UNTOUCHED;

	} // accept
	
	//---------------------------------------------------------

	void CSwitchTrigger::process(const TMessage &message)
	{
		switch(message._type)
		{
		case Message::TOUCHED:
		case Message::UNTOUCHED:
			if(_target)
			{
				TMessage m;
				m._type = Message::SWITCH;
				if (message._type == Message::TOUCHED) {
					m.setArg<int>(std::string("switch"), 1);
				} else {
					m.setArg<int>(std::string("switch"), 0);
				}
				_target->emitMessage(m);
			}
			break;
		}

	} // process


} // namespace Logic

