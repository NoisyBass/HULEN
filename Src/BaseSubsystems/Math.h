/**
@file Math.h

Este fichero contiene la definici�n de ciertos tipos de datos
utilizados por la aplicaci�n y relacionados con la base
matem�tica; en particular, define distintos tipos de matriz,
vector, etc.
<p>
En la pr�ctica, los tipos son simplemente tipos sin�nimos
a los de Ogre, para evitar p�rdidas de tiempo en conversiones
superfluas entre la aplicaci�n y Ogre (s� habr� que hacerlas
entre la aplicaci�n y el motor de f�sica, por ejemplo).
<p>
Se ofrecen tambi�n una serie de funciones auxiliares.
 
@author David Llans�
@date Julio, 2010
*/

#ifndef __BaseSubsystems_Math_H
#define __BaseSubsystems_Math_H

// Includes de Ogre donde se definen los tipos
#include <OgreVector2.h>
#include <OgreVector3.h>
#include <OgreVector4.h>
#include <OgreQuaternion.h>
#include <OgreMatrix3.h>
#include <OgreMatrix4.h>
#include <OgreRay.h>
#include <math.h>

/**
Definicion de matriz de 4x4. La definici�n del tipo de datos
es la misma que la utilizada por el motor gr�fico, por lo tanto
es dependiente del motor usado.
 */
typedef Ogre::Matrix4 Matrix4;

/**
Definici�n de matriz de 3x3 de rotaci�n. La definici�n del tipo 
de datos es la misma que la utilizada por el motor gr�fico, por 
lo tanto es dependiente del motor usado.
 */
typedef Ogre::Matrix3 Matrix3;

/**
Vector (o punto) 2d utilizado. La definici�n del tipo de datos
es la misma que la utilizada por el motor gr�fico, por lo tanto
es dependiente del motor usado.
 */
typedef Ogre::Vector2 Vector2;

/**
Vector (o punto) 3d utilizado. La definici�n del tipo de datos
es la misma que la utilizada por el motor gr�fico, por lo tanto
es dependiente del motor usado.
 */
typedef	Ogre::Vector3 Vector3;

/**
Vector (o punto) 4d utilizado. La definici�n del tipo de datos
es la misma que la utilizada por el motor gr�fico, por lo tanto
es dependiente del motor usado.
 */
typedef	Ogre::Vector4 Vector4;

/**
Quaternion, usado para c�lculos de rotaciones tridimensionales. 
La definici�n del tipo de datos es la misma que la utilizada por 
el motor gr�fico, por lo tanto es dependiente del motor usado.
 */
typedef Ogre::Quaternion Quaternion;

/**
Rayo. La definici�n del tipo de datos es la misma que la utilizada 
por el motor gr�fico, por lo tanto es dependiente del motor usado.
 */
typedef Ogre::Ray Ray;

/**
Namespace en el que ofrecemos alguna definici�n de constante
matam�tica y m�todos para convertir grados en radianes, etc.
*/
namespace Math
{
	/**
	Definici�n de la constante PI.
	*/
	static const float PI = float( 4.0 * atan( 1.0 ) );

	/**
	Constante para pasar de grados a radianes.
	*/
	static const float _deg2Rad = PI / 180.0f;

	/**
	Constante para pasar de radianes a grados.
	*/
	static const float _rad2Deg = 180.0f / PI;

	/**
	Transforma grados en radianes.

	@param degree �ngulo en grados.
	@return �ngulo en radianes.
	*/
	static float fromDegreesToRadians(float degrees) {return degrees*_deg2Rad;}

	/**
	Transforma radianes en grados.

	@param radian �ngulo en radianes.
	@return �ngulo en grados.
	*/
	static float fromRadiansToDegrees(float radians) {return radians*_rad2Deg;}
	
	/**
	Crea un vector unitario de direcci�n a partir de un angulo de
	orientaci�n en radianes.

	@param orientation Orientaci�n en radianes.
	@return Vector unitario en el plano XZ.
	*/
	static Vector3 getDirection(float orientation) 
	{
		return Vector3(-sin(orientation), 0, -cos(orientation));

	} // getDirection
	
