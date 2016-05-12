//---------------------------------------------------------------------------
// LoadingState.h
//---------------------------------------------------------------------------

/**
@file LoadingState.h

Contiene la declaraci�n del estado de men�.

@see Application::CApplicationState
@see Application::CLoadingState

@author Daniel Ruiz
@date Abril, 2016
*/

#ifndef __Application_LoadingState_H
#define __Application_LoadingState_H

#include "ApplicationState.h"
#include "AsyncTask.h"

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Application
{
	class CBaseApplication;
}

namespace CEGUI
{
	class EventArgs;
	class Window;
}

namespace Application
{
	/**
	Como su nombre indica, esta clase es la clase de la pantalla de carga
	del juego. 

	@author Daniel Ruiz
	@date Abril, 2016
	*/
	class CLoadingState : public CApplicationState
	{
	public:

		/**
		Constructor de la clase
		*/
		CLoadingState(CBaseApplication *app) : CApplicationState(app),
			_nextState(""){}

		/**
		Destructor
		*/
		virtual ~CLoadingState();

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
		Cambia el estado que se va a cargar tras el estado de loading.
		*/
		virtual void setNextState(const std::string & nextState);

	private:

		/**
		Ventana CEGUI que muestra el men�.
		*/
		CEGUI::Window* _menuWindow;

		/**
		Referencia del siguiente estado a cargar.
		*/
		std::string _nextState;

		/**
		Flag que indica si el LoadingState est� cargando algo. Se usa para no bloquear la pantalla de loading.
		*/
		bool _isLoading;

	}; // CLoadingState

} // namespace Application

#endif //  __Application_LoadingState_H
