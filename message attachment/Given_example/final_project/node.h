#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

class Node {
	public:
		int x;
		int y;
		int f;

		Node(int n = 0, int m = 0) {
            x = n;
            y = m;
            f = 0;
		}

        Node(const Node& node) {
            x = node.x;
            y = node.y;
            f = node.f;
        }

		Node up();
		Node down();
		Node left();
		Node right();

        bool operator==(const Node& node) {
            return this->x == node.x && this->y == node.y && this->f == node.f;
        }

        bool operator!=(const Node& node) {
            return this->x != node.x || this->y != node.y || this->f != node.f;
        }

        void operator=(const Node& node) {
            this->x = node.x;
            this->y = node.y;
            this->f = node.f;
        }

        static void swap(Node& a, Node& b) {
            Node tmp = a;
            a = b;
            b = tmp;
        }
};

#endif // NODE_H_INCLUDED
