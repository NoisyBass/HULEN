//---------------------------------------------------------------------------
// GameState.h
//---------------------------------------------------------------------------

/**
@file GameState.h

Contiene la declaraci�n del estado de juego.

@see Application::CApplicationState
@see Application::CGameState

@author David Llans�
@date Agosto, 2010
*/

#ifndef __Application_GameState_H
#define __Application_GameState_H

#include "ApplicationState.h"
#include "Logic\Events\Event.h"
#include "Sounds\api\SoundsResources.h"


// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Application 
{
	class CBaseApplication;
}

namespace Graphics 
{
	class CScene;
	class CCamera;
	class CEntity;
	class CStaticEntity;
	class CAnimatedEntity;
}

namespace CEGUI
{
	class Window;
}

namespace Application 
{
	/**
	Clase CGameState; representa el estado de juego de la aplicaci�n.
	Se encarga de la preparaci�n y la carga del mapa l�gico del juego.
	Tiene cableados los nombres de ficheros de mapa y de blueprints por
	simplicidad. En la activaci�n y desactivaci�n se encarga de activar
	y desactivar el m�dulo que se encarga de manejar al jugador leyendo 
	eventos de entrada de perif�ricos y de activar y desactivar el mapa 
	de Logic::CServer. En el tick() tambi�n se actualiza el m�dulo de 
	l�gica.
	<p>
	Como ejemplo de Ventana 2D para el GUI se tiene una peque�a ventana 
	que muestra el tiempo transcurrido. 
	Esto provoca que este estado sea CEGUI dependiente, lo cual no es 
	deseable. La aplicaci�n	deber�a ser independiente de las tecnolog�as 
	usadas.

	@ingroup applicationGroup

	@author David Llans�
	@date Agosto, 2010
	*/
	class CGameState : public CApplicationState 
	{
	public:
		/** 
		Constructor de la clase 
		*/
		CGameState(CBaseApplication *app) : CApplicationState(app), 
			_scene(0), _time(0), _isMapLoaded(false), _mapName("map.lua") 
		{
			_soundResources = Sounds::CSoundsResources::getSingletonPtr();

			_levels.insert({ 1, "sublevelOne.lua" });
			_levels.insert({ 2, "sublevelTwo.lua" });
			_levels.insert({ 3, "sublevelThree.lua" });
			_levels.insert({ 4, "sublevelFour.lua" });
			_levels.insert({ 5, "twoSublevelOne.lua" });
			_levels.insert({ 6, "twoSublevelTwo.lua" });
			_levels.insert({ 7, "twoSublevelThree.lua" });
			_levels.insert({ 8, "twoSublevelFour.lua" });
			_levels.insert({ 9, "twoSublevelFive.lua" });

			_levelsNames.insert({ "sublevelOne.lua", 1 });
			_levelsNames.insert({ "sublevelTwo.lua", 2 });
			_levelsNames.insert({ "sublevelThree.lua", 3 });
			_levelsNames.insert({ "sublevelFour.lua", 4 });
			_levelsNames.insert({ "twoSublevelOne.lua", 5 });
			_levelsNames.insert({ "twoSublevelTwo.lua", 6 });
			_levelsNames.insert({ "twoSublevelThree.lua", 7 });
			_levelsNames.insert({ "twoSublevelFour.lua", 8 });
			_levelsNames.insert({ "twoSublevelFive.lua", 9 });
		
		}

		/** 
		Destructor 
		*/
		virtual ~CGameState() { _soundResources = nullptr; }

		/**
		Funci�n llamada cuando se crea el estado (se "engancha" en la
		aplicaci�n, para que inicialice sus elementos.

		@return true si todo fue bien.
		*/
		virtual bool init();

		/**
		Funci�n llamada cuando se elimina ("desengancha") el
		estado de la aplicaci�n.
		*/
		virtual void release();

		/**
		Funci�n llamada por la aplicaci�n cuando se activa
		el estado.
		*/
		virtual void activate();

		/**
		Funci�n llamada por la aplicaci�n cuando se desactiva
		el estado.
		*/
		virtual void deactivate();

		/**
		Funci�n llamada por la aplicaci�n para que se ejecute
		la funcionalidad del estado.

		@param msecs N�mero de milisegundos transcurridos desde
		la �ltima llamada (o desde la �ctivaci�n del estado, en caso
		de ser la primera vez...).
		*/
		virtual void tick(float msecs);

		/**
		M�todo que cambia el fichero del mapa a cargar. 
		Comprueba que existe el mapa con el nombre que le llega por par�metro.  
		*/
		bool setMap(const std::string &mapname);

		// M�todos de CKeyboardListener
		
		/**
		M�todo que ser� invocado siempre que se pulse una tecla. 
		Ser� la aplicaci�n qui�n llame a este m�todo cuando el 
		estado est� activo. Esta clase NO se registra en el 
		InputManager sino que es la aplicaci�n quien lo hace y 
		delega en los estados.

		@param key C�digo de la tecla pulsada.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners.
		*/
		virtual bool keyPressed(GUI::TKey key);
		
		/**
		M�todo que ser� invocado siempre que se termine la pulsaci�n
		de una tecla. Ser� la aplicaci�n qui�n llame a este m�todo 
		cuando el estado est� activo. Esta clase NO se registra en
		el InputManager sino que es la aplicaci�n quien lo hace y 
		delega en los estados.

		@param key C�digo de la tecla pulsada.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners.
		*/
		virtual bool keyReleased(GUI::TKey key);

		// M�todos de CMouseListener
		
		/**
		M�todo que ser� invocado siempre que se mueva el rat�n. La
		aplicaci�n avisa de este evento al estado actual.

		@param mouseState Estado del rat�n cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners.
		*/
		virtual bool mouseMoved(const GUI::CMouseState &mouseState);
		
		/**
		M�todo que ser� invocado siempre que se pulse un bot�n. La
		aplicaci�n avisa de este evento al estado actual.

		@param mouseState Estado del rat�n cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners.
		*/
		virtual bool mousePressed(const GUI::CMouseState &mouseState);

		/**
		M�todo que ser� invocado siempre que se termine la pulsaci�n
		de un bot�n. La aplicaci�n avisa de este evento al estado 
		actual.

		@param mouseState Estado del rat�n cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners. 
		*/
		virtual bool mouseReleased(const GUI::CMouseState &mouseState);

		/**
		Metodo que utilizaremos para escuchar los eventos de muerte del player
		*/
		void playerListener(std::string &action);

	protected:

		/**
		Indica si el mapa se ha cargado o no.
		*/
		bool _isMapLoaded;

		/**
		Nombre del mapa a cargar.
		*/
		std::string _mapName;

		/**
		Escena del estado.
		*/
		Graphics::CScene* _scene;

		/**
		Ventana que muestra el tiempo de juego transcurrido.
		*/
		//CEGUI::Window* _timeWindow;

		/**
		Tiempo de juego en milisegundos.
		*/
		float _time;

		/**
		Player events.
		*/
		Logic::CEventSystem <Logic::Events::GameStateClass, Logic::Events::PlayerEventFunction> playerEvent;

		/**
		To play sounds
		*/
		Sounds::CSoundsResources* _soundResources;

		/**
		Game Levels
		We have two to get O(1) searches, and I think that doesn't matter 
		have another table wit these values, taht I don't think 
		*/
		std::unordered_map<int, std::string> _levels;
		std::unordered_map<std::string, int> _levelsNames;

	}; // CGameState

} // namespace Application

#endif //  __Application_GameState_H
