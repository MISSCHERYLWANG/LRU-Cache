#include <iostream>
#include <unordered_map>
#include <list>

class LRUCache {
public:
    LRUCache(int capacity) {
        size = capacity;
    }
    int get(int key) {
        /* *
         * Get the value of the key if the key exists in the cache, 
         * otherwise return -1.
         * */
        auto it = m.find(key);
        if (it == m.end()) {
            return -1;
        }
        // put the node to l's head;
        l.splice(l.begin(), l, it->second);
        return it->second->second;
    }
    void set(int key, int value) {
        /**
         * Set or insert the value if the key is not already present. 
         * When the cache reached its capacity, 
         * it should invalidate the least recently used item 
         * before inserting a new item.
         * */
        auto it = m.find(key);
        if (it != m.end()) {
            l.erase(it->second);
        }
        l.push_front(std::make_pair(key, value));
        m[key] = l.begin();
        if (m.size() > size) {
            int k = l.rbegin()->first;
            // erase by key
            m.erase(k);
            l.pop_back();
        }
    }
private:
    int size;
    // l mantains the least recently used node.
    std::list<std::pair<int, int>> l;
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> m;
};

int main()
{
    LRUCache *lru = new LRUCache(2);
    lru->set(1, 1);
    lru->set(2, 2);
    std::cout << lru->get(1) << std::endl;
    lru->set(3, 3);
    std::cout << lru->get(2) << std::endl;
}