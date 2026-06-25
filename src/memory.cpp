#include <vector>
#include <unordered_map>
#include <string>
#include <cstdint>
#include "memory.h"


uint32_t Memory::allocate_id(){
	return next_id++;
}

void Memory::split(
    const std::vector<itemData>& dataset,
    std::vector<IndexItem>& indexItems,
    std::vector<StoreItem>& storeItems
) {
    for (const itemData& item : dataset) {
        uint32_t id = allocate_id();

        indexItems.push_back({id, item.embedding});
        storeItems.push_back({id, item.id, item.data, item.metadata});
    }
}