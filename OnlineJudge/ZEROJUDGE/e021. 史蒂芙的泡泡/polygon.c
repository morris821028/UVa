/*
 * CTU Open Contest 2011
 *
 * Sample solution: Simple Polygon
 * Author: Jakub Cerny
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#define NDEBUG 


#define MAX_POINTS 40000

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define ABS(x) ((x)>0 ? (x) : (-(x)))

typedef struct {
	int x;
	int y;
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
float y_of_segment(int seg, float x){
	int x1 = point[seg].x;
	int y1 = point[seg].y;
	int x2 = point[(seg+1) % n].x;
	int y2 = point[(seg+1) % n].y;
 
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
char segment_above(int seg1, int seg2, float x){
	float y1, y2;
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
	int x;
	int y;
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
 
int main(){
	int i,e;
	int intersections;
	int seg, seg_above, seg_below;
	int dist_seg_above_below, dist_seg_segabove,dist_seg_segbelow;
	T_EVENT* event;
 
	while(1) {
		/* nacti vstup */
		scanf("%d", &n);
		if( n<= 0 ) return 0;
		for(i=0; i<n; i++) {
			scanf("%d %d", &point[i].x, &point[i].y );
		}
 
		/* create events (endpoints) and sort them according to x coordinate and if the same x coordinate, then left endpoints first */
		create_events();
		puts("?");
		qsort( events, 2*n, sizeof(T_EVENT), cmp_points);	
		init_bin_tree();
		puts("??");
		intersections = 0;
		/* process events */
		for(e=0; e<2*n; e++){
			puts("???");
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
		if (intersections)	printf("NO\n");
		else			printf("YES\n");
	}
}

