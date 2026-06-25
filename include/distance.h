#pragma once
#include <vector>

class Distance {
	public:
		static float cosinze_distance(std::vector<float>& a, std::vector<float>& b);
		static float l2_distance(std::vector<float>& a, std::vector<float>& b);
		static float dot_prodct();
};