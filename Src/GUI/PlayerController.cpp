#include "PlayerController.h"

#include "Logic/Entity/Message.h"
#include "Graphics\Server.h"
#include "Graphics\Scene.h"
#include "Graphics\Camera.h"

#include <cassert>

#define TURN_FACTOR 0.001f

namespace GUI {

	CPlayerController::CPlayerController() : _controlledAvatar(nullptr)
	{

	} // CPlayerController

	//--------------------------------------------------------

	CPlayerController::~CPlayerController()
	{
		deactivate();

	} // ~CPlayerController

	//--------------------------------------------------------

	void CPlayerController::activate()
	{		
		CInputManager::getSingletonPtr()->addKeyListener(this);
		CInputManager::getSingletonPtr()->addMouseListener(this);

	} // activate

	//--------------------------------------------------------

	void CPlayerController::deactivate()
	{
		CInputManager::getSingletonPtr()->removeKeyListener(this);
		CInputManager::getSingletonPtr()->removeMouseListener(this);

	} // deactivate

	//--------------------------------------------------------

	bool CPlayerController::keyPressed(TKey key)
	{
		if(_controlledAvatar)
		{
			Logic::TMessage m;
			m._type = Logic::Message::CONTROL;
			switch(key.keyId)
			{
			case GUI::Key::A:
				m.setArg<std::string>(std::string("control"), std::string("walkLeft"));
				break;
			case GUI::Key::D:
				m.setArg<std::string>(std::string("control"), std::string("walkRight"));
				break;
			case GUI::Key::SPACE:
			case GUI::Key::W:
				m.setArg<std::string>(std::string("control"), std::string("jump"));
				break;
			case GUI::Key::T:
				m.setArg<std::string>(std::string("playerEvent"), std::string("die"));
				m._type = Logic::Message::PLAYER_EVENT;
				break;
			case GUI::Key::E:
				m._type = Logic::Message::PICK_CHARGE;
				break;
			default:
				return false;
			}
			_controlledAvatar->emitMessage(m);
			return true;
		}
		return false;

	} // keyPressed

	//--------------------------------------------------------

	bool CPlayerController::keyReleased(TKey key)
	{
		if(_controlledAvatar)
		{
			Logic::TMessage m;
			switch(key.keyId)
			{

			case GUI::Key::A:
				m._type = Logic::Message::CONTROL;
				m.setArg<std::string>(std::string("control"), std::string("stopWalkingLeft"));
				break;
			case GUI::Key::D:
				m._type = Logic::Message::CONTROL;
				m.setArg<std::string>(std::string("control"), std::string("stopWalkingRight"));
				break;
			default:
				return false;
			}
			_controlledAvatar->emitMessage(m);
			return true;
		}
		return false;

	} // keyReleased

	//--------------------------------------------------------
	
	bool CPlayerController::mouseMoved(const CMouseState &mouseState)
	{
		return false;

	} // mouseMoved

	//--------------------------------------------------------
		
	bool CPlayerController::mousePressed(const CMouseState &mouseState)
	{
		if (_controlledAvatar)
		{
			Graphics::CCamera* camera;
			Vector3 pos;
			Logic::TMessage m;

			switch (mouseState.button)
			{
			case GUI::Button::LEFT:
				m._type = Logic::Message::PLAYER_CHANGE_STATE;
				break;
			case GUI::Button::RIGHT:
				m._type = Logic::Message::PUT_CHARGE;
				camera = Graphics::CServer::getSingletonPtr()->getActiveScene()->getCamera();

				pos = camera->screenToWorld(mouseState.posAbsX, mouseState.posAbsY);
				m.setArg<Vector3>(std::string("instancePosition"), Vector3(pos.x, pos.y, 0));
			}

			_controlledAvatar->emitMessage(m);
			return true;
		}
		return false;

	} // mousePressed

	//--------------------------------------------------------

	bool CPlayerController::mouseReleased(const CMouseState &mouseState)
	{
		return false;

	} // mouseReleased

} // namespace GUI
