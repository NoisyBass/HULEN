#ifndef GUI_OBJECTS_CONTROLLER_H
#define GUI_OBJECTS_CONTROLLER_H

#include "InputManager.h"
#include "Logic\Entity\Entity.h"
#include <unordered_map>

namespace GUI
{
	
	class CObjectsController : public CKeyboardListener, public CMouseListener
	{
	public:

		/**
		Constructor.
		*/
		CObjectsController();

		/**
		Destructor.
		*/
		~CObjectsController();

		void addControllerObject(Logic::CEntity* entity);

		void removeControllerObject(const std::string &entityName);

		void activate();

		void deactivate();

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

		std::unordered_map<std::string, Logic::CEntity*> _entities;
		

	}; // class CSceneController

} // namespace GUI

#endif // GUI_OBJECTS_CONTROLLER_H
