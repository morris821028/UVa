class TrieNode {
public:
    // Initialize your data structure here.
    TrieNode *next[26];
    int end;
    TrieNode() {
        memset(next, 0, sizeof(next));
        end = 0;
    }
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string word) {
        TrieNode *u = root;
        for (int i = 0; i < word.length(); i++) {
            int c = word[i]-'a';
            if (u->next[c] == NULL)
                u->next[c] = new TrieNode();
            u = u->next[c];
        }
        u->end |= 1;
    }

    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode *u = root;
        for (int i = 0; i < word.length(); i++) {
            int c = word[i]-'a';
            if (u->next[c] == NULL)
                return false;
            u = u->next[c];
        }
        return u->end != 0;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode *u = root;
        for (int i = 0; i < prefix.length(); i++) {
            int c = prefix[i]-'a';
            if (u->next[c] == NULL)
                return false;
            u = u->next[c];
        }
        return true;
    }

private:
    TrieNode* root;
};

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");
