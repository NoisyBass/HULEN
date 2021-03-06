#ifndef GUI_SERVER_H
#define GUI_SERVER_H

#include "GUI/InputManager.h"
#include "GUI/PlayerController.h"
#include "GUI/LightController.h"
#include "GUI/SceneController.h"
#include "GUI/ObjectsController.h"
#include "Logic/Entity/Components/AvatarController.h"

namespace CEGUI
{
	class System;
}

// Declaraci�n de la clase
namespace GUI
{
	/**
	Servidor del m�dulo GUI que hace de interfaz con el usuario. Est� 
	implementado como un singlenton de inicializaci�n expl�cita. Sirve 
	para comunicar a CEGUI los eventos producidos ya as� hacer funcionar
	la interfaz gr�fica de usuario y permite que se establezca que entidad 
	es controlada por el GUI::CPlayerController. Este control se hace a 
	trav�s del componente Logic::CAvatarController.

	@ingroup GUIGroup

	@author David Llans�
	@date Agosto, 2010
	*/
	class CServer : public CKeyboardListener, public CMouseListener
	{
	public:

		/**
		Devuelve la �nica instancia de la clase CServer.
		
		@return �nica instancia de la clase CServer.
		*/
		static CServer* getSingletonPtr() {return _instance;}

		/**
		Inicializa la instancia

		@return Devuelve false si no se ha podido inicializar.
		*/
		static bool Init();

		/**
		Libera la instancia de CServer. Debe llamarse al finalizar la 
		aplicaci�n.
		*/
		static void Release();

		/**
		Devuelve la instancia de la clase GUI que se encarga de procesar los
		eventos de entrada para controlar al jugador por si se desea configurar
		externemante.

		@return Instancia de la clase GUI que controla al jugador.
		*/
		CPlayerController *getPlayerController() {return _playerController;}

		/**
		Devuelve la instancia de la clase GUI que se encarga de procesar los
		eventos de entrada para controlar a la luz por si se desea configurar
		externemante.

		@return Instancia de la clase GUI que controla a la luz.
		*/
		CLightController *getLightController() { return _lightController;}

		/**
		Devuelve la instancia de la clase GUI que se encarga de procesar los
		eventos de entrada para controlar la escena por si se desea configurar
		externemante.

		@return Instancia de la clase GUI que controla la escena.
		*/
		CSceneController *getSceneController() { return _sceneController; }

		CObjectsController* getObjectsController() { return _objectsController; }



		/***************************************************************
		M�todos de CKeyboardListener
		***************************************************************/
		
		/**
		M�todo que ser� invocado siempre que se pulse una tecla.

		@param key C�digo de la tecla pulsada.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners.
		*/
		bool keyPressed(TKey key);
		
		/**
		M�todo que ser� invocado siempre que se termine la pulsaci�n
		de una tecla.

		@param key C�digo de la tecla pulsada.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners.
		*/
		bool keyReleased(TKey key);
		
		/***************************************************************
		M�todos de CKeyboardListener
		***************************************************************/
		
		/**
		M�todo que ser� invocado siempre que se mueva el rat�n.

		@param mouseState Estado del rat�n cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners.
		*/
		bool mouseMoved(const CMouseState &mouseState);
		
		/**
		M�todo que ser� invocado siempre que se pulse un bot�n.

		@param mouseState Estado del rat�n cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners.
		*/
		bool mousePressed(const CMouseState &mouseState);

		/**
		M�todo que ser� invocado siempre que se termine la pulsaci�n
		de un bot�n.

		@param mouseState Estado del rat�n cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners.
		*/
		bool mouseReleased(const CMouseState &mouseState);

	protected:

		/**
		Constructor.
		*/
		CServer ();

		/**
		Destructor.
		*/
		~CServer();

		/**
		Segunda fase de la construcci�n del objeto. Sirve para hacer
		inicializaciones de la propia instancia en vez de inicializaciones 
		est�ticas.

		@return true si todo fue correctamente.
		*/
		bool open();

		/**
		Segunda fase de la destrucci�n del objeto. Sirve para hacer liberar 
		los recursos de la propia instancia, la liberaci�n de los recursos 
		est�ticos se hace en Release().
		*/
		void close();

		/**
		Clase GUI que se encarga de controlar al jugador.
		*/
		CPlayerController *_playerController;

		/**
		Clase GUI que se encarga de controlar a la luz.
		*/
		CLightController* _lightController;

		/**
		Clase GUI que se encarga de controlar la escena.
		*/
		CSceneController* _sceneController;

		/**
		Clase GUI que se encarga de controlar los objetos.
		*/
		CObjectsController* _objectsController;

		/**
		Sistema de la interfaz gr�fica de usuario CEGUI.
		*/
		CEGUI::System *_GUISystem;

	private:
		/**
		�nica instancia de la clase.
		*/
		static CServer* _instance;

	}; // class CServer

} // namespace GUI

#endif // __GUI_Server_H
