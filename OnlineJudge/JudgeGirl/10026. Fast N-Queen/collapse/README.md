## Collapse ##

OpenMP synatex

```
#pragma omp for schedule(dynamic) collapse(3) reduction(+: ret)
for (int i = 0; i < n; i++) {
	for (int j = 0; j < n; j++) {
		for (int k = 0; k < n; k++) {
			ret += test(i, j, k, n);
		}
	}
}
```

Easy-implementation & efficient for solving N-Queen problem.

### Result ###

Accepted (1177 ms, 384 KB)
