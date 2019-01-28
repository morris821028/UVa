#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-6;
struct Pt {
	int32_t x, y;
	Pt(int32_t a = 0, int32_t b = 0):x(a), y(b) {}
    Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
    Pt operator+(const Pt &a) const {
        return Pt(x + a.x, y + a.y);
    }
    Pt operator*(const double a) const {
        return Pt(x * a, y * a);
    }
    bool operator==(const Pt &a) const {
    	return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
    }
    bool operator<(const Pt &a) const {
        if (fabs(x - a.x) > eps)
            return x < a.x;
        if (fabs(y - a.y) > eps)
            return y < a.y;
        return false;
    }
    double dist(Pt &p) {
    	return hypot(x-p.x, y-p.y);
	}
};

struct Seg {
    Pt s, e;
    Seg(Pt s = Pt(0, 0), Pt e = Pt(0, 0)):
    	s(s), e(e) {}
};

static inline int fastIntersection(Seg &sa, Seg &sb) {
	Pt a = sa.e - sa.s;
	Pt b = sb.s - sb.e;
	Pt c = sa.s - sb.s;
	int64_t alphaX = (int64_t) b.y*c.x - (int64_t) b.x*c.y;
	int64_t Y = (int64_t) a.y*b.x - (int64_t) a.x*b.y;
	if (Y == 0) {						// parallel
		int64_t betaX = (int64_t) a.x*c.y - (int64_t) a.y*c.x;
		if (alphaX != 0 || betaX != 0)	// no-colinear
			return 0;
		if (a.x == 0)
			return max(min(sa.s.y, sa.e.y), min(sb.s.y, sb.e.y)) <= 
				min(max(sa.s.y, sa.e.y), max(sb.s.y, sb.e.y));
		else
			return max(min(sa.s.x, sa.e.x), min(sb.s.x, sb.e.x)) <= 
				min(max(sa.s.x, sa.e.x), max(sb.s.x, sb.e.x));
		return 0;
	}
	if (Y > 0) {
		if (alphaX < 0 || alphaX > Y)
			return 0;
	} else {
		if (alphaX > 0 || alphaX < Y)
			return 0;
	}
	int64_t betaX = (int64_t) a.x*c.y - (int64_t) a.y*c.x;
	if (Y > 0) {
		if (betaX < 0 || betaX > Y)
			return 0;
	} else {
		if (betaX > 0 || betaX < Y)
			return 0;
	}
	return 1;
}


#define MAX_POINTS 100000

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define ABS(x) ((x)>0 ? (x) : (-(x)))

typedef struct {
	int64_t x;
	int64_t y;
} T_POINT;
 
/* Warning: 
	x*y must fit into integer. Thus coordinates <= 32000. */
/* Notation:  
 * 	point[0], point[1], ... point[n-1]         
 *	segment[i] is between point[i]--point[i+1],  thus segment[n-1] is between point[n-1]--point[0]
 */
 
/* vrcholy mnohouhelniku */
int n;
T_POINT point[MAX_POINTS];
 
 
/******************************************************************************* 
 * Beautiful solution for testing segment intersection 
 * -- we do not need floats, everything done with integers and absolute precision 
 *
 */
 
 
/* Returns [-val, 0 val] if consecutive vectors (p1 - p0) and (p2 - p1) turns to the left, straight, right
 * we are using features of cross product									*/
int direction(T_POINT p0, T_POINT p1, T_POINT p2){
	long long value;

	value = (p1.x-p0.x)*(p2.y-p0.y) - (p2.x-p0.x)*(p1.y-p0.y);
	if (value > 0) return 1;
	if (value < 0) return -1;
	return 0;
}
 
/* We assume, that points p1, p2, p3 are collinear. 
 * Procedure returns 1, if p3 lies between endpoints p1,p2 (that is on segment).
 * Otherwise returns 0.  
 */
int on_segment(T_POINT p1, T_POINT p2, T_POINT p3){
  if( MIN(p1.x, p2.x) <= p3.x && p3.x <= MAX(p1.x, p2.x) &&
      MIN(p1.y, p2.y) <= p3.y && p3.y <= MAX(p1.y, p2.y) )
		return 1;
  else
		return 0;
}
 
/*  Returns y coordinate of a point lying on a line determined by segment (with exception for vertical segment).
 */
