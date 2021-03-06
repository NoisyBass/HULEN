#ifndef LOGIC_GAME_OBJECT_H
#define LOGIC_GAME_OBJECT_H

#include "Logic\Entity\Entity.h"
#include "Logic\Entity\Component.h"
#include "Logic\Maps\Map.h"

#include <unordered_map>

namespace Logic
{
	namespace GameObject
	{
		enum TState
		{
			BODY,
			SHADOW,
			BOTH
		};
	}

	class CGameObject
	{
	public:

		CGameObject(TEntityID gameObjectID);

		~CGameObject();

		bool spawn(CMap *map, const Map::CEntity *entityInfo);

		CEntity* getBody() const;

		CEntity* getShadow() const;

		void setBody(CEntity* body);

		void setShadow(CEntity* shadow);

		bool activate();

		void deactivate(bool isDeletingMap);

		bool isActivated();

		void tick(float msecs);

		void addComponent(const std::string& name, IComponent* component);

		bool removeComponent(const std::string& name);

		void destroyAllComponents();

		bool emitMessage(const TMessage &message, IComponent* emitter = 0);

		/**
		M�todo que indica si el game object es o no el jugador.
		Seguro que hay formas mejores desde el punto de vista de
		dise�o de hacerlo, pero esta es la m�s r�pida: la entidad
		con la descripci�n de la entidad tiene esta descripci�n que
		establece en el spawn().

		@return true si la entidad es el jugador.
		*/
		bool isPlayer() { return _isPlayer; }

		/**
		Devuelve true si la luz que se controla por medio del
		raton se esta utilizando.
		*/
		bool isLight() { return _isLight; }

		/**
		Devuelve el identificador �nico del game object.

		@return Identificador.
		*/
		Logic::TEntityID getGameObjectID() const;

		/**
		Devuelve el mapa donde est� el game object.

		@return Puntero al mapa que contiene el game object.
		*/
		CMap *getMap();

		/**
		Devuelve el nombre del game object.

		@return Nombre del game object.
		*/
		const std::string &getName() const;

		/**
		Devuelve el blueprint del game object. Este atributo es leido de
		la entidad del mapa en spawn().

		@return Blueprint del game object.
		*/
		const std::string &getBlueprint() const;

		/**
		Devuelve el nombre del material por defecto para una entidad, ya 
		sea de luz, o de sombra.
		*/
		const std::string& getDefaultMaterial(const std::string type) const;

		/**
		Devuelve la posici�n de la entidad que esta activa, en caso de que ambas lo esten
		devuelve la posici�n del body.
		*/
		Vector3 getPosition() const;

		/**
		Devuelve el componente
		*/
		IComponent* getComponent(const std::string& name);

		/**
		Devuelve el componente de los hijos, siendo state SHADOW o BODY.
		*/
		IComponent* getComponentInChildren(const GameObject::TState state, const std::string& name);

		GameObject::TState getState() const { return _state;  }

	protected:

		/**
		Clase amiga que puede modificar los atributos (en concreto se
		usa para modificar el mapa.
		*/
		friend class CMap;

		friend class CPlayerManager;

		CEntity* _body;
		CEntity* _shadow;

		bool _activated;

		/**
		Identificador �nico del game object.
		*/
		Logic::TEntityID _gameObjectID;

		/**
		Tipo para la lista de componetes.
		*/
		typedef std::map<std::string, IComponent*> TComponentMap;

		/**
		Lista de los componentes del game object.
		*/
		TComponentMap _components;

		/**
		Tipo del game object declarado en el archivo blueprints.
		*/
		std::string _blueprint;

		/**
		Nombre del game object.
		*/
		std::string _name;

		/**
		Mapa l�gico donde est� el game object.
		*/
		Logic::CMap *_map;

		/**
		Atributo que indica si lael game object es el jugador; por defecto
		es false a no ser que se lea otra cosa de los atributos.
		*/
		bool _isPlayer;

		/**
		Atributo que indica si la entidad es la luz que movemos con el raton.
		por defecto es false.
		*/
		bool _isLight;

		/**
		Atributo que indica el estado en el que se encuentra el game object.
		Puede ser BODY, SHADOW o BOTH
		*/
		GameObject::TState _state;

		/**
		Nombre del material por defecto para las sombras.
		*/
		std::string _defaultShadowMaterial;

		/**
		Nombre del material por defecto para el cuerpo.
		*/
		std::string _defaultBodyMaterial;

	}; // class CGameObject

} // namespace Logic

#endif // LOGIC_GAME_OBJECT_H