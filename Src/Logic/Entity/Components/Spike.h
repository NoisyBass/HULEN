#ifndef __Logic_Spike_H
#define __Logic_Spike_H

#include "Logic/Entity/Component.h"

namespace Logic 
{

	class CSpike : public IComponent
	{
		DEC_FACTORY(CSpike);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CSpike() : IComponent(){}

		/**
		Destructor (virtual); Quita de la escena y destruye la entidad gr�fica.
		*/
		virtual ~CSpike();
		
		/**
		Inicializaci�n del componente, utilizando la informaci�n extra�da de
		la entidad le�da del mapa (Maps::CEntity). Toma del mapa el atributo
		model con el modelo que se deber� cargar e invoca al m�todo virtual
		createGraphicsEntity() para generar la entidad gr�fica.

		@param entity Entidad a la que pertenece el componente.
		@param map Mapa L�gico en el que se registrar� el objeto.
		@param entityInfo Informaci�n de construcci�n del objeto le�do del
			fichero de disco.
		@return Cierto si la inicializaci�n ha sido satisfactoria.
		*/
		virtual bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		/**
		M�todo virtual que elige que mensajes son aceptados. Son v�lidos
		SET_TRANSFORM.

		@param message Mensaje a chequear.
		@return true si el mensaje es aceptado.
		*/
		virtual bool accept(const TMessage &message);

		/**
		M�todo virtual que procesa un mensaje.

		@param message Mensaje a procesar.
		*/
		virtual void process(const TMessage &message);

	protected:

		

	}; // class CSpike

	REG_FACTORY(CSpike);

} // namespace Logic

#endif // __Logic_Spike_H
