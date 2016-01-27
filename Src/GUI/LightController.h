#ifndef __GUI_LightController_H
#define __GUI_LightController_H

#include "InputManager.h"

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Logic 
{
	class CEntity;
}

// Declaraci�n de la clase
namespace GUI
{
	
	class CLightController : public CKeyboardListener, public CMouseListener
	{
	public:

		/**
		Constructor.
		*/
		CLightController();

		/**
		Destructor.
		*/
		~CLightController();

		/**
		Establece el componente de la luz al que enviaremos acciones 
		de movimiento en funci�n de las teclas pulsadas y el movimiento 
		del rat�n.

		@param controlledLight Componente al que enviaremos acciones de 
		movimiento en funci�n de las teclas pulsadas y el movimiento del 
		rat�n.
		*/
		void setControlledLight(Logic::CEntity *controlledLight) 
										{_controlledLight = controlledLight;} 

		/**
		Activa la la clase, se registra en el CInputManager y as� empieza a 
		escuchar eventos.
		*/
		void activate();

		/**
		Desctiva la la clase, se deregistra en el CInputManager y deja de 
		escuchar eventos.
		*/
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

		/**
		Luz a la que enviaremos acciones de movimiento en
		funci�n de las teclas pulsadas y el movimiento del rat�n.
		*/
		Logic::CEntity *_controlledLight;

	}; // class CLightController

} // namespace GUI

#endif // __GUI_LightController_H
