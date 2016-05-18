/**
@file Camera.h

Contiene la declaraci�n del componente que controla la c�mara gr�fica
de una escena.

@see Logic::CCamera
@see Logic::IComponent

@author David Llans�
@date Septiembre, 2010
*/
#ifndef __Logic_Camera_H
#define __Logic_Camera_H

#include "Logic/Entity/Component.h"

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Graphics 
{
	class CCamera;
	class CScene;
}

//declaraci�n de la clase
namespace Logic 
{
/**
	Componente que se encarga de mover la c�mara gr�fica de una escena, para que 
	�sta se pueda reenderizar, siguiendo al jugador.
	<p>
	La c�mara se situar� a una distancia detr�s del jugador y a una altura del 
	suelo y enfocar� a un punto imaginario por delante del jugador que estar� 
	tambi�n a cierta altura del suelo. Todas estas caracter�sticas son configurables 
	desde la declaraci�n del mapa definiendo los nombres de atributo "distance",
	"height", "targetDistance" y "targetHeight".
	<p>
	El componente ir� recalculando en cada ciclo las posiciones de la c�mara y del
	punto de mira en funci�n de la posici�n y orientaci�n del jugador.
	
    @ingroup logicGroup

	@author David Llans� Garc�a
	@date Septiembre, 2010
*/
	class CCamera : public IComponent
	{
		DEC_FACTORY(CCamera);
	public:

		/**
		Constructor por defecto; en la clase base no hace nada.
		*/
		CCamera() : IComponent(), _graphicsCamera(0), _zoomSpeed(1), 
			_isZoomedIn(false), _isZoomingIn(false), _isZoomingOut(false),
			_offsetX(0), _offsetY(0), _offsetZ(0){}
		
		/**
		Inicializaci�n del componente, utilizando la informaci�n extra�da de
		la entidad le�da del mapa (Maps::CEntity). Se accede a los atributos 
		necesarios como la c�mara gr�fica y se leen atributos del mapa.

		@param entity Entidad a la que pertenece el componente.
		@param map Mapa L�gico en el que se registrar� el objeto.
		@param entityInfo Informaci�n de construcci�n del objeto le�do del
			fichero de disco.
		@return Cierto si la inicializaci�n ha sido satisfactoria.
		*/
		virtual bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		/**
		M�todo que activa el componente; invocado cuando se activa
		el mapa donde est� la entidad a la que pertenece el componente.
		<p>
		Se coge el jugador del mapa, la entidad que se quiere "seguir".

		@return true si todo ha ido correctamente.
		*/
		virtual bool activate();
		
		/**
		M�todo que desactiva el componente; invocado cuando se
		desactiva el mapa donde est� la entidad a la que pertenece el
		componente. Se invocar� siempre, independientemente de si estamos
		activados o no.
		<p>
		Se pone el objetivo a seguir a NULL.
		*/
		virtual void deactivate();

		/**
		M�todo llamado en cada frame que actualiza el estado del componente.
		<p>
		Se encarga de mover la c�mara siguiendo al jugador.

		@param msecs Milisegundos transcurridos desde el �ltimo tick.
		*/
		virtual void tick(float msecs);

		/**
		Metodo que sirve para hacer el zoomIn sobre el personaje.
		Solo lo hace cuando no se ha hecho un zoomIn anteriormente.
		Hace el zoomIn sobre el player.
		*/
		void zoomIn();

		/**
		Metodo que sirve para hacer el zoomIn sobre el personaje.
		Solo lo hace cuando no se ha hecho un zoomIn anteriormente.
		Hace el zoomIn sobre el player.
		*/
		void zoomOut();

	protected:
		
		/**
		C�mara gr�fica.
		*/
		Graphics::CCamera *_graphicsCamera;

		/**
		Indica si la camara debe seguir al target o no. 
		Esto implica que la posici�n del target no debe actualizarse en cada tick.
		*/
		bool _fixed;

		// Par�metros del zoom de la c�mara

		/**
		Posicion inicial de la c�mara.
		*/
		Vector3 startPosition;

		/**
		Velocidad a la que hace el Zoom In y Zoom Out.
		*/
		float _zoomSpeed;

		/**
		Indica si la c�mara est� haciendo un Zoom In.
		*/
		bool _isZoomingIn;

		/**
		Indica si se ha hecho un Zoom In.
		*/
		bool _isZoomedIn;

		/**
		Indica si est� haciendo un Zoom Out.
		*/
		bool _isZoomingOut;

		/**
		Coordenada X que se le suma a la posici�n del player sobre la ue hacer zoom.
		*/
		float _offsetX;

		/**
		Coordenada Y que se le suma a la posici�n del player sobre la ue hacer zoom.
		*/
		float _offsetY;

		/**
		Coordenada > que se le suma a la posici�n del player sobre la ue hacer zoom.
		*/
		float _offsetZ;

	}; // class CCamera

	REG_FACTORY(CCamera);

} // namespace Logic

#endif // __Logic_Camera_H