double y_of_segment(int seg, double x){
	int64_t x1 = point[seg].x;
	int64_t y1 = point[seg].y;
	int64_t x2 = point[(seg+1) % n].x;
	int64_t y2 = point[(seg+1) % n].y;
 
	if(x1==x2) {  /* segment is vertical - we rotate everything by epsilon clockwise */
		if( x == x1 ) return MIN(y1,y2);
		if( x < x1 ) return -INFINITY;
		else	     return +INFINITY;
	}
	else 
		return y1+(x-x1)/(x2-x1)*(y2-y1);
}
 
/* Returns 1 if seg1 is above seg2. 0 Otherwise.
 *
 * -- segment must be strictly above, if both segments on one line, above == FALSE.
 */
char segment_above(int seg1, int seg2, double x){
	double y1, y2;
	T_POINT p1, p2, p3, p4, pom, pmax, pmin;
 
	y1 = y_of_segment(seg1, x);
	y2 = y_of_segment(seg2, x);
	if( ABS(y1 - y2) < 0.000001 ) { 
		/* segments intersects or have common endpoint */
		p1 = point[seg1];
		p2 = point[(seg1+1)%n];
		p3 = point[seg2];
		p4 = point[(seg2+1)%n];
		/* Notation: number points of each segment from left to right */
		if( ( p1.x > p2.x ) || ( p1.x == p2.x && p1.y > MIN(p1.y, p2.y)  ))
			{ pom = p1; p1 = p2; p2 = pom; }
		if( ( p3.x > p4.x ) || ( p3.x == p4.x && p3.y > MIN(p3.y, p4.y)  ))
			{ pom = p3; p3 = p4; p4 = pom; }

		/* Check it for other x -- try other endpoints of segments */
		pmax = p2; if(p2.x < p4.x)  pmax = p4;
		pmin = p1; if(p3.x < p1.x)  pmin = p3;
		if( pmax.x > x ) {
			y1 = y_of_segment(seg1, pmax.x);
			y2 = y_of_segment(seg2, pmax.x);
		} else if( pmin.x < x ) {
			y1 = y_of_segment(seg1, pmin.x);
			y2 = y_of_segment(seg2, pmin.x);
		}
	}
	/* in all cases */
	return( y1 > y2 );	
}

/* Compute if segment p_1p_2 intersects segment p_3p_4 
 * Returns 1 if intersects, 0 otherwise
 */
int intersect(T_POINT p1, T_POINT p2, T_POINT p3, T_POINT p4){
 
	int d1 = direction(p3, p4, p1);
	int d2 = direction(p3, p4, p2);
	int d3 = direction(p1, p2, p3);
	int d4 = direction(p1, p2, p4);
 
	if(  ((d1>0 && d2 <0) || (d1<0 && d2>0)) &&
	     ((d3>0 && d4 <0) || (d3<0 && d4>0)) ) 
		return 1;
	else if (d1 == 0 && on_segment(p3, p4, p1)) 
		return 1;
	else if (d2 == 0 && on_segment(p3, p4, p2)) 
		return 1;
	else if (d3 == 0 && on_segment(p1, p2, p3)) 
		return 1;
	else if (d4 == 0 && on_segment(p1, p2, p4)) 
		return 1;
	else return 0;
}
 
 
 
/*************************************************************************************
 * Binary search tree for storing status on sweepline 
 *
 */
 
typedef struct node {
	int seg; /* index of segment on the sweepline, key value is computed dynamicly for X coordinate */
	struct node *down;
	struct node *up;
} T_NODE;
 
/* binary search tree */
T_NODE *root;
int nodes_last;
T_NODE nodes[MAX_POINTS]; /* memory chunk for storing nodes */
int empty_nodes_last;
T_NODE *empty_nodes[MAX_POINTS]; /* stack of empty nodes */
 
 
void init_bin_tree() {
	root = NULL;
	nodes_last = -1;
	empty_nodes_last = -1;
}
 
T_NODE* new_node(int seg) {
	T_NODE * node;
 
	if( empty_nodes_last < 0) {
		node = &nodes[++nodes_last];
		assert(nodes_last < MAX_POINTS);
	} else {
		node = empty_nodes[empty_nodes_last--];
	}
	node->seg = seg;
	node->up = NULL;
	node->down = NULL;
	return node;
}
 
