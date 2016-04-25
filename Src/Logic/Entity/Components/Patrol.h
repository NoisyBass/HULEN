#ifndef LOGIC_PATROL_H
#define LOGIC_PATROL_H

#include "Logic/Entity/Component.h"

namespace Logic 
{
	class CPatrol : public IComponent
	{
		DEC_FACTORY(CPatrol);
	public:

		/**
		Constructor por defecto.
		*/
		CPatrol();
		
		/**
		Inicializaci�n del componente usando la descripci�n de la entidad que hay en 
		el fichero de mapa.
		*/
		bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo) override;

		bool activate() override;

		void deactivate() override;
		
		bool accept(const TMessage &message) override;
		
		void process(const TMessage &message) override;

		void tick(float msecs) override;

	protected:
		
		Vector3 _patrolPosition1;

		Vector3 _patrolPosition2;
	private:

		bool _arrivedToDestination;
		Vector3 _arrivedDestination;

	}; // class CPatrol

	REG_FACTORY(CPatrol);

} // namespace Logic

#endif // LOGIC_PATROL_H
