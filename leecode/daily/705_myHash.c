#include <>

typedef struct {

} MyHashSet;

/** Initialize your data structure here. */

MyHashSet* myHashSetCreate() {

}

void myHashSetAdd(MyHashSet* obj, int key) {

}

void myHashSetRemove(MyHashSet* obj, int key) {

}

/** Returns true if this set contains the specified element */
bool myHashSetContains(MyHashSet* obj, int key) {

}

void myHashSetFree(MyHashSet* obj) {

}

/**
 * Your MyHashSet struct will be instantiated and called as such:
 * MyHashSet* obj = myHashSetCreate();
 * myHashSetAdd(obj, key);
 
 * myHashSetRemove(obj, key);
 
 * bool param_3 = myHashSetContains(obj, key);
 
 * myHashSetFree(obj);
*/
int main(void)
{
    MyHashSet* obj = myHashSetCreate();
    int key = 10;

    myHashSetAdd(obj, key);
    myHashSetRemove(obj, key);

    printf("contain %d ? %s\n", key, myHashSetContains(obj, key) ? "True" : "False");

    myHashSetFree(obj);
    return 0;
}
