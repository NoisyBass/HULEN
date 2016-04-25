#ifndef MOVECONTROLLER_H
#define MOVECONTROLLER_H

#include "Logic/Entity/Component.h"
#include "Logic/Entity/Entity.h"

//declaraci�n de la clase
namespace Logic 
{

	class CMoveController : public IComponent
	{
		DEC_FACTORY(CMoveController);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CMoveController() : IComponent(), _speed(0.01), _gravity(0.015) {}
	
		/**
		Inicializaci�n del componente, utilizando la informaci�n extra�da de
		la entidad le�da del mapa (Maps::CEntity). Toma del mapa el atributo
		speed que indica a la velocidad a la que se mover� el jugador.

		@param entity Entidad a la que pertenece el componente.
		@param map Mapa L�gico en el que se registrar� el objeto.
		@param entityInfo Informaci�n de construcci�n del objeto le�do del
			fichero de disco.
		@return Cierto si la inicializaci�n ha sido satisfactoria.
		*/
		virtual bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		/**
		M�todo llamado en cada frame que actualiza el estado del componente.
		
		Se encarga de mover la entidad en cada vuelta de ciclo cuando es
		necesario (cuando est� andando o desplaz�ndose lateralmente).

		@param msecs Milisegundos transcurridos desde el �ltimo tick.
		*/
		virtual void tick(float msecs);

		/**
		M�todo virtual que elige que mensajes son aceptados. Son v�lidos
		CONTROL.

		@param message Mensaje a chequear.
		@return true si el mensaje es aceptado.
		*/
		virtual bool accept(const TMessage &message);

		/**
		M�todo virtual que procesa un mensaje.

		@param message Mensaje a procesar.
		*/
		virtual void process(const TMessage &message);

		void nextPosition(const Vector3 &position);

	private:
		void calculateDirection();

		bool destinationReached();

		void walkLeft();

		void walkRight();

		void stop();

	protected:

		/**
		Atributo que indica la magnitud de velocidad de la entidad.
		*/
		float _speed;

		/**
		Gravedad
		*/
		float _gravity;

		Vector3 _positionToGo;

		Vector3 _nextPositionToGo;


	}; // class CAvatarController

	REG_FACTORY(CMoveController);

} // namespace Logic

#endif // MOVECONTROLLER_H
