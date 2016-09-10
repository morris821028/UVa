/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string ret = "";
        encode(root, ret);
        return ret;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        stringstream ss(data);
        return decode(ss);
    }
private:
    string int2str(int &i) {
        string s;
        stringstream ss(s);
        ss << i;
        return ss.str();
    }
    int str2int(string &s) {
        int x;
        sscanf(s.c_str(), "%d", &x);
        return x;
    }
    void encode(TreeNode *u, string &ret) {
        if (u == NULL) {
            ret += "$ ";
            return ;
        }
        
        ret += int2str(u->val) + " ";
        encode(u->left, ret);
        encode(u->right, ret);
    }
    TreeNode* decode(stringstream &ss) {
        string token;
        ss >> token;
        if (token == "$")
            return NULL;
        TreeNode *u = (TreeNode *) malloc(sizeof(TreeNode));
        u->val = str2int(token);
        u->left = decode(ss);
        u->right = decode(ss);
        return u;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
