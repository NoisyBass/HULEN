POR LA PARTE DE LA LOGICA:
--------------------------

-> Las entidades ya no tienen un id unico, ni el mapa. Estos campos los tiene ahora el game object

POR LA PARTE DE LA CARGA:
-------------------------

-> Ha hecho falta cambiar la EntityFactory, ya que como su nombre indica, s�lo cargaba entidades XD.
Y necesitamos ser capaces de cargar entidades y game objects.
Al cargar una entidad le ponias todos sus componentes y la asignabas al mapa (funci�n createEntity de EntityFactory). 
�Problema? Ahora el mapa s�lo tiene game objects, y los game objects las entidades. Por lo que las entidades ya no se 
a�aden al mapa, sino a su game object, y el game object es el que se a�ade al mapa.

SOLUCION:
	- En map.txt debe aparecer siempre el game object antes que las entidades
	- Hay un nuevo campo en los objetos del map.txt que se llama "blueprint", equivale al antiguo "type"
	- Ahora "type" nos indica si ese objeto es un GameObject, o una Entity
	- Si es una entidad necesitaremos otro campo "game_object" con el nombre del GameObject que va a contenerla (similar a lo de los triggers)
	- Si es un GameObject (type = "GameObject") en EntityFactory::createEntity hacemos lo que haciamos antes con las entidades, lo creamos, 
	le a�adimos los componentes y lo a�adimos al mapa.
	- Si es una entidad (type = "Entity") creamos la entidad y le a�adimos los componentes, pero no la a�adimos al mapa, sino que buscamos en el
	mapa su GameObject (de ahi que necesitemos el campo "game_object") y la a�adimos a �l.

EJEMPLO DE COMO SER�AN LOS FICHEROS

-> blueprints.txt

PlayerManager CPlayerManager
PlayerBody CAvatarController CAnimatedGraphics CPhysicController
PlayerShadow CAvatarController CAnimatedGraphics CPhysicController

* En realidad si PlayerBody y PlayerShadow son exactamente iguales podriamos tener un unico blueprint Player, pero por claridad pongo ambos

-> map.txt

Map = {
	PlayerManager = {
		type = "GameObject",
		blueprint = "PlayerManager",
		// M�s campos necesarios...
	},
	PlayerBody = {
		type = "Entity",
		game_object = "PlayerManager",
		blueprint = "PlayerBody",
		// M�s campos necesarios...
	},
	PlayerShadow = {
		type = "Entity",
		game_object = "PlayerManager",
		blueprint = "PlayerShadow",
		// M�s campos necesarios...
	},
}