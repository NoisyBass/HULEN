//---------------------------------------------------------------------------
// AsyncTask.h
//---------------------------------------------------------------------------

/**
@file AsyncTask.h

Contiene la funcionalidad para poder ejecutar tareas as�ncronas.

@see Application::CAsyncTask
@see Application::CAsyncTask

@author Daniel Ruiz
@date Abril, 2016
*/

#ifndef __Application_AsyncTask_H
#define __Application_AsyncTask_H

#include <vector>
#include <thread>        

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n

namespace Application
{

	class AsyncTaskData {

	public:

		virtual void run() = 0;
	};

	class OnAsyncTaskFinished {

	public:

		virtual void onAsyncTaskListener() = 0;
	};

	

	class AsyncTask
	{

	public:

		/**
		Constructor de la clase
		*/
		AsyncTask(AsyncTaskData * asyncTaskData);

		/**
		Destructor de la aplicaci�n
		*/
		virtual ~AsyncTask();

		void attach(OnAsyncTaskFinished * onAsyncTaskFinished);

		void notify();

		void run();


		/**
		Hilo de ejecuci�n que va a ejecutar la tarea as�ncrona.
		*/
		std::thread * _thread;

	private:

		void runAsyncData();

		/**
		Tipo de datos lista de OnAsyncTaskFinished. Es un vector de las STL.
		*/
		typedef std::vector<class OnAsyncTaskFinished *> OnAsyncTaskFinishedList;

		/**
		Lista de objetos los cuales van a recibir la notificaci�n cuando acabe la tarea.
		*/
		OnAsyncTaskFinishedList * _onAsyncTaskFinishedList;

		/*
		Objeto que tiene la funci�n que va a ejecutar la tarea as�ncrona.
		*/
		AsyncTaskData * _asyncTaskData;


	}; // namespace Application

}
#endif //  __Application_AsyncTask_H