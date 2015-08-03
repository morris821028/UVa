#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <math.h>
#include <map>
#include <vector>
#include <set>
using namespace std;
void lz77_encode(unsigned char *in, int n, unsigned char *out, int &m)  {
	m = 0;
	if (n <= 16) {
		for (int i = 0; i < n; i++)
			out[m++] = in[i];
		return ;
	}
	memcpy(out, in, 16);
	m += 16;
	while (n > 16) {
		int mx = 0, offset, i, j;
		for (i = 0; i < 16; i++) {
			for (j = 0; i+j < 16 && j+16 < n && in[i+j] == in[j+16]; j++);
			if (j > mx)
				mx = j, offset = i;
		}
		if (mx <= 1) {
			out[m++] = 0;
			out[m++] = in[16];
			in++, n--;
		} else {
			out[m++] = (offset<<4)|(mx-1);
			in += mx, n -= mx;
		}
	}
}
void lz77_decode(unsigned char *in, int n, unsigned char *out, int &m)  {
	m = 0;
	if (n <= 16) {
		for (int i = 0; i < n; i++)
			out[m++] = in[i];
		return ;
	}
	memcpy(out, in, 16);
	in += 16, n -= 16, m += 16;
	int offset, mx;
	while (n > 0) {
		if (*in) {
			offset = (*in)>>4, mx = ((*in)&0xf)+1;
			memcpy(out + m, out + m - 16 + offset, mx);
			m += mx;
			in++, n -= 1;
		} else {
			out[m++] = in[1];
			in += 2, n -= 2;
		}
	}
}
void base64_encode(unsigned char *in, int n, unsigned char *out, int &m)  {
static char encode_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                    'w', 'x', 'y', 'z', '0', '1', '2', '3',
                    '4', '5', '6', '7', '8', '9', '+', '/'};
