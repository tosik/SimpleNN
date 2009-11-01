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


//#define DEBUG
#include "nn.cpp"

using namespace std;
#define SIZE 5

int main(void)
{
	NN nn;
	/** 入力信号 */
	static int input[SIZE][N_NEURON]   = {
		{ 1,0,0,1,0 },
		{ 0,1,0,1,0 },
		{ 1,0,1,0,1 },
		{ 0,1,1,1,1 },
		{ 1,1,1,0,1 },
	};
	/** 教師信号（期待する出力） */
	static int teacher[SIZE][N_NEURON]   = {
		{ 0,0,0,0,0 },
		{ 0,1,0,1,1 },
		{ 0,1,1,0,1 },
		{ 1,0,0,0,1 },
		{ 1,0,0,0,1 },
	};


#ifdef DEBUG
	cout << "teach" << endl;
#endif
	for(int cnt=0; cnt<80; cnt++)
	{
		for(int s=0; s<SIZE; s++)
		{
			bool flag = false;
			while(!flag)
			{
				flag = true;
				int *output = nn.teach(input[s],teacher[s]);
				for(int i=0; i<N_NEURON; i++)
					if(output[i] != teacher[s][i])
						flag = false;
#ifdef DEBUG
				cout << "---out---" << endl;
				for(int i=0; i<N_NEURON; i++)
					cout << output[i] << " " << endl;
				cout << "---------" << endl;
#endif
			}
		}
	}

#ifdef DEBUG
	cout << "calc" << endl;
#endif
	for(int s=0; s<SIZE; s++)
	{
		int *output = nn.calc(input[s]);
		cout << "---out---" << endl;
		for(int i=0; i<N_NEURON; i++)
			cout << output[i] << " " << endl;
		cout << "---------" << endl;
	}

}
