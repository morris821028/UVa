class WordDictionary {
public:
    struct Node {
        Node *next[26];
        int cnt, label;
        void init() {
            cnt = label = 0;
            memset(next, 0, sizeof(next));
        }
    };
    Node *root;
    Node* newNode() {
        // Node *p = &nodes[size++];
        Node *p = new Node();
        p->init();
        return p;
    }
    WordDictionary() {
        root = newNode();
    }
    int toIndex(char c) {
        return c - 'a';
    }
    // Adds a word into the data structure.
    void addWord(string word) {
        Node *u = root;
        for (int i = 0; i < word.length(); i++) {
            int c = toIndex(word[i]);
            if (u->next[c] == NULL)
                u->next[c] = newNode();
            u = u->next[c];
        }
        u->label |= 1;
    }

    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool dfs(Node *u, int idx, string &word) {
        if (u == NULL)
            return false;
        if (idx == word.length())
            return u->label != 0;
        if (word[idx] == '.') {
            for (int i = 0; i < 26; i++) {
                if (dfs(u->next[i], idx+1, word))
                    return true;
            }
        } else {
            int c = toIndex(word[idx]);
            if (dfs(u->next[c], idx+1, word))
                return true;
        }
        return false;
    }
    bool search(string word) {
        return dfs(root, 0, word);
    }
};

// Your WordDictionary object will be instantiated and called as such:
// WordDictionary wordDictionary;
// wordDictionary.addWord("word");
// wordDictionary.search("pattern");
