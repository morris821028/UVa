class LFUCache {
public:
    struct Node {
        int freq;
        list< pair<int, int> > pList;
        Node(int f):freq(f) {}
    };
    list<Node> fList;
    int size;
    unordered_map<int, list<Node>::iterator> Rf;
    unordered_map<int, list< pair<int, int> >::iterator> Rp;
    LFUCache(int capacity) {
        size = capacity;
    }
    
    void incFreq(unordered_map<int, list<Node>::iterator>::iterator it, 
                unordered_map<int, list< pair<int, int> >::iterator>::iterator jt, 
                int key, int val) {
        int f = it->second->freq+1;
        list<Node>::iterator next_it = it->second;
        if (next_it != fList.end()) next_it++;
        // not found and insert
        if (next_it == fList.end() || next_it->freq != f)   
            next_it = fList.insert(next_it, Node(f));
        // found and update information
        if (it->second->pList.size() == 1)
            fList.erase(it->second);
        else
            it->second->pList.erase(jt->second);
        jt->second = next_it->pList.insert(next_it->pList.end(), make_pair(key, val));
        it->second = next_it;
    }
    int get(int key) {
        auto it = Rf.find(key);
        if (it == Rf.end())
            return -1;
        auto jt = Rp.find(key);
        int val = jt->second->second;
        incFreq(it, jt, key, val);
        return val;
    }
    void evict() {
        if (size == 0)
            return ;
        list<Node>::iterator t = fList.begin();
        list< pair<int, int> >::iterator kp = t->pList.begin();
        int key = kp->first, val = kp->second;
        Rf.erase(key);
        Rp.erase(key);
        t->pList.erase(kp);
        if (t->pList.size() == 0)
            fList.erase(t);
    }
    void put(int key, int val) {
        if (size == 0)
            return ;
        if (Rf.count(key)) {
            list<Node>::iterator t = Rf.find(key)->second;
            list< pair<int, int> >::iterator kp = Rp.find(key)->second;
            kp->second = val;
            incFreq(Rf.find(key), Rp.find(key), key, val);
            return ;
        }
        if (Rf.size() == size)
            evict();
        list<Node>::iterator next_it = fList.begin();
        list<pair<int, int>>::iterator next_jt;
        if (next_it == fList.end() || next_it->freq != 1)
            next_it = fList.insert(next_it, Node(1));
        next_jt = next_it->pList.insert(next_it->pList.end(), make_pair(key, val));
        Rf[key] = next_it;
        Rp[key] = next_jt;
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache obj = new LFUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
