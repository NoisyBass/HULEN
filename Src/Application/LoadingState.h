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
	del juego. Es muy sencilla y lo �nico que hace es cargar
	un layout de CEGUI al inicio y activarlo y desactivarlo cuando
	se activa o desactiva el estado (haci�ndo visible/invisible tambi�n
	el puntero del rat�n). Tambi�n asocia los eventos de los botones
	del men� a las funciones C++ que se deben invocar cuando los botones
	son pulsados.
	<p>
	Este estado es CEGUI dependiente, lo cual no es deseable, la aplicaci�n
	deber�a ser independiente de las tecnolog�as usadas.

	@ingroup applicationGroup

	@author David Llans�
	@date Agosto, 2010
	*/
	class CLoadingState : public CApplicationState, public AsyncTaskData, public OnAsyncTaskFinished
	{
	public:
		/**
		Constructor de la clase
		*/
		CLoadingState(CBaseApplication *app) : CApplicationState(app),
			_nextState(""), _asyncTask(NULL) , _isLoadingAysnc(false){}

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
		virtual void tick(unsigned int msecs);

		virtual void setNextState(const std::string & nextState);

		// M�todos correspondientes para la carga as�ncrona de las tareas.

		virtual void run();

		virtual void onAsyncTaskListener();

	private:

		/**
		Ventana CEGUI que muestra el men�.
		*/
		CEGUI::Window* _menuWindow;

		/**
		Referencia del siguiente estado a cargar.
		*/
		std::string _nextState;

		/*
		Tarea as�ncrona que gestiona el estado de Loading.
		*/
		AsyncTask * _asyncTask;

		/*
		Flag que indica si se est� realizando la carga as�ncrona.
		*/
		bool _isLoadingAysnc;

	}; // CLoadingState

} // namespace Application

#endif //  __Application_LoadingState_H
