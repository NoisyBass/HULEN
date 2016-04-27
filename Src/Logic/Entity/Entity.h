#ifndef LOGIC_ENTITY_H
#define LOGIC_ENTITY_H

#include "BaseSubsystems/Math.h"
#include "Logic/Maps/EntityID.h"
#include "Logic/Maps/Map.h"
#include "Logic/Maps/EntityFactory.h"
#include "Logic/Entity/GameObject.h"
#include "Logic/Entity/Component.h"
#include "Map/MapEntity.h"

// Mensaje
#include "Message.h"

#include <list>
#include <map>
#include <string>

// Declaraci�n de la clase
namespace Logic 
{
	/**
	Clase que representa una entidad en el entorno virtual. Las entidades
	son meros contenedores de componentes, y su funcionamiento depende
	de cu�les tenga. Adem�s, la clase contiene una serie de atributos que
	pueden ser accedidos desde los componentes (Id, nombre, etc.).
	<p>
	Tras la creaci�n de la entidad, donde se inicializan los valores de la
	entidad a su valor por defecto, se invocar� a su m�todo spawn() en el
	que se inicializar�n los atributos de la entidad con los valores leidos 
	del fichero del mapa. Tras esto, en alg�n momento, cuando se active
	el mapa se llamar� al m�todo activate() de la entidad. En este momento
	los componentes har�n visibles los componentes gr�ficos y dem�s ya que 
	apartir de ah� es cuando la entidad empieza su funci�n siendo actualizada 
	por el tick() en cada vuelta de bucle.

    @ingroup logicGroup
    @ingroup entityGroup

	@author David Llans�
	@date Agosto, 2010
	*/
	class CEntity 
	{
	protected:

		/**
		La factoria de entidades se encarga de crear las entidades
		pero cada game object es el responsable de eliminar sus entidades
		*/
		friend class CEntityFactory;
		friend class CGameObject;

		/**
		Constructor protegido de la clase (para crear CEntity debe
		utilizarse la factor�a CEntityFactory). El constructor
		no hace m�s que poner el identificador �nico de la entidad
		, pues la inicializaci�n efectiva se hace en el m�todo spawn().
		
		@param entityID Identificador �nico de la entidad.
		*/
		CEntity();

		/**
		Destructor de la clase. Es un m�todo protegido pues para
		eliminar CEntity debe utilizarse la factor�a
		CEntityFactory. El destructor invoca al destructor de
		cada componente.
		Cuando el destructor es invocado, �ste _ya ha sido desenganchado
		del mapa al que perteneci�_, por lo que los destructores de los
		componentes no pueden utilizar el mapa.
		*/
		~CEntity();

		/**
		Inicializaci�n del objeto Logic, utilizando la informaci�n extra�da de
		la entidad le�da del mapa (Map::CEntity). Avisar� a los componentes
		de la entidad para que se inicialicen.

		@param map Mapa Logic en el que se registrar� la entidad.
		@param entity Informaci�n de construcci�n de la entidad le�da del
		fichero de disco.
		@return Cierto si la inicializaci�n ha sido satisfactoria.
		*/
		bool spawn(CGameObject* gameObject, CMap *map, const Map::CEntity *entityInfo);

	public:

		/**
		Activa la entidad. Esto significa que el mapa ha sido activado.
		<p>
		El m�todo llama al activate() de todos los componentes para que
		se den por enterados y hagan lo que necesiten.
		 
		@return Devuelve true si todo fue bien.
		*/
		bool activate();

		/**
		Desactiva la entidad. Esto significa que el mapa ha sido desactivado.
		<p>
		El m�todo llama al deactivate() de todos los componentes para que
		se den por enterados y hagan lo que necesiten.
		*/
		void deactivate();

		/**
		Funci�n llamada en cada frame para que se realicen las funciones
		de actualizaci�n adecuadas.
		<p>
		Llamar� a los m�todos tick() de todos sus componentes.

		@param msecs Milisegundos transcurridos desde el �ltimo tick.
		*/
		void tick(float msecs);

		/**
		M�todo que a�ade un nuevo componente a la lista de la entidad.

		@param component Componente a a�adir.
		*/
		void addComponent(const std::string& name, IComponent* component);

		/**
		M�todo que quita un componente de la lista.

		El componente es eliminado de la lista de componentes de la
		entidad, pero <b>no</b> es desactivado ni eliminado (con delete);
		la responsabilidad de esa tarea se deja al invocante.

		@param component Componente a borrar.
		@return true si se borr� el componente (false si el componente
		no estaba en el objeto).
		*/
		bool removeComponent(const std::string& name);
		
		/**
		M�todo que destruye todos los componentes de una entidad.
		*/
		void destroyAllComponents();

		/**
		Recibe un mensaje que envia a todos los componentes de la lista menos 
		al componente que lo envia, si �ste se especifica en el segundo campo.

		@param message Mensaje a enviar.
		@param emitter Componente emisor, si lo hay. No se le enviar� el mensaje.
		@return true si al menos un componente acept� el mensaje
		*/
		bool emitMessage(const TMessage &message, IComponent* emitter = 0);
		
		/**
		Devuelve el nombre de la entidad.

		@return Nombre de la entidad.
		*/
		const std::string &getName() const { return _name; }

		/**
		Devuelve el blueprint de la entidad. Este atributo es leido de
		la entidad del mapa en spawn().

		@return Blueprint de la entidad.
		*/
		const std::string &getBlueprint() const { return _blueprint; }

		/**
		Establece la posici�n de la entidad. Avisa a los componentes
		del cambio.

		@param position Nueva posici�n.
		*/
		void setPosition(const Vector3 &position, IComponent* invoker = 0);

		/**
		Devuelve la posici�n de la entidad.
		<p>
		La posici�n es inicialmente le�da del mapa (si no aparece,
		se colocar� a (0, 0, 0)), aunque, obviamente, puede
		cambiar con el tiempo.

		@return Posici�n de la entidad en el entorno.
		*/
		Vector3 getPosition() const { return _position; }

		/**
		Indica si la entidad se encuentra activa.

		@return true si la entidad est� activa.
		*/
		bool isActivated() { return _activated; }

		CGameObject* getGameObject() const;

		IComponent* getComponent(const std::string& name);

		/**
		Direction
		*/
		enum ENTITY_DIRECTION {
			RIGHT = 1,
			LEFT = -1
		};

		int getDirection() { return _direction; };

		void setDirection(ENTITY_DIRECTION direction){ _direction = direction;}

	protected:

		/**
		Game object al que pertenece la entidad.
		*/
		CGameObject* _gameObject;

		/**
		Tipo para la lista de componetes.
		*/
		typedef std::map<std::string, IComponent*> TComponentMap;

		/**
		Lista de los componentes de la entidad.
		*/
		TComponentMap _components;

		/**
		Indica si la entidad est� activa.
		*/
		bool _activated;

		/**
		Tipo de la entidad declarado en el archivo blueprints.
		*/
		std::string _blueprint;

		/**
		Nombre de la entidad.
		*/
		std::string _name;

		/**
		Matriz de transformaci�n de la entidad. Contiene posici�n y orientaci�n.
		*/
		//Matrix4 _transform;

		bool _changeState;

		/**
		Entity direction.
		*/
		ENTITY_DIRECTION _direction;

		/**
		Entity position
		*/
		Vector3 _position;

	}; // class CEntity

} // namespace Logic

#endif // __Logic_Entity_H
