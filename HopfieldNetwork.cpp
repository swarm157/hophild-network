/*
 * HopfieldNetwork.cpp
 *
 *  Created on: 26 окт. 2020 г.
 *      Author: Пользователь
 */

#include "HopfieldNetwork.h"

HopfieldNetwork::HopfieldNetwork(int SIZE, std::string FILENAME) {
	reCreate(SIZE, FILENAME);

}
HopfieldNetwork::HopfieldNetwork(std::string FILENAME) {
	fileName = FILENAME;
	load();

}

HopfieldNetwork::~HopfieldNetwork() {
	neurons.clear();
	lastNeurons.clear();
	for(int i = 0 ; i < values.size();i++) {
		values[i].clear();
	}
	values.clear();
	// TODO Auto-generated destructor stub
}

void HopfieldNetwork::run(int I) {
	for(int i = 0 ; i < lastNeurons.size();i++) {
		lastNeurons[i] = 0;
	}
	int g = 0;
	while(true) {
		if((I>0) && (I==g)) {
			break;
		}

		bool exit = false;
		for(int i = 0; i < data.size();i++) {

			if(neurons==data[i]) {
				exit = true;
				break;
			}
		}
		if(exit)
			break;
		lastNeurons = neurons;
		for(int i = 0; i < neurons.size(); i++) {
			neurons[i] = 0;
		}

		for(int i = 0; i < neurons.size(); i++) {
			for(int o = 0; o < neurons.size(); o++) {
				neurons[i]+=lastNeurons[o]*values[i][o];
			}
			if(neurons[i]>0) {
				neurons[i] = 1;
			} else {
				neurons[i] = -1;
			}
		}

		g++;
	}




}

void HopfieldNetwork::learn() {
	std::ifstream loader;
	loader.open(fileName+".hfnset");
	std::string buffer;
	loader >> buffer;
	int size = std::atoi(buffer.c_str());
	loader >> buffer;
	int size2 = std::atoi(buffer.c_str());
	if(size==neurons.size()) {
		for(int i = 0; i < data.size(); i++) {
				data[i].clear();
			}
			data.clear();
		std::vector<float> dExample;

		for(int i = 0; i < size2; i++) {
			data.push_back(dExample);
			for(int o = 0; o < size; o++) {
				loader >> buffer;
				data[data.size()-1].push_back(std::atoi(buffer.c_str()));
			}
		}
		learn(data);

	} else {
		std::cerr << "error, file not correct" << std::endl;
		std::cerr << "range " << neurons.size() << " input size " << size << " input size2 " << size2 << std::endl;
	}
}
void HopfieldNetwork::learn(std::vector<std::vector<float>> dat) {
	data = dat;
	for(int i = 0; i < values.size(); i++) {
		for(int o = 0; o < values.size(); o++) {
			for(int p = 0; p < dat.size(); p++) {
				values[i][o]+=dat[p][o]*dat[p][i];
			}
			values[i][o]/=dat[0].size();
		}
	}



	for(int i = 0 ;i < values.size(); i++)
				values[i][i] = 0;
}

void HopfieldNetwork::save() {
	std::ofstream saver;
	saver.open(fileName+".hfn");
	saver << values.size();
	saver << std::endl;
	saver << sync;
	saver << std::endl;
	for(int i = 0 ; i < values.size(); i++) {
		for(int o = 0 ; o < values.size(); o++) {
			saver << values[i][o] << " ";
		}
		saver << std::endl;
	}
}

void HopfieldNetwork::load() {
	std::ifstream loader;
	loader.open(fileName+".hfn");
	std::string buffer;
	loader >> buffer;
	int size = std::atoi(buffer.c_str());
	loader >> buffer;
	sync = std::atoi(buffer.c_str());
	reCreate(size, fileName);
	for(int i = 0; i < values.size(); i++) {
		for(int o = 0; o < values.size(); o++) {
			loader >> buffer;
			values[i][o] = std::atof(buffer.c_str());
		}
	}
	loader.close();
}


