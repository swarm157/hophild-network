/*
 * HopfieldNetwork.h
 *
 *  Created on: 26 окт. 2020 г.
 *      Author: Пользователь
 */

#ifndef HOPFIELDNETWORK_H_
#define HOPFIELDNETWORK_H_

#include<vector>
#include<fstream>
#include<string>
#include<cstdio>
#include<iostream>

class HopfieldNetwork {
private:
	std::vector<std::vector<float>> data;
	bool sync = true;
	std::string fileName;
	std::vector<float> neurons;
	std::vector<float> lastNeurons;
	std::vector<float> example;
	std::vector<std::vector<float>> values;
public:
	HopfieldNetwork(int SIZE, std::string FILENAME);
	HopfieldNetwork(std::string FILENAME);
	~HopfieldNetwork();
	void run(int I);
	void learn();
	void learn(std::vector<std::vector<float>> data);
	void setInput(std::vector<float> INPUT) {
		if(neurons.size() >= INPUT.size()) {
			for(int i = 0; i < neurons.size(); i++) {
				neurons[i] = INPUT[i];
			}
		}
	}
	void copy(HopfieldNetwork COPY) {
		neurons = COPY.getInput();
		lastNeurons = COPY.getInput();
		values = COPY.getValues();
		for(int i = 0; i < values.size();i++) {
			values[i] = COPY.getValues()[i];
		}
	}
	void reCreate(int SIZE, std::string FILENAME) {
			fileName = FILENAME;

			neurons.clear();
			lastNeurons.clear();
			for(int i = 0; i < values.size(); i++) {
				values[i].clear();
			}
			values.clear();
			for(int i = 0; i < SIZE;i++) {
				neurons.push_back(0);
				lastNeurons.push_back(0);
			}
			for(int i = 0; i < SIZE; i++) {
				values.push_back(example);
				for(int o = 0; o < SIZE; o++) {
					values[i].push_back(0);
				}
			}
		}
	std::vector<float> getInput() {
		return neurons;
	}
	std::vector<std::vector<float>> getValues() {
		return values;
	}
	std::string getFileName() {
		return fileName;
	}
	void setFileName(std::string FILENAME) {
		fileName = FILENAME;
	}
	bool getSync() {
		return sync;
	}
	void setSync(bool SYNC) {
		sync = SYNC;
	}

	void save();
	void load();
};

#endif /* HOPFIELDNETWORK_H_ */
