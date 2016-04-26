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

#ifndef __Application_CAsyncTask_H
#define __Application_CAsyncTask_H

#include <vector>
#include <thread>        

namespace Application
{
	/**
	Interfaz que debe implementar cualquier clase que deba ejecutar algo en una tarea as�ncrona.
	*/
	class IAsyncTaskData {

	public:

		virtual void run() = 0;
	};

	/**
	Interfaz que debe implementar la clase la cual quiere ejecutar un m�todo cuando la tarea as�ncrona acabe.
	*/
	class IOnAsyncTaskFinished {

	public:

		virtual void onAsyncTaskListener() = 0;
	};

	
	class CAsyncTask
	{

	public:

		/**
		Constructor de la clase
		*/
		CAsyncTask(IAsyncTaskData * CAsyncTaskData);

		/**
		Destructor de la AsyncTask
		*/
		virtual ~CAsyncTask();

		// M�todos del Patr�n Observer

		/**
		Permite registrar una clase que implemente el interfaz IOnAsyncTaskFinished para que ejecute
		esa funci�n que implemente el interfaz cuando la AsyncTask acabe.
		*/
		void attach(IOnAsyncTaskFinished * onCAsyncTaskFinished);

		/**
		Permite ejecutar AsyncTask.
		*/
		void run();

		/**
		Bloquea el thread que llama a este m�todo hasta que la AsyncTask acabe. 
	
		IMPORTANTE
		No usar conjuntamente si la clase implementa el interfaz IOnAsyncTaskFinished 
		y se registra en la lista _onAsyncTaskFinishedList.
		*/
		void join();

	private:

		/**
		Ejecute el m�todo onAsyncTaskListener de la lista _onAsyncTaskFinishedList.
		Actualmente, esa notificaci�n se manda cuando la tarea as�ncrona acabe. 
		Por eso solo la AsyncTask debe llamarlo (modificador private).
		*/
		void notify();

		/**
		M�todo auxiliar que hace que notifique a la lista _onAsyncTaskFinishedList tras haber acabado la AsyncTask.
		*/
		void runAsyncData();

		/**
		Tipo de datos lista de OnCAsyncTaskFinished. Es un vector de las STL.
		*/
		typedef std::vector<class IOnAsyncTaskFinished *> OnAsyncTaskFinishedList;

		/**
		Lista de objetos los cuales van a recibir la notificaci�n cuando acabe la tarea.
		*/
		OnAsyncTaskFinishedList * _onAsyncTaskFinishedList;

		/*
		Objeto que tiene la funci�n que va a ejecutar la tarea as�ncrona.
		*/
		IAsyncTaskData * _asyncTaskData;

		/**
		Hilo de ejecuci�n que va a ejecutar la tarea as�ncrona.
		*/
		std::thread * _thread;

	}; // CAsyncTask

} // namespace Application

#endif //  __Application_CAsyncTask_H