void print_tree(T_NODE *node, int depth){
	int i;
	if(node != NULL)
	{
		print_tree( node->up, depth+1);
		for(i=0; i<5*depth; i++)
			printf(" ");
		printf("seg%d\n", node->seg);
		print_tree( node->down, depth+1);
	}
}
 
/* call it as root = insert_node(root, seg, x); */
T_NODE* insert_node(T_NODE *node, int seg, int x){
	if(node == NULL)
		return new_node(seg);
	else {
		if( segment_above( seg, node->seg, x)  ) {
			node->up = insert_node(node->up, seg, x);
		}
		else {
			node->down = insert_node(node->down, seg, x);
		}
		return node;
	}
}
 
/* call it as root = delete_node(root, seg, x); */
T_NODE* delete_node(T_NODE* node, int seg, int x){
	T_NODE* repl_node;
 
	if(node == NULL)
		return NULL;
	else {
	  if(node->seg == seg) {
		/* delete_node node */
		if(node->down == NULL) {
			empty_nodes[++empty_nodes_last] = node;
			return node->up;
		} else if(node->up == NULL) {
			empty_nodes[++empty_nodes_last] = node;
			return node->down;
		} else {
			repl_node = node->down;
			while( repl_node->up != NULL) repl_node = repl_node->up;				
			node->seg = repl_node->seg;
			node->down = delete_node(node->down, node->seg, x);
			return node;
		}
	  }
	  else {
		if( segment_above(seg, node->seg, x) ) {
			node->up = delete_node(node->up, seg, x);
		}
		else {
			node->down = delete_node(node->down, seg, x);
		}
		return node;
	  }  
	}
}
 
/* Returns segment id of segment above segment "seg" on sweep line with coordinate x.
 * Or -1 if it is top segment. 
 */
int above(int seg, int x){
	T_NODE* node = root;
	T_NODE* parent_above = NULL;
 
	while (node != NULL && node->seg != seg){
		if( segment_above( seg, node->seg, x) ) {
			node = node->up;		
		}
		else {
			parent_above = node;
			node = node->down;
		}
	}
	/* we found the node with seg */
	if (node->up == NULL) {
		return (parent_above ? parent_above->seg : -1 ) ;
	}
	else {
		node = node->up;
		while (node->down != NULL)
			node = node->down;
		return node->seg;
	}
}
 
/* Returns segment id of segment below segment "seg" on sweep line with coordinate x.
 * Or -1 if it is bottom segment. 
 */
int below(int seg, int x){
	T_NODE* node = root;
	T_NODE* parent_below = NULL;
 
	while (node != NULL && node->seg != seg){
		if( segment_above( seg, node->seg, x) ) {
			parent_below = node;
			node = node->up;		
		}
		else {
			node = node->down;
		}
	}
	/* we found the node with seg */
	if (node->down == NULL)
		return (parent_below ? parent_below->seg : -1 ) ;
	else {
		node = node->down;
		while (node->up != NULL)
			node = node->up;
		return node->seg;
	}
}
 
/*************************************************************************************
 * Events on the sweep line
 *
 */
 
typedef struct {
	int64_t x;
	int64_t y;
	int seg;
	char is_left;
} T_EVENT;
 
/* queue of events on the sweep line */
T_EVENT events[2*MAX_POINTS];
 
/* Each endpoint of a segment coresponds to an event on the sweep line. 
 * Add all endpoints to event list. */
void create_events(){
	int i;
	for(i=0 ; i<n; i++) {
		/* segment p[i]p[i+1] and endpoint p[i] */
		events[2*i].x = point[i].x;
		events[2*i].y = point[i].y;
		events[2*i].seg = i;
		if (point[i].x == point[ (i+1) % n].x )
			/* We slightly rotate all coordinates clockwise by epsilon. */
			events[2*i].is_left = (point[i].y < point[ (i+1) % n].y );  
		else
			events[2*i].is_left = (point[i].x < point[ (i+1) % n].x );
		/* segment p[i]p[i-1] and endpoint p[i] */
		events[2*i+1].x = point[i].x;
		events[2*i+1].y = point[i].y;
		events[2*i+1].seg = (i-1+n) % n;
		if (point[i].x == point[ (i-1+n) % n].x )
			/* We slightly rotate all coordinates clockwise by epsilon. */
			events[2*i+1].is_left = (point[i].y < point[ (i-1+n) % n].y );  
		else
			events[2*i+1].is_left = (point[i].x < point[ (i-1+n) % n].x );
	}
}
 
 
/* sort lexicographicaly - first: by x coordinate, second: left endpoints first */
int cmp_points(const void* p, const void* q){
	int value;
	value =  ((T_EVENT*) p)->x - ((T_EVENT*) q)->x ;
	if (value != 0)
		return value;
	else
		return (((T_EVENT*) p)->is_left ? -1 : 1 ); 
}

