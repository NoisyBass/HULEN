#include "Crawler.h"

#include "Logic/Entity/Components/Vision.h"

namespace Logic
{
	IMP_FACTORY(CCrawler);

	CCrawler::CCrawler()
		: IComponent()
	{
		// Creamos la m�quina de estados
		_agent = new AI::FSMCrawler();

	} // CCrawler

	CCrawler::~CCrawler()
	{
		if (_agent)
			delete _agent;

	} // ~CCrawler


	void CCrawler::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		// Actualizamos los valores que necesita el agente
		CVision* crawlerVision = (CVision*)(_entity->getComponent("CVision"));
		if (crawlerVision->_seeingEntity && !crawlerVision->_lastSeenEntity->getName().compare("Player_Body"))
		{
			std::cout << "He visto al player" << std::endl;
			_agent->getValues()->setBoolValue("SeeingPlayer", true);
		}
		else
		{
			_agent->getValues()->setBoolValue("SeeingPlayer", false);
		}
			

		_agent->update();

	} // tick

} // namespace Logic