#ifndef GRAPHICS_ANIMATED_ENTITY_H
#define GRAPHICS_ANIMATED_ENTITY_H

#include "Graphics/Entity.h"
#include "Graphics/Scene.h"

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Ogre 
{
	class AnimationState;
}
	
namespace Graphics 
{
	/**
	Esta clase debe ser implementada por las clases que quieren
	registrarse en una entidad animada para enterarse de cuando
	terminan las animaciones de �sta.
	
	@ingroup graphicsGroup

	@author David Llans�
	@date Julio, 2010
	*/
	class CAnimatedEntityListener 
	{
	public:

		/**
		M�todo que ser� invocado siempre que se termine una animaci�n.
		Las animaciones en c�clicas no invocar�n nunca este m�todo.

		@param animation Nombre de la animaci�n terminada.
		*/
		virtual void animationFinished(const std::string &animation, const bool nextAnimation) {}

		virtual void animationWithoutLoopStarted(const std::string &animation) {}

	}; // CAnimatedEntityListener

	/**
	Clase que representa una entidad gr�fica con animaciones. Especializa la clase
	Graphics::CEntity por lo que contiene una referencia a una entidad de 
	Ogre y al Nodo que la contiene. A�ade la posibilidad de activar una animaci�n 
	y reproducirla.
	<p>
	Esta clase es bastante sencilla y solo controlamos una animaci�n activa.
	Podr�a ser m�s sofisticada permitiendo interpolaci�n de animaciones o avisando
	mediante observers cuando una animaci�n termina de reproducirse.
	<p>
	Oculta los detalles escabrosos del motor gr�fico.
	
	@ingroup graphicsGroup

	@author David Llans�
	@date Julio, 2010
	*/
	class CAnimatedEntity : public CEntity
	{
	public:


		/**
		Constructor de la clase.

		@param name Nombre de la entidad.
		@param mesh Nombre del modelo que debe cargarse.
		*/
		CAnimatedEntity(const std::string &name, const std::string &mesh);

		/**
		Destructor de la aplicaci�n.
		*/
		virtual ~CAnimatedEntity();

		/**
		Activa una animaci�n a partir de su nombre.

		@param anim Nombre de la animaci�n a activar.
		@param loop true si la animaci�n debe reproducirse c�clicamente.
		@param nextAnimation por defecto siempre vamos a querer que se reproduzca despues de 
		acabar, la animacion por defecto, pero en algun caso como la muerte del personaje
		que no queramos que se reproduzca ninguna animaci�n m�s, basta con activar el flag a false.
		@return true si la animaci�n solicitada fue correctamente activada.
		*/
		bool setAnimation(const std::string &anim, bool loop, bool nextAnimation = true);
		
		/**
		Desactiva una animaci�n a partir de su nombre.

		@param anim Nombre de la animaci�n a activar.
		@return true si la animaci�n solicitada fue correctamente desactivada.
		*/
		bool stopAnimation(const std::string &anim);
		
		/**
		Desactiva todas las animaciones de una entidad.
		*/
		void stopAllAnimations();

		/**
		Funci�n que registra al oyente de la entidad gr�fica. Por 
		simplicidad solo habr� un oyente por entidad.
		*/
		void setObserver(CAnimatedEntityListener *observer)
											{_observer = observer;}

		/**
		Funci�n que quita al oyente de la entidad gr�fica. Por 
		simplicidad solo habr� un oyente por entidad.
		*/
		void removeObserver(CAnimatedEntityListener *observer)
							{if(_observer = observer) _observer = 0;}

		std::string getCurrentAnimationName() const;

		bool getCurrentAnimationLoop() const;

		void dumpAnimsStates();

		void initAnimationStates(float defaultVelocity, std::unordered_map<std::string, float>& animationValues, float defaultBlending, std::unordered_map<std::string, float>& blendingValues);

	protected:

		/**
		Objeto oyente que es informado de cambios en la entidad como 
		la terminaci�n de las animaciones. Por simplicidad solo habr�
		un oyente por entidad.
		*/
		CAnimatedEntityListener *_observer;

		// Cada entidad debe pertenecer a una escena. Solo permitimos
		// a la escena actualizar el estado.
		friend class CScene;
		
		/**
		Actualiza el estado de la entidad cada ciclo.
		
		@param secs N�mero de milisegundos transcurridos desde la �ltima 
		llamada.
		*/
		virtual void tick(float secs);

		struct Animation{
			Animation() : animationState(nullptr), fadingIn(false), fadingOut(false), animationVelocity(0.0f), blendingVelocity(0.0f) {};

			Animation(Ogre::AnimationState* as, bool fadingIn, bool fadingOut, float animationVelocity, float blendingVelocity) :
				animationState(as), fadingIn(fadingIn), fadingOut(fadingOut), animationVelocity(animationVelocity), blendingVelocity(blendingVelocity) {};

			~Animation() = default;

			Ogre::AnimationState* animationState;
			float animationVelocity;
			float blendingVelocity;
			bool fadingIn;
			bool fadingOut;
		};

		std::unordered_map < std::string, Animation* > _animations;

		/**
		Animaci�n que tiene la entidad activada.
		*/
		Animation* _currentAnimation;

		/**
		Indica que cuando se acaba una animacion, se reproduzca la
		animaci�n por defecto o no.
		*/
		bool _nextAnimation;

	}; // class CAnimatedEntity

} // namespace Graphics

#endif // __Graphics_AnimatedEntity_H
