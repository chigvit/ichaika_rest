#pragma once

#include <iostream>
#include <list>
#include <unordered_map>
#include <mutex>


using namespace std;

class LRUCache {
private:
    int capacity;
    list<int> cache;
    unordered_map<int, pair<int, list<int>::iterator>> cacheMap;
    mutex mtx;

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }

    int get(int key) {
        lock_guard<mutex> lock(mtx);

        if (cacheMap.find(key) == cacheMap.end()) {
            return -1;
        }

        cache.splice(cache.begin(), cache, cacheMap[key].second);
        return cacheMap[key].first;
    }

    void put(int key, int value) {
        lock_guard<mutex> lock(mtx); 

        if (cacheMap.find(key) != cacheMap.end()) {
            cacheMap[key].first = value;
            cache.splice(cache.begin(), cache, cacheMap[key].second);
            return;
        }

        if (cache.size() == capacity) {
            int leastRecentlyUsedKey = cache.back();
            cache.pop_back();
            cacheMap.erase(leastRecentlyUsedKey);
        }

        cache.push_front(key);
        cacheMap[key] = make_pair(value, cache.begin());
    }
};
