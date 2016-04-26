#ifndef LOGIC_MAP_H
#define LOGIC_MAP_H

#include "Map/MapEntity.h"
#include "Logic/Maps/EntityID.h"
#include "Logic/Entity/Message.h"
#include "Graphics/Scene.h"

#include <map>
#include <unordered_map>

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Logic 
{
	class CEntity;
	class CGameObject;
}

// Declaraci�n de la clase
namespace Logic
{
	/**
	Clase que representa un mapa l�gico.
	<p>
	Esta clase se encarga de almacenar todas las entidades del mapa, tanto 
	aquellas que tienen representaci�n gr�fica y se ven como entidades
	puramente l�gicas. Gestiona la activaci�n y desactivaci�n de �stas y
	tiene tambi�n m�todos para buscar entidades, tanto por su nombre como 
	por su tipo y por su identificador.

	@ingroup logicGroup
	@ingroup mapGroup

	@author David Llans�
	@date Agosto, 2010
	*/
	class CMap
	{
	public:

		/**
		M�todo factor�a que carga los prefabs. Tras el parseo de
		todas las entidades del mapa mediante CMapParser, genera todas las
		entidades con CEntityFactory.

		@param filename Nombre del archivo a cargar.
		@return Prefabs generado.
		*/
		static bool createPrefabsFromFile(const std::string &prefabFileName);

		/**
		M�todo factor�a que carga un mapa de fichero. Tras el parseo de
		todas las entidades del mapa mediante CMapParser, genera todas las
		entidades con CEntityFactory.

		@param filename Nombre del archivo a cargar.
		@return Mapa generado.
		*/
		static CMap* createEntitiesFromFile(const std::string &filename);

		/**
		Comprueba si existe un fichero con el nombre indicado en el par�metro.

		@param filename Nombre del archivo que se quiere comprobar que existe.
		@return si existe o no el fichero.
		*/
		static bool checkFileExists(const std::string &filename);

		static Map::CEntity* getGameObjectFromPrefab(const std::string &prefabName);

		static Map::CEntity* getBodyFromPrefab(const std::string &prefabName);

		static Map::CEntity* getShadowFromPrefab(const std::string &prefabName);

		/**
		Crea una nueva instancia de un prefab.
		*/
		static CGameObject* instantiatePrefab(const std::string& prefabToInstantiate, const std::string& nameToNewInstance,
			const std::string& bodyPosition = "{0, 0, 0}", const std::string& shadowPosition = "{0, 0, 0}");

		/**
		Constructor.

		@param name Nombre que se le da a este mapa.
		*/
		CMap(const std::string &name);

		/**
		Destructor.
		*/
		~CMap();
		
		/**
		Activa el mapa. Invocar� al m�todo activate() de todas las 
		entidades para que se den por enterados y hagan lo que necesiten.
		 
		@return Devuelve true al invocador si todas las entidades se
		activaron sin problemas.
		*/
		bool activate();

		/**
		Desactiva el mapa. Invocar� al m�todo deactivate() de todas las 
		entidades para que se den por enterados y hagan lo que necesiten.
		*/
		void deactivate();

		/**
		Funci�n llamada en cada frame para que se realicen las funciones
		de actualizaci�n adecuadas.
		<p>
		Llamar� a los m�todos tick() de todas las entidades.

		@param msecs Milisegundos transcurridos desde el �ltimo tick.
		*/
		void tick(float msecs);

		/**
		A�ade una nueva entidad al mapa. Si la entidad ya estaba incluida
		no se hace nada.

		@param entity Entidad a a�adir.
		*/
		void addGameObject(CGameObject *gameObject);

		/**
		Elimina una entidad del mapa. Si la entidad no estaba incluida
		no se hace nada. La funci�n desactiva previamente la entidad si
		�sta se encontraba activa.

		@note El mapa no se hace responsable de eliminar (con delete) la
		entidad.

		@param entity Entidad a eliminar.
		*/
		void removeGameObject(CGameObject *gameObject);

		/**
		Elimina y destruye todas las entidades del mapa dejando la lista 
		de entidades vac�a.
		*/
		void destroyAllGameObjects();

		/**
		Recupera una entidad del mapa a partir de su ID.

		@param entityID ID de la entidad a recuperar.
		@return Entidad con el ID pedido, NULL si no se encuentra.
		*/
		CGameObject* getGameObjectByID(TEntityID gameObjectID);

		/**
		Recupera una entidad del mapa a partir de su nombre.

		@param name nombre de la entidad a recuperar.
		@param start Entidad desde la que se debe empezar a buscar
		en la lista. �til si se tienen varias entidades con el mismo
		nombre y desde fuera se quiere ir accediendo a ellas una a una.
		Si no se especifica se empieza desde el principio.
		@return Entidad con el nombre pedido, NULL si no se encuentra.
		*/
		CGameObject* getGameObjectByName(const std::string &name, CGameObject *start = 0);

		/**
		Recupera una entidad del mapa a partir de su tipo.

		@param type nombre del tipo de la entidad a recuperar.
		@param start Entidad desde la que se debe empezar a buscar
		en la lista. �til si se tienen varias entidades del mismo tipo
		y desde fuera se quiere ir accediendo a ellas una a una.
		Si no se especifica se empieza desde el principio.
		@return Entidad con el nombre pedido, NULL si no se encuentra.
		*/
		CGameObject* getGameObjectByBlueprint(const std::string &blueprint, CGameObject *start = 0);

		/**
		Devuelve la escena gr�fica correspondiente a este mapa.

		@return Escena con las entidades gr�ficas.
		*/
		Graphics::CScene *getScene() {return _scene;}

		/**
		Envia un mensaje a todas los gameobjects existentes.
		*/
		void sendMessageToGameObjects(Logic::TMessage m);

		/**
		Destruye todos los prefabs que se han creado.
		*/
		static void destroyAllPrefabs();


	private:

		

		/**
		Tipo tabla de entidades de mapa.
		*/
		typedef std::map<TEntityID,CGameObject*> TGameObjectMap;

		/**
		tabla con las entidades del mapa localizadas por su ID.
		*/
		TGameObjectMap _gameObjectMap;

		/**
		Nombre del mapa.
		*/
		std::string _name;

		/**
		Referencia al mapa con las entidades. lo guardamos para poder
		instaciar nuevas entidades con los prefabs.
		*/
		static CMap* _entitiesMap;

		/**
		Escena gr�fica donde se encontrar�n las representaciones gr�ficas de
		las entidades.
		*/
		Graphics::CScene* _scene;

		struct TPrefab{
			Map::CEntity* gameObject;
			Map::CEntity* bodyEntity;
			Map::CEntity* shadowEntity;
		};

		typedef std::unordered_map<std::string, TPrefab*> TPrefabList;

		static TPrefabList _prefabList;

	}; // class CMap

} // namespace Logic

#endif // __Logic_Map_H
