

typedef struct {

} MyHashMap;

/** Initialize your data structure here. */

MyHashMap* myHashMapCreate() {

}

/** value will always be non-negative. */
void myHashMapPut(MyHashMap* obj, int key, int value) {

}

/** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
int myHashMapGet(MyHashMap* obj, int key) {

}

/** Removes the mapping of the specified value key if this map contains a mapping for the key */
void myHashMapRemove(MyHashMap* obj, int key) {

}

void myHashMapFree(MyHashMap* obj) {

}

/**
 * Your MyHashMap struct will be instantiated and called as such:
 * MyHashMap* obj = myHashMapCreate();
 * myHashMapPut(obj, key, value);
 
 * int param_2 = myHashMapGet(obj, key);
 
 * myHashMapRemove(obj, key);
 
 * myHashMapFree(obj);
*/