	/**
	Aplica un viraje a una matriz de transformaci�n.

	@param turn Giro en radianes que se quiere aplicar.
	@param transform Matriz de transformaci�n a modificar.
	*/
	static void yaw(float turn, Matrix4& transform) 
	{
		Matrix3 rotation;
		transform.extract3x3Matrix(rotation);
		Ogre::Radian yaw, pitch, roll;
		rotation.ToEulerAnglesYXZ(yaw, pitch, roll);
		Ogre::Radian newYaw = yaw + Ogre::Radian(turn);
		rotation.FromEulerAnglesYXZ(newYaw, pitch, roll);
		transform = rotation;

	} // yaw
	
	/**
	Extrae el estado del viraje de una matriz de transformaci�n.

	@param transform Matriz de transformaci�n.
	@return Viraje de la entidad.
	*/
	static float getYaw(const Matrix4& transform) 
	{
		Matrix3 rotation;
		transform.extract3x3Matrix(rotation);
		Ogre::Radian yaw, pitch, roll;
		rotation.ToEulerAnglesYXZ(yaw, pitch, roll);
		return yaw.valueRadians();

	} // getYaw
	
	/**
	Establece un viraje a una matriz de transformaci�n.

	@param turn Giro en radianes que se quiere etablecer.
	@param transform Matriz de transformaci�n a modificar.
	*/
	static void setYaw(float turn, Matrix4& transform) 
	{
		// Reiniciamos la matriz de rotaci�n
		transform = Matrix3::IDENTITY;
		// Sobre esta rotamos.
		Math::yaw(turn,transform);

	} // setYaw
	
	/**
	Crea un vector unitario de direcci�n en el plano XZ a partir 
	de una matriz de transformaci�n.

	@param transform Matriz de transformaci�n.
	@return Vector unitario en el plano XZ.
	*/
	static Vector3 getDirection(const Matrix4& transform) 
	{
		return getDirection(getYaw(transform));

	} // getDirection

	/**
	Normaliza un vector3
	*/
	static float normaliseVector3(Vector3& vectorToNormalise)
	{
		return vectorToNormalise.normalise();
	}

	static Vector3 rotationVector3YAxis(const Vector3& vector3, float degrees)
	{

		float radians = fromDegreesToRadians(degrees);

		float yAxis[3][3] = { { cos(radians), 0, sin(radians) },
							  { 0,			   1, 0 },
							  { -sin(radians), 0, cos(radians) } };

		float vector[3] = { vector3.x, vector3.y, vector3.z };
		float result[3] = { 0, 0, 0 };

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				result[i] += yAxis[i][j] * vector3[j];
			}
		}

		return Vector3(result[0], result[1], result[2]);
	}

	static Vector3 rotationVector3ZAxis(const Vector3& vector3, int degrees)
	{
		float radians = fromDegreesToRadians(degrees);

		float zAxis[3][3] = { { cos(radians), -sin(radians), 0 },
								{ sin(radians), cos(radians), 0 },
								{ 0,			0,			   1 } };

		float vector[3] = { vector3.x, vector3.y, vector3.z };
		float result[3] = { 0, 0, 0 };

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				result[i] += zAxis[i][j] * vector3[j];
			}
		}

		return Vector3(result[0], result[1], result[2]);
	}

	static Vector3 rotationVector3XAxis(const Vector3& vector3, float degrees)
	{
		float radians = fromDegreesToRadians(degrees);

		float xAxis[3][3] = {   { 1,			0, 0 },
								{ 0, cos(radians), -sin(radians) },
								{ 0, sin(radians), cos(radians) } };

		float vector[3] = { vector3.x, vector3.y, vector3.z };
		float result[3] = { 0, 0, 0 };

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				result[i] += xAxis[i][j] * vector3[j];
			}
		}

		return Vector3(result[0], result[1], result[2]);
	}

	static float clamp(float value, float min, float max){
		if (value <= min) return min;
		else if (value >= max) return max;
		else return value;
	}

	static float lerp(float a, float b, float f){
		return a + clamp(f,0,1) * (b - a);
	}

	static Vector3 lerp(const Vector3 & a, const Vector3 & b, float f){

		return Vector3(lerp(a.x, b.x, f),
			lerp(a.y, b.y, f),
			lerp(a.z, b.z, f));
	}

} // namespace Math

#endif // __BaseSubsystems_Math_H
