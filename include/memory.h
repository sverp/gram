#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <cstdint>

struct IndexItem {
    uint32_t internal_id;
    std::vector<float> embedding;
};

struct StoreItem {
    uint32_t internal_id;
    std::string external_id;
    std::string data;
    std::string metadata;
};

struct itemData {
    std::string id;
    std::vector<float> embedding;
    std::string data;
    std::string metadata;
};

class Memory {
	private:
		uint32_t next_id;
	public:
		Memory() : next_id(0) {}
		uint32_t allocate_id();
		void split(const std::vector<itemData>& dataset, std::vector<IndexItem>& indexItems, std::vector<StoreItem>& items);
};

