#include "ivf.h"
#include "distance.h"
#include "memory.h"
#include <limits>
#include <cstdlib>
#include <iostream>


std::vector<std::vector<float>> ivf::kmeanspp(std::vector<IndexItem>& dataset, int k){
	std::vector<std::vector<float>> centroids;
    int n = dataset.size();
    if (n == 0 || k <= 0) {
        return centroids;
    }

    k = std::min(k, n);
	int first = rand() % n;
	centroids.push_back(dataset[first].embedding);
	std::vector<float> min_distance_list(n);

    while( centroids.size() < k){
        float distance = 0.0f;
        for(int i = 0; i < n; i++){
            float minDist = std::numeric_limits<float>::max();
            for( auto& c: centroids){
                float d = Distance::cosine_distance(dataset[i].embedding, c);
                minDist = std::min(d,minDist);
            }
            min_distance_list[i] = minDist * minDist;
            distance += min_distance_list[i];
        }	
        
        float r = ((float) rand() / RAND_MAX) * distance;
        float cumulative = 0.0f;

        for (int i = 0; i < n; i++) {
            cumulative += min_distance_list[i];
            if (cumulative >= r) {
                centroids.push_back(dataset[i].embedding);
                break;
            }
        }
    }
	return centroids;
}

std::vector<std::vector<float>> ivf::kmean (std::vector<IndexItem>& dataset,int k, int max_iterations){
    std::vector<std::vector<float>> centroids = ivf::kmeanspp(dataset, k);
    if (centroids.empty()) {
        return centroids;
    }

    int Nc = centroids.size();
    int n = dataset.size();
    int dim = (dataset[0].embedding).size();
    std::vector<int> centroids_mapping(n,0);

    for(int iter = 0; iter < max_iterations; iter++){
       std::vector<std::vector<float>> new_centroids(Nc, std::vector<float>(dim, 0.0f));
       std::vector<int> count(Nc,0);
        for(int i = 0; i < n; i++){
            int current = 0;
            float minDist = std::numeric_limits<float>::max();
            for(int j = 0; j < Nc; j++){
                float d = Distance::cosine_distance(dataset[i].embedding, centroids[j]);
                if(d < minDist){
                    minDist = d;
                    current = j;
                }
            }
            centroids_mapping[i] = current;
            count[current]++;
            for(int j = 0; j < dim; j++){
                new_centroids[current][j] += dataset[i].embedding[j];
            }
        }

        for(int i = 0; i < static_cast<int>(count.size()); i++){
            if(count[i] == 0){
                new_centroids[i] = centroids[i];
                continue;
            }
            for(int j = 0; j < dim; j++){
                new_centroids[i][j] /= count[i];
            }
        }
        centroids.swap(new_centroids);
    }

    return centroids;
}

IVFIndex ivf::ivf_index(std::vector<IndexItem>& dataset, int k){
    IVFIndex index;
    index.centroid = ivf::kmean(dataset,k);
    index.list.resize(index.centroid.size());
    for(int i = 0; i < static_cast<int>(dataset.size()); i++){
        int best = 0;
        float mini = std::numeric_limits<float>::max();
        for(int j = 0; j < static_cast<int>(index.centroid.size()); j++){
            float distance = Distance::cosine_distance(index.centroid[j], dataset[i].embedding);
            if(mini > distance){
                mini = distance;
                best = j;
            }
        }
        index.list[best].push_back(dataset[i].internal_id);
    }
    return index;
}

StoreItem ivf::search(std::vector<float> query,IVFIndex indexes, std::vector<IndexItem> items, std::vector<StoreItem> store_items){
    if (indexes.centroid.empty() || indexes.list.empty() || items.empty() || store_items.empty()) {
        return {};
    }

    int centroid_selection = 0;
    float centroid_min_distance = std::numeric_limits<float>::max();
    int centroids_area = indexes.centroid.size();
    for (int i = 0; i < centroids_area; i++) {
        float distance = Distance::cosine_distance(query, indexes.centroid[i]);
        if (distance < centroid_min_distance) {
            centroid_min_distance = distance;
            centroid_selection = i;
        }
    }
    std::cout << "selected centroids is " << centroid_selection << std::endl;

    if (indexes.list[centroid_selection].empty()) {
        return {};
    }

    uint32_t nearest_internal_id = indexes.list[centroid_selection][0];
    float nearest_distance = std::numeric_limits<float>::max();
    for (uint32_t internal_id : indexes.list[centroid_selection]) {
        bool found = false;
        IndexItem currentIndex;
        for (const auto& x : items) {
            if (x.internal_id == internal_id) {
                currentIndex = x;
                found = true;
                break;
            }
        }
        if (!found) {
            continue;
        }

        float distance = Distance::cosine_distance(query, currentIndex.embedding);
        if (distance < nearest_distance) {
            nearest_distance = distance;
            nearest_internal_id = internal_id;
        }
    }

    for (const auto& y : store_items) {
        if (y.internal_id == nearest_internal_id) {
            return y;
        }
    }

    return {};
}