vector<Pt> P;
int is_simple_polygon(vector<int> A) {
	int i,e;
	int intersections;
	int seg, seg_above, seg_below;
	int dist_seg_above_below, dist_seg_segabove,dist_seg_segbelow;
	T_EVENT* event;

	n = A.size();
	if (n <= 1)
		return 1;
	for (int i = 0; i < n; i++)
		point[i].x = P[A[i]].x, point[i].y = P[A[i]].y;
//	printf("Polygon(");
//	for (int i = 0; i < n; i++) {
//		printf("(%d,%d)%c", point[i].x, point[i].y, ",)"[i==n-1]);
//	}
//	puts("");
	/* create events (endpoints) and sort them according to x coordinate and if the same x coordinate, then left endpoints first */
	create_events();
	qsort( events, 2*n, sizeof(T_EVENT), cmp_points);	
	init_bin_tree();
	intersections = 0;

	/* process events */
	for(e=0; e<2*n; e++){
		event = events+e;
		seg = event->seg;
		if( event->is_left ){
			/* event -- left end-point -- add it to sweep line */
			root = insert_node(root, seg, event->x);
			/* test intersection with neighbours */
			seg_above = above( seg, event->x);
			seg_below = below( seg, event->x);
			dist_seg_segabove = ABS(seg-seg_above);
			dist_seg_segbelow = ABS(seg-seg_below);
			/* consecutive segments can share a point 
			   (if they were overlaping, there is another endpoint on a segment, 
                               thus we need not to handle such a case) */
			if(  (seg_above != -1 && (dist_seg_segabove > 1 && dist_seg_segabove < n-1) 
				&&  intersect( point[seg], point[(seg+1)%n], point[seg_above], point[(seg_above+1)%n] ))
			  || (seg_below != -1 && (dist_seg_segbelow > 1 && dist_seg_segbelow < n-1) 
				&&  intersect( point[seg], point[(seg+1)%n], point[seg_below], point[(seg_below+1)%n] ))  ) 
			{
				intersections++;
				break;
			}
		}
		else {
			/* event -- right end-point -- remove it from sweep line */
			/* test intersection of segment above with segment below */
			seg_above = above( seg, event->x);
			seg_below = below( seg, event->x);
			dist_seg_above_below = ABS(seg_below-seg_above);

			/* consecutive segments can share a point 
			   (if they were overlaping, there is another endpoint on a segment, 
			   thus we need not to handle this case) */
			if(  (seg_above != -1 &&  seg_below != -1 
				&& (dist_seg_above_below > 1 && dist_seg_above_below < n-1) 
				&& intersect( point[seg_below], point[(seg_below+1)%n], point[seg_above], point[(seg_above+1)%n] )) )
			{
				intersections++;
				break;
			}
			root = delete_node(root, seg, event->x);
		}
	}
	/*if (intersections)	printf("No, polygon with %d vertices is self-intersecting.\n",n);
		else			printf("Yes, polygon with %d vertices is simple.\n",n);*/
	return intersections == 0;
}

