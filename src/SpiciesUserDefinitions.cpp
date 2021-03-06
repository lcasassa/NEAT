#include <fstream> // ofstream
#include <map> // map
#include <iostream>
#include <cstring>


#include "SpiciesUserDefinitions.hpp"



namespace NEAT
{

SpiciesUserDefinitions::~SpiciesUserDefinitions()
{

}

SpiciesUserDefinitions::SpiciesUserDefinitions(  ): SpiciesUserDefinitions( "./SPICIESUD" )
{

}
SpiciesUserDefinitions::SpiciesUserDefinitions( std::string path )
{
	std::map <std::string, double> loadData; // Se guardara la informacion en el mapa primero y luego se pasara a las variables.
	std::ifstream file;
	std::string line;
	char * piece1; // Aqui se guardan los strings
	char * piece2; // y aquí el valor 
	char * saveptr; // variable para indicar el lugar donde quedó la ultima lectura del strtok_r
	char delimiters[] = " \n\t"; // Los delimitadores usados.
	// Obtener toda la informacion del archivo
	file.open(  path , std::ios::in );
	if( file.is_open() )
	{
		while ( std::getline(file, line) )
	    {
	    	char * dup = strdup(line.c_str());
			piece1 = strtok_r( dup, delimiters, &saveptr); // Por si acaso se desea hacer uso de hilos.
			piece2 = strtok_r(NULL, delimiters, &saveptr);	    	
	    	loadData.emplace( std::make_pair( piece1, atof( piece2 ) ) );
	    	free(dup);
	    }
	    file.close();
	}

	// Se cargan todas las variables con los datos.
	maxAmountOfRacesPerSpicie = uint( loadData["maxAmountOfRacesPerSpicie"] ) ;	
	maxYears = uint( loadData["maxYears"] ) ;	

	loadData.clear();
}

void SpiciesUserDefinitions::printInfo()
{
	std::cout << 
	"maxAmountOfRacesPerSpicie: " << maxAmountOfRacesPerSpicie << std::endl <<
	"maxYears: " << maxYears <<
	std::endl;
}

}