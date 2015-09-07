#ifndef REFERENCE_MAP_VECTOR_HPP
#define REFERENCE_MAP_VECTOR_HPP

#include <iostream>
#include <vector>
#include "GlobalInformation.hpp"
#include "Neuron.hpp"
#include <cstdlib>
#include <algorithm>

#define NOT_CONNECTIONS_BACK -2
#define AVAIBLE_MUTATION -1
#define NOT_MUTATION_AVAIBLE -3

namespace NEATSpikes
{

	class ReferenceMapVector
	{ 
		public: 
			ReferenceMapVector()
			{

			}

			ReferenceMapVector(int position)
			{
				this->position = position;
				initialSize = position*2 + 1;  
				coordinates = new int[initialSize];
				amountOfAvaibleMutations = initialSize;
				std::fill_n(coordinates, initialSize, AVAIBLE_MUTATION);
			}

			ReferenceMapVector(int position, GlobalInformation * globalInformation, std::vector < Neuron * > * neurons, bool connectionsBack)
			{
				std::cerr << "ReferenceMapVector::1" << std::endl;
				// Se crea este vector y se setean los valores.
				this->position = position;
				this->connectionsBack = connectionsBack;
				initialSize = position*2 + 1;  
				coordinates = new int[initialSize];
				amountOfAvaibleMutations = initialSize;
				this->neurons = neurons;
				this->globalInformation = globalInformation;
				std::cerr << "ReferenceMapVector::2" << std::endl;
				std::fill_n(coordinates, initialSize, AVAIBLE_MUTATION);
				std::cerr << "ReferenceMapVector::3" << std::endl;

				// En caso de que se prohiba conecciones recursivas se deben eliminar todas las opciones recursivas.
				std::cerr << "ReferenceMapVector::4" << std::endl;
				if(!connectionsBack)
				{
				std::cerr << "ReferenceMapVector::5" << std::endl;
					coordinates[position] = NOT_CONNECTIONS_BACK;
					amountOfAvaibleMutations --;

					amountOfAvaibleMutations -= (initialSize-1)/2;
				std::cerr << "neuronsize " << (*neurons).size() << "\t" << position << std::endl;
					int thisNeuronLayerPlace = globalInformation->layerToPlace((*neurons).at(position)->getLayer());
					//Se mira la primera mitad nada mas pues la siguiente mitad es inverso.
				std::cerr << "ReferenceMapVector::6" << std::endl;
					for (int i = 0; i < (initialSize-1)/2; ++i)
					{
						int otherNeuronLayerPlace = globalInformation->layerToPlace((*neurons).at(i)->getLayer()); 
				std::cerr << "ReferenceMapVector::7" << std::endl;
						if( thisNeuronLayerPlace >= otherNeuronLayerPlace )
						{
							coordinates[i] = NOT_CONNECTIONS_BACK;
							coordinates[initialSize -1 -i] = -1;
				std::cerr << "ReferenceMapVector::8" << std::endl;
							if(thisNeuronLayerPlace == otherNeuronLayerPlace)
							{
								coordinates[initialSize - 1 -i] = NOT_CONNECTIONS_BACK;
								amountOfAvaibleMutations--;
				std::cerr << "ReferenceMapVector::9" << std::endl;
							}
						}
						else
						{
				std::cerr << "ReferenceMapVector::10" << std::endl;
							coordinates[initialSize -1 -i] = NOT_CONNECTIONS_BACK;
							coordinates[i] = -1;
				std::cerr << "ReferenceMapVector::11" << std::endl;

						}
					}
				}
			}

			~ReferenceMapVector()
			{
				delete[] coordinates;
			}

			int getAmountOfAvaibleMutations()
			{
				return amountOfAvaibleMutations;
			}

			int getAvaibleAtPlace (int place)
			{
				int count = 0; 
				for (int i = 0; i < initialSize; ++i)
				{
					if(coordinates[i] == AVAIBLE_MUTATION)
					{
						if(count == place)
						{
							return i;
						}
						count++;
					}
				}

				std::cerr << "ERROR::ReferenceMapVector::getAvaibleAtPlace::Not avaivle place found" << std::endl;
				exit(EXIT_FAILURE);
			}

			void set ( int absolutePlace, int value )
			{
				coordinates [ absolutePlace ] = value;
				amountOfAvaibleMutations--;
			}

			int get ( int absolutePlace )
			{
				return coordinates [ absolutePlace ];
			}

			ReferenceMapVector * duplicate(std::vector < Neuron * > * _neurons)
			{
				ReferenceMapVector * result = new ReferenceMapVector(position);
				for (int i = 0; i < position*2 + 1; ++i)
				{
					result->coordinates[i] =  this->coordinates[i];
				}
				result->amountOfAvaibleMutations = this->amountOfAvaibleMutations;
				result->connectionsBack = this->connectionsBack;
				result->neurons = _neurons;
				return result;
			}

			void print()
			{
				for (int i = 0; i < initialSize-1; ++i)
				{
					std::cout << coordinates[i] << "  "; 
				}
				std::cout << coordinates[initialSize-1];
			}

		private:
			int amountOfAvaibleMutations;
			int * coordinates;
			int position;
			bool connectionsBack;
			std::vector < Neuron * > * neurons;
			int initialSize;
			GlobalInformation * globalInformation;
	};
}
#endif