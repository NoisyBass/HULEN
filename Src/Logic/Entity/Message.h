#ifndef LOGIC_MESSAGE_H
#define LOGIC_MESSAGE_H

#include <string>
#include <unordered_map>

#include <boost/variant/variant.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/get.hpp>

#include "BaseSubsystems/Math.h"

// Predeclaraciones
namespace Logic {
	class CEntity;
};

namespace Logic
{
	/**
	Namespace para los tipos de mensajes posibles.
	*/
	namespace Message
	{
		enum TMessageType
		{
			DESTROY,
			SET_POSITION,
			SET_ANIMATION,
			STOP_ANIMATION,
			CONTROL,
			AVATAR_WALK,
			KINEMATIC_MOVE,
			TOUCHED,
			UNTOUCHED,
			SWITCH,
			DAMAGED,
			MOUSE_POINTER_MOVE,
			LIGHT_SET_POSITION,
			LIGHT_SET_COLOR,
			PLAYER_ENTER_LIGHT,
			PLAYER_OUT_LIGHT,
			PLAYER_CHANGE_STATE,
			SEND_STATE,
			RECEIVE_ANIMATION_STATE,
			RECEIVE_AVATAR_STATE,
			RECEIVE_PHYSIC_STATE,
			RECEIVE_ENTITY_STATE,
			PLAYER_EVENT,
			AMBIENT_LIGHT_SET_FOR_DEBUG,
			AMBIENT_LIGHT_SET_REAL_MATERIAL,
			SHAPE_HIT,
			PICK_CHARGE,
			PUT_CHARGE,
			PICK_FROM_DEATH_CHARGE,
			ARRIVED_TO_DESTINATION,
			ROLL_ENTITY_NODE,
			INTERACTUABLE,
			LEVER_INTERACTUABLE,
			PLAYER_LEVER_INTERACT,
			CHARGE_ERASED,
			HOW_MANY_CHARGES,
			DEATH_PLANE,
			ON_CONTACT,
			ANIMATION_WITHOUT_LOOP_STARTED,
			ANIMATION_WITHOUT_LOOP_FINISHED,
			GROUND_COLLISION,
			PLAYER_DEATH,
			DISABLE_SIMULATION,
			PLAYER_DEATH_BY_DEATH_PLANE,
			CHANGE_MATERIAL,
		};

		/**
		Tipo del argumento de un mensaje
		*/
		typedef boost::variant<Matrix4, int, float, bool, std::string, Vector3, CEntity*> TMessageArg;
	}


	/**
	Contiene el tipo de datos de un mensaje. Cada mensaje cuenta
	con un mapa de argumentos, que se diferencian con un id unico,
	de tipo string. De esta manera cada mensaje puede tener tantos
	argumentos como sea necesario, y cada uno puede estar identificado
	con un nombre que sea intuitivo.

	Cada argumento esta representado por una union de los distintos
	tipos que podremos necesitar dependiendo del tipo de mensaje.
	Una union es un tipo especial de clase que puede contener datos
	solo para uno de sus miembros a la vez.
	Para esto nos hemos decantado por usar la clase Boost.Variant
	(Para mas info http://www.boost.org/doc/libs/1_59_0/doc/html/variant.html)

	@ingroup logicGroup
	@ingroup entityGroup

	@author
	@date
	@ingroup grupoEntidad
	*/
	typedef struct
	{
		/**
		Tipo del mensaje.
		*/
		Message::TMessageType _type;

		/**
		Mapa con los argumentos del mensaje
		Cada argumento esta identificado por un nombre unico.
		Por ejemplo, si estamos ante el caso de un mensaje de tipo
		SET_ANIMATION, en la funcion process correspondiente llamaremos a
		Graphics::AnimatedEntity::setAnimation(const std::string& anim, bool loop),
		por lo que necesitaremos dos argumentos, y, para mantener la consistencia
		y que los nombres sean intuitivos, llamaremos a nuestros argumentos
		"animation" y "loop"
		*/
		std::unordered_map<std::string, Message::TMessageArg> _args;

		template<typename T>
		T getArg(const std::string& id) const
		{
			return boost::get<T>(_args.at(id));
		}

		template<typename T>
		void setArg(const std::string& id, const T& value)
		{
			_args.emplace(std::make_pair(id, value));
		}

		bool existArg(const std::string& id) const
		{
			return _args.find(id) != _args.end();
		}

	} TMessage;

} // namespace Logic

#endif // LOGIC_MESSAGE_H