struct CMD {
	int cmd;
	double x, y;
	CMD(int cmd, double x = 0, double y = 0):cmd(cmd), x(x), y(y) {}
};
int main() {
//	srand(time(NULL));
	int testcase = 1;
//	printf("%d\n", testcase);
    while (testcase--) {
    	int w, h, n, m, q;
    	int x, y;
    	n = 100000, m = 100000;
    	int E = 1000000000;
    	const double sqr3 = sqrt(3)/2;
    	const double sqr2 = 1.0f/2;
    	vector<CMD> C;
		vector<int> A;
		set<Pt> S;
    	P.clear();
    	P.push_back(Pt(0, 0)); S.insert(Pt(0, 0));
    	P.push_back(Pt(E, 0)); S.insert(Pt(E, 0));
    	P.push_back(Pt(E*sqr2, E*sqr3)); S.insert(Pt(E*sqr2, E*sqr3));
    	A.clear();
    	A.push_back(0); C.push_back(CMD(1, 0, 0));
    	A.push_back(1); C.push_back(CMD(1, 1, 1));
    	A.push_back(2); C.push_back(CMD(1, 2, 2));

		vector<CMD> D;
		for (; C.size() < 50000; ) {
			int cmd = rand()%3+1;
			if (cmd == 2)
				cmd = 1;
			cmd = 1;
			if (cmd == 1 && P.size()+4 < 100000) {
				int TRY_LIMIT = 10;
//				vector<int> cand;
//				for (int i = 0; i < A.size(); i++) {
//					int a = A[i], b = A[(i+1)%A.size()];
//					if (P[a].dist(P[b]) >= 20)
//						cand.push_back(i);
//				}
					
				do {
//					int pos_a = cand[rand()%cand.size()];
					int pos_a = rand()%A.size();
					int pos_b = (pos_a+1)%A.size();
					int a = A[pos_a], b = A[pos_b];
					if (P[a].dist(P[b]) >= 20) {
						double len = P[a].dist(P[b]);
						int p = P.size(), q = P.size()+1, r = P.size()+2;
						Pt ab = P[b]-P[a];
						double dx = ab.x, dy = ab.y;
						double ndx = dy/3, ndy = -dx/3;
						Pt pp(P[a].x + dx/3, P[a].y + dy/3);
						Pt pq(P[a].x + dx/2 + ndx*sqr3, P[a].y + dy/2 + ndy*sqr3);
						Pt pr(P[a].x + dx*2/3, P[a].y + dy*2/3);
						assert(S.count(pp) == 0); S.insert(pp);
						assert(S.count(pq) == 0); S.insert(pq);
						assert(S.count(pr) == 0); S.insert(pr);
						P.push_back(pp);
						P.push_back(pq);
						P.push_back(pr);
						A.insert(A.begin()+pos_b, r); C.push_back(CMD(1, r, pos_b)); // assert(is_simple_polygon(A) == 1);
						A.insert(A.begin()+pos_b, q); C.push_back(CMD(1, q, pos_b)); // assert(is_simple_polygon(A) == 1);
						A.insert(A.begin()+pos_b, p); C.push_back(CMD(1, p, pos_b)); // assert(is_simple_polygon(A) == 1);
						D.push_back(CMD(2, pos_b));
						D.push_back(CMD(2, pos_b));
						D.push_back(CMD(2, pos_b));
						break;
					}
					TRY_LIMIT--;
				} while (TRY_LIMIT > 0);
				if (TRY_LIMIT <= 0)
					cmd = 3;
			}

			if (cmd == 3) {
				int64_t lx = 0, ly = -E/2;
				int64_t rx = E, ry = E;
				double fx, fy;
				fx = rand()*rand()%(rx-ly+10) + lx - 10;
				fy = rand()*rand()%(rx-ly+10) + ly - 10;
				fx += (float) (rand()%100)/100;
				fy += (float) (rand()%100)/100;
				C.push_back(CMD(3, fx, fy));
//				printf("%d %.2lf %.2lf\n", cmd, fx, fy);
			}
			fprintf(stderr, "P %d CMD %d\n", P.size(), C.size());
		}
		
		assert(is_simple_polygon(A) == 1);
		
		if (D.size() > 0) {
			for (int i = D.size()-1; i >= 0 && C.size() < 100000; i--) {
				if (rand()%100 > 50) {
					C.push_back(D[i]);
				} else {
					int64_t lx = 0, ly = -E/2;
					int64_t rx = E, ry = E;
					double fx, fy;
					fx = rand()*rand()%(rx-ly+10) + lx - 10;
					fy = rand()*rand()%(rx-ly+10) + ly - 10;
					fx += (float) (rand()%100)/100;
					fy += (float) (rand()%100)/100;
					C.push_back(CMD(3, fx, fy));
	//				printf("%d %.2lf %.2lf\n", cmd, fx, fy);
				}
			}
		}
    	
    	printf("%d %d\n\n", P.size(), C.size());
    	for (int i = 0; i < P.size(); i++) {
    		printf("%d %d\n", P[i].x, P[i].y);
		}
		puts("");
		for (int i = 0; i < C.size(); i++) {
			if (C[i].cmd == 1) {
				printf("%d %d %d\n", C[i].cmd, (int) C[i].x, (int) C[i].y);
			} else if (C[i].cmd == 2) {
				printf("%d %d\n", C[i].cmd, (int) C[i].x);
			} else {
				printf("%d %.2lf %.2lf\n", C[i].cmd, C[i].x, C[i].y);
			}
		}
//    	set<Pt> S;
//    	P.clear();
//    	printf("%d %d\n\n", n, m);
//    	for (int i = 0; i < n; i++) {
//    		do {
//    			x = rand()*rand()%10000000;
//    			y = rand()*rand()%10000000;
//    			if (!S.count(Pt(x, y)))
//    				break;
//			} while (true);
//			S.insert(Pt(x, y));
//			printf("%d %d\n", x, y);
//			P.push_back(Pt(x, y));
//		}
//
//		puts("");
//		vector<int> A;
//		set<int> SA;
//		int mxsize = 0;
//		int FAIL_INSERT = 0;
//		for (int i = 0; i < m; i++) {
//			int cmd = rand()%3+1;
//			int u, k;
//			if (cmd == 2 && rand()%100 > 10)
//				cmd = 1;
//			if (A.size() == 0 && cmd == 2)
//				cmd = 1;
//			if (A.size() == 0)
//				cmd = 1;
//			if (A.size() == n)
//				cmd = rand()%2+2;
//			if (cmd == 2 && rand()%100 > 50)
//				cmd = 3;
//			if (cmd == 1) {
////				puts("CMD 1");
//				int TRY_LIMIT = 10;
//				vector<int> cand;
//				for (int i = 0; i < n; i++) {
//					if (SA.count(i) == 0)
//						cand.push_back(i);
//				}
//				do {
//					if (cand.size() == 0) {
//						TRY_LIMIT = -1;
//						break;
//					}
//					int pos = rand()%cand.size();
//					u = cand[pos]%n;
////					puts("S");
//					k = rand()%(A.size()+1);
//					A.insert(A.begin()+k, u);
////					puts("E");
//					if (is_simple_polygon(A))
//						break;
//					A.erase(A.begin()+k);
//					TRY_LIMIT--;
//				} while (TRY_LIMIT > 0);
//				if (TRY_LIMIT <= 0)
//					cmd = 3, FAIL_INSERT++;
//				if (cmd == 1) {
//					printf("%d %d %d\n", cmd, u, k);
//					SA.insert(u);
//				}
//			}
//			if (cmd == 2) {
////				puts("CMD 2");
//				assert(A.size() > 0);
//				int TRY_LIMIT = 10;
////				puts("SS");
//				do {
//					k = rand()%A.size();
//					u = A[k];
//					A.erase(A.begin()+k);
//					if (is_simple_polygon(A))
//						break;
//					A.insert(A.begin()+k, u);
//					TRY_LIMIT--;
//				} while (TRY_LIMIT > 0);
//				if (TRY_LIMIT <= 0)
//					cmd = 3;
//				if (cmd == 2) {
//					printf("%d %d\n", cmd, k);
//					SA.erase(u);
//				}
//			}
//			if (cmd == 3) {
////				puts("CMD 3");
//				int lx = INT_MAX, ly = INT_MAX;
//				int rx = INT_MIN, ry = INT_MIN;
//				double fx, fy;
//				for (int i = 0; i < A.size(); i++) {
//					Pt p = P[A[i]];
//					lx = min(lx, p.x), ly = min(ly, p.y);
//					rx = max(rx, p.x), ry = max(ry, p.y);
//				}
//				if (lx > rx)
//					lx = -10000, rx = 10000, ly = -10000, ry = 10000;
//				fx = rand()*rand()%(rx-ly+10) + lx - 10;
//				fy = rand()*rand()%(rx-ly+10) + ly - 10;
//				fx += (float) (rand()%100)/100;
//				fy += (float) (rand()%100)/100;
//				printf("%d %.2lf %.2lf\n", cmd, fx, fy);
//			}
//			fflush(stdout);
//			fprintf(stderr, "size %d\n", A.size());
//			fflush(stderr);
//			mxsize = max(mxsize, (int) A.size());
//		}
//		fprintf(stderr, "MAX_SIZE %d, FAIL_INSER %d\n", mxsize, FAIL_INSERT);
    }
	return 0;
}

