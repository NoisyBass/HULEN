//---------------------------------------------------------------------------
// LoadingState.cpp
//---------------------------------------------------------------------------

/**
@file LoadingState.cpp

Contiene la implementaci�n del estado de la pantalla de loading.

@see Application::CApplicationState
@see Application::CLoadingState

@author Daniel Ruiz
@date Abril, 2016
*/

#include "LoadingState.h"

#include "GUI/Server.h"
#include "Sounds\Server.h"

// Incluimos las tareas as�ncronas
#include "AsyncTask.h"

#include <CEGUI/CEGUI.h>

#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

namespace Application {

	CLoadingState::~CLoadingState()
	{
	} // ~CLoadingState

	//--------------------------------------------------------

	bool CLoadingState::init()
	{
		CApplicationState::init();

		// Cargamos la ventana que muestra el men�
		_menuWindow = CEGUI::WindowManager::getSingletonPtr()->loadLayoutFromFile("Loading.layout");

		return true;

	} // init

	//--------------------------------------------------------

	void CLoadingState::release()
	{

		CApplicationState::release();

	} // release

	//--------------------------------------------------------

	void CLoadingState::activate()
	{
		CApplicationState::activate();

		// Activamos la ventana que nos muestra el men� y activamos el rat�n.
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().setRootWindow(_menuWindow);
		_menuWindow->setVisible(true);
		_menuWindow->activate();
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().getMouseCursor().show();

		// OGRE Background Load :(
		// http://www.ogre3d.org/forums/viewtopic.php?f=2&t=42416
		// http://www.ogre3d.org/forums/viewtopic.php?f=1&t=68539

		/*
		// Creamos la tarea as�ncrona.
		_asyncTask = new  AsyncTask(this);

		// Nos registramos para cuando la tarea as�ncrona acabe se nos notifique.
		_asyncTask->attach(this);

		// Ejecutamos la tarea as�ncrona;
		_isLoadingAysnc = true;

		_asyncTask->run();
		*/



	} // activate

	//--------------------------------------------------------

	void CLoadingState::deactivate()
	{
		// Desactivamos la ventana GUI con el men� y el rat�n.
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().getMouseCursor().hide();
		_menuWindow->deactivate();
		_menuWindow->setVisible(false);

		CApplicationState::deactivate();
	} // deactivate

	//--------------------------------------------------------

	void CLoadingState::tick(unsigned int msecs)
	{
		CApplicationState::tick(msecs);

		// Pop LoadingState
		_app->popState(true);

		if (_nextState == "game"){

			// Push GameState
			_app->pushState("game", true);

			// Push PauseState
			_app->pushState("pause", true);
		}

		// Pop PauseState (deactivation)
		_app->popState();

	} // tick

	//--------------------------------------------------------

	void CLoadingState::setNextState(const std::string & nextState)
	{
		_nextState = nextState;
	} // setNextState

	//--------------------------------------------------------

	// M�todos correspondientes para la carga as�ncrona de las tareas.

	// M�todos que se va a ejecutar cuando la tarea as�ncrona comience.

	void CLoadingState::run(){

		for (int i = 0; i < 10000; i++)
			std::cout << "Carga as�ncrona funcionando " << std::endl;
	}

	// M�todos que se va a acabar cuando la tarea as�ncrona acabe.

	void CLoadingState::onAsyncTaskListener(){
		_isLoadingAysnc = false;

		std::cout << "Carga as�ncrona acabada " << std::endl;

	}

} // namespace Application
