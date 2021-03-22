#include <iostream>
#include "fmod.h"
#include <fmod.hpp>



void saluda() {

	// FMOD TESTING
	FMOD::System* system;
	FMOD_RESULT result;
	result = FMOD::System_Create(&system); // Creamos el objeto system
	// 128 canales (numero maximo que podremos utilizar simultaneamente)
	result = system->init(128, FMOD_INIT_NORMAL, 0); // Inicializacion de FMOD

	FMOD::Sound* sound;
	result = system->createSound(
		"Assets/Audio/ProtoDarkMaze_Menu.mp3", // path al archivo de sonido
		FMOD_DEFAULT, // valores (por defecto en este caso: sin loop, 2D)
		0, // informacion adicional (nada en este caso)
		&sound);

	FMOD::Channel* channel;
	result = system->playSound(
		sound, // buffer que se "engancha" a ese canal
		0, // grupo de canales, 0 sin agrupar (agrupado en el master)
		false, // arranca sin "pause" (se reproduce directamente)
		&channel); // devuelve el canal que asigna
		// el sonido ya se esta reproduciendo

		///-----initialization_start-----
	std::system("Pause");
}