#include "ChargeInteractuable.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Entity/GameObject.h"
#include "Map/MapEntity.h"
#include "Logic/Entity/Components/PhysicEntity.h"
#include "Logic/Server.h"
#include "Sounds\api\SoundsResources.h"

namespace Logic
{
	IMP_FACTORY(CChargeInteractuable);

	CChargeInteractuable::CChargeInteractuable()
		: IComponent(), _canInteract(false), _volume(0), _pitch(0)
	{

	} // Cinteractuable

	CChargeInteractuable::~CChargeInteractuable()
	{

	} // ~CInteractuable

	bool CChargeInteractuable::spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(name, entity, map, entityInfo))
			return false;

		_graphics = (CGraphics*)(_entity->getComponent("CGraphics"));

		/**
		Sounds
		*/
		Sounds::CSoundsResources* sounds = Sounds::CSoundsResources::getSingletonPtr();

		if (entityInfo->hasAttribute("chargeImpactSound"))
			_sound = entityInfo->getStringAttribute("chargeImpactSound");

		if (entityInfo->hasAttribute("chargeImpactVolume"))
			_volume = entityInfo->getFloatAttribute("chargeImpactVolume");

		if (entityInfo->hasAttribute("chargeImpactPitch"))
			_pitch = entityInfo->getFloatAttribute("chargeImpactPitch");


		return true;

	} // spawn

	bool CChargeInteractuable::accept(const TMessage &message)
	{
		//std::cout << "Message type: " << message._type << std::endl;
		return message._type == Message::ON_CONTACT ||
			message._type == Message::INTERACTUABLE ||
			message._type == Message::DEATH_PLANE;

	} // accept

	void CChargeInteractuable::process(const TMessage &message)
	{
		TMessage msg;
		CEntity* contactEntity;
		switch (message._type)
		{
		case Message::ON_CONTACT:
			contactEntity = message.getArg<CEntity*>("entity");
			if (contactEntity->getBlueprint() == "World" || contactEntity->getBlueprint() == "LightLever")
			{
				msg._type = Message::DISABLE_SIMULATION;
				_entity->emitMessage(msg);
				
				Sounds::CSoundsResources* sounds = Sounds::CSoundsResources::getSingletonPtr();
				sounds->playAndDestroySound(_sound, _volume, _pitch, _entity->getPosition(), Vector3(0,0,0));
			}
			break;
		case Message::INTERACTUABLE:
			
			if (message.getArg<bool>("canInteract")){
				_canInteract = true;
				_graphics->setMaterial("Charge_on");
			}
			else{
				_canInteract = false;
				_graphics->setMaterial("Charge_off");
			}
			break;
		case Message::DEATH_PLANE:
			msg._type = Message::PICK_FROM_DEATH_CHARGE;
			msg.setArg<CEntity*>("entityCharge", _entity);
			Logic::CServer::getSingletonPtr()->getPlayer()->emitMessage(msg);
			break;
		default:
			break;
		}

	} // process

} // namespace Logic