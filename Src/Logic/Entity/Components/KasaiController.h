#ifndef LOGIC_KASAI_CONTROLLER_H
#define LOGIC_KASAI_CONTROLLER_H

#include "Logic/Entity/Component.h"

namespace Logic
{
	/**
	Este componente es el encargado de mover a Kasai, la luz que puede ser
	controlada por el jugador. El componente nos permite cambiar su posici�n o
	hacerla visible o invisible.
	*/
	class CKasaiController : public IComponent
	{
		DEC_FACTORY(CKasaiController);
	public:

		/**
		Constructor por defecto
		*/
		CKasaiController();

		/**
		Inicializaci�n del componente, utilizando la informaci�n extra�da de
		la entidad le�da del mapa (Maps::CEntity).

		@param entity Entidad a la que pertenece el componente.
		@param map Mapa L�gico en el que se registrar� el objeto.
		@param entityInfo Informaci�n de construcci�n del objeto le�do del
		fichero de disco.
		@return Cierto si la inicializaci�n ha sido satisfactoria.
		*/
		bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo) override;

		/**
		M�todo que activa el componente; invocado cuando se activa
		el mapa donde est� la entidad a la que pertenece el componente.

		@return true si todo ha ido correctamente.
		*/
		bool activate() override;

		/**
		M�todo que desactiva el componente; invocado cuando se
		desactiva el mapa donde est� la entidad a la que pertenece el
		componente. Se invocar� siempre, independientemente de si estamos
		activados o no.
		*/
		void deactivate() override;

		/**
		M�todo virtual que elige que mensajes son aceptados. Son v�lidos
		KASAI_MOVE, KASAI_SET_VISIBLE.

		@param message Mensaje a chequear.
		@return true si el mensaje es aceptado.
		*/
		bool accept(const TMessage &message) override;

		/**
		M�todo virtual que procesa un mensaje.

		@param message Mensaje a procesar.
		*/
		void process(const TMessage &message) override;

	protected:

		/**
		Atributo para saber si la entidad esta visible.
		*/
		bool _isVisible;

		/**
		Nombre del player.
		*/
		std::string _playerName;

		/**
		Referencia al player.
		*/
		CGameObject* _player;

	}; // class CKasaiController

	REG_FACTORY(CKasaiController);

} // namespace Logic

#endif // LOGIC_KASAI_CONTROLLER_H