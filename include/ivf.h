#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <cstdint>
#include "memory.h"

struct IVFIndex {
    std::vector<std::vector<float>> centroid;
    std::vector<std::vector<uint32_t>> list;
};

struct Item {
    std::string id;
    std::vector<float> embedding;
    std::string data;                  
    std::unordered_map<std::string, std::string> metadata;
};

class ivf {
    public:
		static std::vector<std::vector<float>> kmeanspp(std::vector<IndexItem>& dataset, int k);
        static std::vector<std::vector<float>> kmean(std::vector<IndexItem>& dataset, int k, int max_iterations = 100);
		static IVFIndex ivf_index(std::vector<IndexItem>& dataset, int k);
        static StoreItem search(std::vector<float> query,IVFIndex indexes, std::vector<IndexItem> items, std::vector<StoreItem> storeItems);
} ;
