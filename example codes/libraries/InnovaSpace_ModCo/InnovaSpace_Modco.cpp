/* 
    Libreria InnovaSpace_Modco.h by InnovaSpace
	Desarrollada para la implementacion del magentometro ModCo, 
	el cual tiene funcionalidad en los tres ejes (x,y,z).

	date: 17/08/2021
	date Modified: 17/08/2021
	Author: Mateo Roldan 
*/
//Incluimos cabecero .h
#include <InnovaSpace_Modco.h>

//Constructor de la clase
InnovaSpace_Modco :: InnovaSpace_Modco(){}

//Funcion de retorno vacio, empleada para limpiar array de caracteres 
void InnovaSpace_Modco :: clean_buff(char *ptr_buff/*Puntero a la primera posicion del Array*/, uint8_t _n/*Largo del Array*/){
	for (int i = 0; i < _n; ++i)
	{
		//Mediante un for se recorre el array y se asigna un ' ' a cada posicion
		ptr_buff[i] = ' ';
	}
}

void InnovaSpace_Modco :: get_Modco(dataModco &_data /*Estructura referenciada de tipo dataModco*/){
	clean_buff(buff_Modco, BUFF_SIZE); // Se limpia el buff principal donde se guardaran los datos leidos desde el magnetometro

	Serial3.readBytesUntil('\n', buff_Modco, BUFF_SIZE); //Se lee el puerto serial3 hasta el proximo salto de linea, donde esta conectado nuestro sensor.

	int pos = 5, pos2 = 0;	// Variables enteras empleadas como iteradores
	while(buff_Modco[pos] != ','){
		//Los datos son almacenados en el buffer temporal mientras sean distintos a una ',' que indica la finalizacion de la data en el eje x
		buff_temp[pos2] = buff_Modco[pos];
		//aumentamos los iteradores, avanzando en los array.
		pos++;
		pos2++;
	} 
	_data.x = atoi(buff_temp);       	// Se castea los caracteres leidos a enteros, para luego asignarlos a la estructura
	clean_buff(buff_temp, AXIS_SIZE);   // Limpiamos el buffer temporal

	pos2 = 0;
	pos++;
    while(buff_Modco[pos] != ','){ 
    	//Los datos son almacenados en el buffer temporal mientras sean distintos a una ',' que indica la finalizacion de la data en el eje y
    	buff_temp[pos2] = buff_Modco[pos];
    	//aumentamos los iteradores, avanzando en los array.
    	pos++;
    	pos2++;
    }
    _data.y = atoi(buff_temp);          // Se castea los caracteres leidos a enteros, para luego asignarlos a la estructura
    clean_buff(buff_temp, AXIS_SIZE);	// Limpiamos el buffer temporal
     
    pos++;
    pos2 = 0;
    while(buff_Modco[pos] != '*'){
    	//Los datos son almacenados en el buffer temporal mientras sean distintos a una '*' que indica la finalizacion de la data en el eje z
    	buff_temp[pos2] = buff_Modco[pos];
    	//aumentamos los iteradores, avanzando en los array.
    	pos++;
    	pos2++;
    }
    _data.z = atoi(buff_temp);       	// Se castea los caracteres leidos a enteros, para luego asignarlos a la estructura
    clean_buff(buff_temp, AXIS_SIZE);	// Limpiamos el buffer temporal
}