static int mod_table[] = {0, 2, 1};

	m = 4 * ((n + 2) / 3);
	for (int i = 0, j = 0; i < n; ) {
		unsigned int a, b, c, d;
		a = i < n ? in[i++] : 0;
		b = i < n ? in[i++] : 0;
		c = i < n ? in[i++] : 0;
		d = (a<<16)|(b<<8)|c;
		out[j++] = encode_table[(d>>18)&0x3f];
		out[j++] = encode_table[(d>>12)&0x3f];
		out[j++] = encode_table[(d>>6)&0x3f];
		out[j++] = encode_table[d&0x3f];
	}
	for (int i = 0; i < mod_table[n%3]; i++)
		out[m - 1 - i] = '=';
}
void base64_decode(unsigned char *in, int n, unsigned char *out, int &m)  {
static int decode_table[256];
	for (int i = 'A'; i <= 'Z'; i++)	decode_table[i] = i - 'A';
	for (int i = 'a'; i <= 'z'; i++)	decode_table[i] = i - 'a' + 26;
	for (int i = '0'; i <= '9'; i++)	decode_table[i] = i - '0' + 52;
	decode_table['+'] = 62, decode_table['/'] = 63;
	m = n/4*3;
	if (in[n-1] == '=')	m--;
	if (in[n-2] == '=')	m--;
	for (int i = 0, j = 0; i < n; ) {
		unsigned int a, val = 0;
		for (int k = 3; k >= 0; i++, k--) {
			a = in[i] == '=' ? 0 : decode_table[in[i]];
			val |= a<<(k*6);
		}
		if (j < m)	out[j++] = (val>>16)&0xff;
		if (j < m)	out[j++] = (val>>8)&0xff;
		if (j < m)	out[j++] = (val>>0)&0xff;
	}
}
void huffman_encode(unsigned char *in, int n, unsigned char *out, int &m)  {
	m = 0;
	struct Table {
		int f, bit, bn;
	} tables[512];
	struct Node {
		int f, tid;
		Node *l, *r;
		Node(int a = 0, int b = 0, Node *ls = NULL, Node *rs = NULL):
			f(a), tid(b), l(ls), r(rs) {}
		bool operator<(const Node &x)  const {
			return f < x.f;
		}
	} nodes[512];
	struct Stack {
		Node *node;
		int bit, bn;
		Stack(Node *a = NULL, int b = 0, int c = 0):
			node(a), bit(b), bn(c) {}
	} stacks[1024];
	int size = 0, leaf;
	multiset< pair<int, Node*> > S;
	memset(tables, 0, sizeof(tables));
	for (int i = 0; i < n; i++)
		tables[in[i]].f++;
	for (int i = 0; i < 256; i++) {
		if (tables[i].f) {
			nodes[size] = Node(tables[i].f, i);
			S.insert({nodes[size].f, &nodes[size]});
			size++;
		}
	}
	leaf = size;
	while (S.size() >= 2) {
		pair<int, Node*> u, v;
		u = *S.begin(), S.erase(S.begin());
		v = *S.begin(), S.erase(S.begin());
		int f = u.second->f + v.second->f; 
		nodes[size] = Node(f, -1, u.second, v.second);
		S.insert({nodes[size].f, &nodes[size]});
		size++;
		
	}
	int stkIdx = 0;
	stacks[stkIdx++] = Stack(&nodes[size-1], 0, 0);
	while (stkIdx) {
		Stack u = stacks[--stkIdx], v;
		if (u.bn >= 31) {
			fprintf(stderr, "huffman error: bit length exceeded\n");
			exit(0);
		}
		if (u.node->l == NULL) {
			tables[u.node->tid].bit = u.bit;
			tables[u.node->tid].bn = u.bn;
		} else {
			v = Stack(u.node->l, u.bit | (1<<u.bn), u.bn+1);
			u.node = u.node->r, u.bn++;
			stacks[stkIdx++] = u;
			stacks[stkIdx++] = v;
		}
	}
	int bits_cnt = 0;
	for (int i = 0; i < 256; i++)
		bits_cnt += tables[i].f * tables[i].bn;
	fprintf(stderr, "huffman: %d bit length\n", bits_cnt);
	
	memcpy(out+m, &bits_cnt, 4), m += 4;
	memcpy(out+m, &leaf, 1), m += 1;
	for (int i = 0; i < leaf; i++) {
		Table t = tables[nodes[i].tid];
		memcpy(out+m, &nodes[i].tid, 1), m += 1;
		memcpy(out+m, &t.bn, 1), m += 1;
		memcpy(out+m, &t.bit, (t.bn + 7)/8), m += (t.bn + 7)/8;
	}
	
	int cnt = 0, mask = 0;
	for (int i = 0; i < n; i++) {
		int bit = tables[in[i]].bit;
		int bn = tables[in[i]].bn;
		while (bn) {	// LBS
			int j = min(bn, 8 - cnt);
			mask |= (bit&((1<<j)-1))<<cnt;
			cnt += j, bn -= j, bit >>= j;
			if (cnt == 8) {
				memcpy(out+m, &mask, 1), m += 1;
				cnt = 0, mask = 0;
			}
		}
	}
	if (cnt)
		memcpy(out+m, &mask, 1), m += 1;
	fprintf(stderr, "huffman encode length %d\n", m);
}
void huffman_decode(unsigned char *in, int n, unsigned char *out, int &m)  {
	m = 0;
	map<int, int> R[64];
	int bits_cnt = 0, leaf = 0;
	memcpy(&bits_cnt, in, 4), in += 4, n -= 4;
	memcpy(&leaf, in, 1), in += 1, n -= 1;
	fprintf(stderr, "huffman: %d bit length\n", bits_cnt);
	fprintf(stderr, "huffman: %d leaves\n", leaf);
	for (int i = 0; i < leaf; i++) {
		int tid = 0, bn = 0, bit = 0;
		memcpy(&tid, in, 1), in += 1, n -= 1;
		memcpy(&bn, in, 1), in += 1, n -= 1;
		memcpy(&bit, in, (bn+7)/8), in += (bn+7)/8, n -= (bn+7)/8;
		R[bn][bit] = tid;
	}
	int mask = 0, cnt = 0;
	for (int i = 0; i < bits_cnt; i++) {
		mask |= ((in[(i>>3)]>>(i&7))&1)<<cnt;
		cnt++;
		if (R[cnt].count(mask)) {
			out[m++] = R[cnt][mask];
			cnt = 0, mask = 0;
		}
	}
}
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		unsigned char in[32767], in2[32767], *pin;
        pin = in;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
                int r, g, b;
				scanf("%d %d %d", &r, &g, &b);
				*pin = r, pin++;
                *pin = g, pin++;
                *pin = b, pin++;
			}
		}
		int lz77n, b64n, elz77n, tn, hufn, ehufn;
		unsigned char buf[4][32767] = {}, test[32767] = {};
		// Case 1
//		base64_encode(in, n*m*3, buf[1], b64n);
		// Case 2
//		huffman_encode(in, n*m, buf[0], hufn);
//		base64_encode(buf[0], hufn, buf[1], b64n);
//		base64_decode(buf[1], b64n, buf[2], ehufn);
//		huffman_decode(buf[2], ehufn, test, tn);
		// Case 3
//		lz77_encode(in, n*m, buf[0], lz77n);
//		base64_encode(buf[0], lz77n, buf[1], b64n);
//		base64_decode(buf[1], b64n, buf[2], elz77n);
//		lz77_decode(buf[2], elz77n, test, tn);
		// Case 4
//		huffman_encode(in, n*m, buf[0], hufn);
//		lz77_encode(buf[0], hufn, buf[2], lz77n);
//		base64_encode(buf[2], lz77n, buf[1], b64n);
		// Case 5
//		lz77_encode(in, n*m, buf[0], lz77n);
//		huffman_encode(buf[0], hufn, buf[2], hufn);
//		base64_encode(buf[2], lz77n, buf[1], b64n);
		// Case 6
        for (int i = 0; i < n*m*3; i += 3) {
			in2[i] = in[i] - (i >= 3 ? in[i-3] : 0);
            in2[i+1] = in[i+1] - (i >= 4 ? in[i-4] : 0);
            in2[i+2] = in[i+2] - (i >= 5 ? in[i-5] : 0);
        }
		huffman_encode(in2, n*m*3, buf[0], hufn);
		base64_encode(buf[0], hufn, buf[1], b64n);
		for (int i = 0; i < b64n; i++)
			printf("%c", buf[1][i]);
		puts("");
	}
	return 0;
}
