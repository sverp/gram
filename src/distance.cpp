#include "distance.h"
#include <cmath>
#include <stdexcept>

float Distance::cosine_distance(std::vector<float>& a, std::vector<float>& b){
	if( a.size() != b.size()){
		throw std::invalid_argument("vectors must be of smame length");
	}

	int n = a.size();
	float dot = 0;
	float Am = 0;
	float Bm = 0;
	for(int i = 0; i < n; i++){
		dot += a[i]*b[i];
		Am += a[i]*a[i];
		Bm += b[i]*b[i];
	}
	float distance = dot / (std::sqrt(Am) * std::sqrt(Bm));
	return 1.0f - distance;
}




float Distance::l2_distance(std::vector<float>& a, std::vector<float>& b){
	if( a.size() != b.size()){
		throw std::invalid_argument("vectors must be of same length");
	}

	int n = a.size();
	float distance = 0;

	for(int i = 0; i < n; i++){
		distance += (a[i]-b[i])*(a[i]-b[i]);
	}

	return distance;
	
}
