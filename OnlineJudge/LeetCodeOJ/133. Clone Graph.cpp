/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    UndirectedGraphNode *newNode(int label, UndirectedGraphNode *u) {
        UndirectedGraphNode *ret = new UndirectedGraphNode(label);
        ret->neighbors.resize(u->neighbors.size());
        return ret;
    }
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if (node == NULL)
            return NULL;
            
        queue<UndirectedGraphNode*> Q;
        map<int, UndirectedGraphNode*> visited;
        UndirectedGraphNode *u = newNode(node->label, node), *v;
        UndirectedGraphNode *ret = u;
        Q.push(u), Q.push(node);
        visited[u->label] = u;
        while (!Q.empty()) {
            u = Q.front(), Q.pop();
            v = Q.front(), Q.pop();
            for (int i = 0; i < v->neighbors.size(); i++) {
                UndirectedGraphNode* e = v->neighbors[i];
                if (visited.count(e->label)) {
                    u->neighbors[i] = visited[e->label];
                } else {
                    UndirectedGraphNode* t = newNode(e->label, e);
                    visited[t->label] = t;
                    u->neighbors[i] = t;
                    Q.push(t), Q.push(e);
                }
            }
        }
        return ret;
    }
}; 
