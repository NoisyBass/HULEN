/**
@file Camera.cpp

Contiene la implementaci�n del componente que controla la c�mara gr�fica
de una escena.
 
@see Logic::CCamera
@see Logic::IComponent

@author David Llans�
@date Agosto, 2010
*/

#include "Camera.h"

#include "Logic/Server.h"
#include "Logic/Entity/Entity.h"
#include "Logic\Entity\GameObject.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Graphics/Scene.h"
#include "Graphics/Camera.h"

#include "BaseSubsystems/Math.h"

namespace Logic 
{
	IMP_FACTORY(CCamera);
	
	//---------------------------------------------------------

	bool CCamera::spawn(const std::string& name, CEntity *entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if(!IComponent::spawn(name, entity,map,entityInfo))
			return false;

		_graphicsCamera = _entity->getGameObject()->getMap()->getScene()->getCamera();
		if(!_graphicsCamera)
			return false;

		if(entityInfo->hasAttribute("fixed"))
			_fixed = entityInfo->getBoolAttribute("fixed");

		if (entityInfo->hasAttribute("ratio")){
			std::string auxRatio = entityInfo->getStringAttribute("ratio");

			//Ratio por defecto
			float ratio = 4.0f / 3.0f;

			if (auxRatio == "169")
				ratio = 16.0f / 9.0f;
			else if (auxRatio == "43")
				ratio = 4.0f / 3.0f;

			_graphicsCamera->setAspectRatio(ratio);

		}

		if (entityInfo->hasAttribute("fov"))
			_graphicsCamera->setFOV(entityInfo->getFloatAttribute("fov"));

		if (_fixed){

			// Actualizar la posici�n de la c�mara con la posici�n de la entidad.
			_graphicsCamera->setCameraPosition(_entity->getPosition());

			// La c�mara apunta al 0, 0 , 0
			_graphicsCamera->setTargetCameraPosition(Vector3::ZERO);
		}

		startPosition = _graphicsCamera->getCameraPosition();

		return true;

	} // spawn

	/*void CCamera::init(const std::string& name, CEntity *entity, CMap *map, const Map::CEntity *entityInfo)
	{

	} // init*/
	
	//---------------------------------------------------------

	bool CCamera::activate()
	{
		_isZoomedIn = _isZoomingOut = _isZoomingIn = false;

		// par�metros cableados en el c�digo.
		_offsetX = 2;
		_offsetY = 0;
		_offsetZ = 7; 
		_zoomSpeed = 1;

		if (_fixed){

			_graphicsCamera->setCameraPosition(_entity->getPosition());
			_graphicsCamera->setTargetCameraPosition(Vector3::ZERO);
		}

		CServer::getSingletonPtr()->setCamera(this);

		return true;
	} // activate
	
	//---------------------------------------------------------

	void CCamera::deactivate()
	{
		_isZoomedIn = _isZoomingOut = _isZoomingIn = false;
		_offsetX = _offsetY = _offsetZ = 0;
		_zoomSpeed = 1;

		CServer::getSingletonPtr()->setCamera(nullptr);
	} // deactivate
	
	//---------------------------------------------------------

	void CCamera::tick(float msecs)
	{
		IComponent::tick(msecs);

		if (_isZoomingIn && !_isZoomedIn){

			// Posici�n de la C�mara
			Vector3 position = _graphicsCamera->getCameraPosition();

			// Player Moved Position
			Vector3 playerMovedPosition = CServer::getSingletonPtr()->getPlayer()->getPosition() + 
				Vector3(_offsetX,_offsetY,_offsetZ);

			/*
			// Interpolaci�n de Targets ( Target Actual con la Posici�n del Player)
			Vector3 interpolatedTargets = Math::lerp(
				_graphicsCamera->getTargetCameraPosition(), playerMovedPosition , msecs * 3);
			_graphicsCamera->setTargetCameraPosition(interpolatedTargets);
			*/

			// Interpolaci�n de Posiciones (Posici�n Actual con la Posici�n del Target => Desplazamiento)
			Vector3 interpolatedPosition = Math::lerp(
				position, playerMovedPosition, msecs * _zoomSpeed);
			_graphicsCamera->setCameraPosition(interpolatedPosition);

			// Detectar que hemos llegado a la posici�n final
			if (abs((interpolatedPosition - playerMovedPosition).x) < 0.1){

				_isZoomingIn = false;

				_isZoomedIn = true;

				// Cambiar esto si se quiere separar el Zoom In del Zoom Out
				zoomOut();
			}
		}

		if (_isZoomingOut && _isZoomedIn){

			// Posici�n de la C�mara
			Vector3 position = _graphicsCamera->getCameraPosition();

			// Interpolaci�n de Posiciones (Posici�n Actual con la Posici�n de Start => Desplazamiento)
			Vector3 interpolatedPosition = Math::lerp(
				position, startPosition, msecs * _zoomSpeed);
			_graphicsCamera->setCameraPosition(interpolatedPosition);

			// Detectar que hemos llegado a la posici�n final
			if (abs((interpolatedPosition - startPosition).x) < 0.1){

				_isZoomingOut = false;

				_isZoomedIn = false;
			}

		}
	} // tick

	//---------------------------------------------------------

	void CCamera::zoomIn()
	{
		_isZoomingIn = true;
	} // zoomIn

	void CCamera::zoomOut()
	{
		_isZoomingOut = true;
	} // zoomOut

} // namespace Logic

