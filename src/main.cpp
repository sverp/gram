#include <iostream>
#include <vector>
#include "ivf.h"
#include "memory.h"


std::vector<itemData> ndata = {
    {
        "item_1",
        {0.12f, 0.45f, 0.33f, 0.91f, 0.27f, 0.66f, 0.51f, 0.08f},
        "The quick brown fox jumps over the lazy dog.",
        "category:animals"
    },
    {
        "item_2",
        {0.77f, 0.14f, 0.58f, 0.22f, 0.49f, 0.31f, 0.63f, 0.40f},
        "Artificial intelligence is transforming modern technology.",
        "category:technology"
    },
    {
        "item_3",
        {0.05f, 0.88f, 0.44f, 0.19f, 0.72f, 0.35f, 0.60f, 0.11f},
        "Mountains and rivers shape the geography of a region.",
        "category:geography"
    },
    {
        "item_4",
        {0.91f, 0.23f, 0.17f, 0.54f, 0.36f, 0.69f, 0.28f, 0.47f},
        "Basketball players train daily to improve their skills.",
        "category:sports"
    },
    {
        "item_5",
        {0.39f, 0.62f, 0.15f, 0.83f, 0.20f, 0.57f, 0.74f, 0.09f},
        "The solar system consists of planets orbiting a star.",
        "category:science"
    },
    {
        "item_6",
        {0.48f, 0.07f, 0.92f, 0.34f, 0.59f, 0.13f, 0.80f, 0.26f},
        "Cooking at home can be healthier than eating outside.",
        "category:lifestyle"
    },
    {
        "item_7",
        {0.18f, 0.73f, 0.29f, 0.64f, 0.41f, 0.52f, 0.10f, 0.95f},
        "Music can influence mood and concentration.",
        "category:arts"
    },
    {
        "item_8",
        {0.66f, 0.21f, 0.53f, 0.12f, 0.84f, 0.37f, 0.45f, 0.70f},
        "Programming requires logical thinking and practice.",
        "category:education"
    },
    {
        "item_9",
        {0.24f, 0.56f, 0.68f, 0.03f, 0.77f, 0.42f, 0.19f, 0.61f},
        "Cities grow as industries and populations expand.",
        "category:economics"
    },
    {
        "item_10",
        {0.50f, 0.32f, 0.11f, 0.97f, 0.26f, 0.48f, 0.73f, 0.14f},
        "Space exploration helps us understand the universe.",
        "category:space"
    }
};


int main() {
    Memory mem;

    std::vector<IndexItem> indexItems;
    std::vector<StoreItem> storeItems;

    mem.split(ndata, indexItems, storeItems);

    IVFIndex indexes = ivf::ivf_index(indexItems, 3);

    for(int i = 0; i < indexes.centroid.size(); i++){
        for(int j = 0; j < indexes.centroid[0].size(); j++){
            std::cout << indexes.centroid[i][j] << " ";
        }
        std::cout << "\n";
        
    }
    
    for(int i = 0; i < indexes.list.size(); i++){
    std::cout << "list[" << i << "]: ";
    for(int j = 0; j < indexes.list[i].size(); j++){
        std::cout << indexes.list[i][j] << " ";
    }
    std::cout << "\n";
    }
    std::vector<float> query = {0.45f, 0.62f, 0.11f, 0.89f, 0.24f, 0.51f, 0.70f, 0.12f};
    StoreItem res = ivf::search(query,indexes, indexItems, storeItems);
    std::cout << res.data << std::endl;



    return 0;
}