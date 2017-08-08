class AllOne {
private:
    struct Node {
        int val;
        unordered_set<string> key;
        Node(int val, string k): val(val) {key.insert(k);}
    };
    list<Node> freq;
    unordered_map<string, list<Node>::iterator> R;
public:
    /** Initialize your data structure here. */
    AllOne() {
        
    }
    
    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
        auto it = R.find(key);
        if (it != R.end()) {
            auto jt = it->second;
            int f = it->second->val+1;
            it->second->key.erase(key);
            jt++;
            if (jt == freq.end() || jt->val != f)
                jt = freq.insert(jt, Node(f, key));
            else
                jt->key.insert(key);
            
            if (it->second->key.size() == 0)
                freq.erase(it->second);
            it->second = jt;
        } else {
            int f = 1;
            list<Node>::iterator jt;
            if (freq.size() == 0 || freq.begin()->val != f)
                jt = freq.insert(freq.begin(), Node(f, key));
            else
                freq.begin()->key.insert(key), jt = freq.begin();
            
            R[key] = jt;
        }
    }
    
    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        auto it = R.find(key);
        if (it != R.end()) {
            auto jt = it->second;
            auto kt = it->second;
            int f = it->second->val-1;
            it->second->key.erase(key);
            if (f > 0) {
                if (kt != freq.begin()) kt--;
                if (jt == freq.begin())
                    kt = freq.insert(freq.begin(), Node(f, key));
                else if (kt->val != f)
                    kt = freq.insert(jt, Node(f, key));
                else
                    kt->key.insert(key);
            } else {
                R.erase(key);
            }
            
            if (it->second->key.size() == 0)
                freq.erase(it->second);
            if (f > 0)
                it->second = kt;
        }
    }
    
    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        return freq.size() == 0 ? "" : *(freq.rbegin()->key.begin());
    }
    
    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        return freq.size() == 0 ? "" : *(freq.begin()->key.begin());
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne obj = new AllOne();
 * obj.inc(key);
 * obj.dec(key);
 * string param_3 = obj.getMaxKey();
 * string param_4 = obj.getMinKey();
 */
