/*
 * SimpleNN. Neural-Network Simple Program.
 * Copyright (C) Toshiyuki Hirooka <toshi.hirooka@gmail.com> http://wasabi.in/
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include <iostream>
#include <iomanip>

const int N_NEURON_LAYER = 3;
const int N_NEURON = 5;

class NN
{
	public:

		// Status of Neurons
		int neurons[N_NEURON_LAYER][N_NEURON];

		// Weight of Neurons
		float weight[N_NEURON_LAYER][N_NEURON][N_NEURON];

		NN()
		{
			for(int y=0; y<N_NEURON_LAYER; y++)
				for(int x=0; x<N_NEURON; x++)
					neurons[y][x] = 0;
			for(int z=0; z<N_NEURON; z++)
				for(int y=0; y<N_NEURON; y++)
					for(int x=0; x<N_NEURON_LAYER; x++)
						weight[x][y][z] =0;
		}

		void viewNeurons()
		{
			for(int y=0; y<N_NEURON; y++)
			{
				for(int x=0; x<N_NEURON_LAYER; x++)
					std::cout << neurons[x][y] << " ";
				std::cout << std::endl;
			}
		}

		void viewWeight()
		{
			for(int x=0; x<N_NEURON_LAYER; x++)
			{
				for(int y=0; y<N_NEURON; y++)
				{
					for(int z=0; z<N_NEURON; z++)
					{
						std::cout << std::setw(15) << std::fixed << weight[x][y][z] << " ";
					}
					std::cout << std::endl;
				}
				std::cout << std::endl;
			}
		}

		int* calc(int input[N_NEURON])
		{
			int teacher[N_NEURON] = {0,0,0,0,0};
			return step(input,teacher);
		}

		int* teach(int input[N_NEURON], int teacher[N_NEURON])
		{
			return step(input,teacher,true);
		}

		int* step(int input[N_NEURON], int teacher[N_NEURON], bool teach = false)
		{
#ifdef DEBUG
			std::cout << "input" << std::endl;
#endif
			// input neurons
			for(int n=0; n<N_NEURON; n++)
			{
				neurons[0][n] = input[n];
			}
#ifdef DEBUG
			viewNeurons();
#endif

			// calculate each layers
#ifdef DEBUG
			std::cout << "calc" << std::endl;
#endif
			for(int layer=1; layer<N_NEURON_LAYER; layer++)
			{
				for(int y=0; y<N_NEURON; y++)
				{
					int t = 0;
					for(int x=0; x<N_NEURON; x++)
					{
						t += (int)(weight[layer-1][y][x] * neurons[layer-1][x]);
						if(t - 0.5 >= 0)
							neurons[layer][y] = 1;
						else
							neurons[layer][y] = 0;
					}
				}
			}
#ifdef DEBUG
			viewNeurons();
#endif

			if(teach)
			{
#ifdef DEBUG
				std::cout << "teach" << std::endl;
#endif
				// study
				for(int layer=0; layer<N_NEURON_LAYER; layer++)
				{
					for(int j=0; j<N_NEURON; j++)
					{
						bool flag = true;
						for(int i=0; i<N_NEURON; i++)
						{
							if(neurons[N_NEURON_LAYER-1][i] != teacher[i])
								flag = false;
						}
						if(!flag)
						{
							for(int i=0; i<N_NEURON; i++)
							{
								weight[layer][i][j] += 1.1 * (teacher[i] - neurons[N_NEURON_LAYER-1][i]) * neurons[layer][j];
							}
						}
					}
				}
#ifdef DEBUG
				viewWeight();
#endif
			}

			// return output layer
			return neurons[N_NEURON_LAYER-1];
		}

};

