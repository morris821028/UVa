#include <stdio.h> 
#include <string.h>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <map>
using namespace std;
struct Point {
	double x, y, z;
	Point(double a=0, double b=0, double c=0):
		x(a), y(b), z(c) {}
	Point operator-(const Point &a) const {
		return Point(x - a.x, y - a.y, z - a.z);
	}
	double len() {
		return sqrt(x * x + y * y + z * z);
	}
};
int main() {
	const double pi = acos(-1);
	const double earth_r = 6378;
	char s[1024], s2[1024], s3[1024];
	double lat, lon; //  latitude, longitude
	map<string, Point> R;
	while (scanf("%s", s) == 1) {
		if (!strcmp(s, "#"))
			break;
		scanf("%lf %lf", &lat, &lon);
		lat = lat * pi / 180.0;
		lon = lon * pi / 180.0;
		double x, y, z;
		x = earth_r * cos(lat) * cos(lon);
		y = earth_r * cos(lat) * sin(lon);
		z = earth_r * sin(lat);
		R[s] = Point(x, y, z);
	}
	while (scanf("%s", s) == 1) {
		if (!strcmp(s, "#"))
			break;
		scanf("%s %s", s2, s3);
		if (R.find(s) == R.end() || R.find(s2) == R.end() || R.find(s3) == R.end()) {
			printf("%s is ? km off %s/%s equidistance.\n", s3, s, s2);
		} else {
			Point A = R[s], B = R[s2], M = R[s3];
			Point AB = A - B, OM = M;
			double dot = AB.x * OM.x + AB.y * OM.y + AB.z * OM.z;
			double theta = acos(fabs(dot) / AB.len() / OM.len());
			double ret = (pi /2 - theta) * earth_r;
#define eps 1e-6
			if (fabs(AB.x) < eps && fabs(AB.y) < eps && fabs(AB.z) < eps)
				ret = 0;
			printf("%s is %.0lf km off %s/%s equidistance.\n", s3, ret, s, s2);
		}
	}
	return 0;
}
