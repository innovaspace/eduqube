/* 
    Libreria InnovaSpace_Modco.h by InnovaSpace
	Desarrollada para la implementacion del magentometro ModCo, 
	el cual tiene funcionalidad en los tres ejes (x,y,z).

	date: 17/08/2021
	date Modified: 17/08/2021
	Author: Mateo Roldan 
*/

//Cabecera de la libreria.
#ifndef INNOVASPACE_MODCO_H
#define InnovaSpace_Modco_H
#include<Arduino.h>

#define BUFF_SIZE 30	//Tamano del buff donde recibiremos los datos
#define AXIS_SIZE 5     //Tamano del buff auxiliar que nos servira al manipular el buffer anterior.

//Estructura de tipo dataModco, alamcenara los datos leidos en los tres ejes. 
struct dataModco
{
	int16_t x, y, z; //Variables enteras de 16 bits. 
};

//Clase InnovaSpace_Modco  
class InnovaSpace_Modco
{
public:
	//Metodos publicos 
	InnovaSpace_Modco();              // Constructor de la clase 
	void clean_buff(char *, uint8_t); // Metodo clean_buff, se encarga de limpiar un buff
	void get_Modco(dataModco &);      // Metodo get_Modco, obtiene los datos del magnetometro

private:
	//Atributos privados 
	char buff_Modco[BUFF_SIZE];	 // Array de caracteres, empleado para recolectar los datos del magnetometro 
	char buff_temp[AXIS_SIZE];   // Array de caracteres, empleado como buffer auxiliar.
};
#endif