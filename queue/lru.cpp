#include <cassert>
#include <queue>
#include <unordered_map>

class LRUCache {
public:
    LRUCache(const int &capacity) {
        this->capacity = capacity;
    }
    
    int get(const int &key) {
        if (cache_data.find(key) == cache_data.end()) return KEY_NOT_FOUND;
        // If the key already exists, there needs to be an existing lru entry.
        // We will modify this lru entry.
        update_lru(key);
        return cache_data[key];
    }
    
    void put(const int &key, const int &value) {
        if (cache_data.find(key) == cache_data.end()) {
            if (cache_data.size() >= capacity) {
                // Select the lru entry to be evicted from cache.
                int removed_entry = lru.front();
                lru.pop();
                while (stale_lru_entries.find(removed_entry) != stale_lru_entries.end()) {
                    // If the current entry is present in stale_lru_entries, the entry is not lru.
                    // We will ignore this entry and process the next lru entry (if one exists).
                    stale_lru_entries[removed_entry]--;
                    if (stale_lru_entries[removed_entry] == 0) {
                        stale_lru_entries.erase(removed_entry);
                    }
                    if (lru.empty()) break;
                    removed_entry = lru.front();
                    lru.pop();
                }
                // Evicting the entry from cache.
                cache_data.erase(removed_entry);
            }
            lru.push(key);
        } else {
            // If the key already exists, there needs to be an existing lru entry.
            // We will modify this lru entry.
            update_lru(key);
        }
        cache_data[key] = value;
    }

    private:
    int capacity;
    int KEY_NOT_FOUND = -1;
    std::queue<int> lru;
    std::unordered_map<int, int> cache_data;
    // map that stores the number of stale queue entries for a 
    // key. key: key, val: frequency
    std::unordered_map<int, int> stale_lru_entries;

    void update_lru(const int &key) {
        // Update LRU order for keys that already exist in the cache.

        if (lru.front() == key) {
            // Simple case: when key was the lru entry.
            lru.pop();
        } else {
            // Complicated case: when key is not the lru entry.
            // We will mark the next lru entry for the key as stale, and
            // subsequent put operations won't evict this stale page.
            if (stale_lru_entries.find(key) != stale_lru_entries.end()) {
                stale_lru_entries[key]++;
            } else {
                stale_lru_entries[key] = 1;
            }
        }
        lru.push(key);
    }
};

int main() {
    /* Your LRUCache object will be instantiated and called as such:
    * LRUCache* obj = new LRUCache(capacity);
    * int param_1 = obj->get(key);
    * obj->put(key,value);
    */
    int capacity = 2;
    LRUCache* obj = new LRUCache(capacity);
    obj->put(1,1);
    obj->put(2,2);
    int val = obj->get(1);  assert(val == 1);
    obj->put(3,3);
    val = obj->get(2);      assert(val == -1);
    obj->put(4,4);
    val = obj->get(1);      assert(val == -1);
    val = obj->get(3);      assert(val == 3);
    val = obj->get(4);      assert(val == 4);
}
 