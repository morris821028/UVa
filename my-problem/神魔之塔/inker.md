# Problem #

Nick will have different passwords for different websites. It's difficult for remember many passwords, so usually produces a specific word combinations. Let it be remember easily.

Unfortunately, Nick haven't visited the PTC website for a long time, and forgotten before setting the password. He remember part of the password fragments, but some fragments has lost. According to the habit which setting the password, he will pick some tokens from a specific collection to combine a password.

How many kinds of passwords ?

# Input #

Input consists of several datasets. 

The first line of each dataset consists of `N S`, `N` ($ N \le 20 $) is the size of token collection and `S` will be 1 to 100 characters for string of password. `S` is composed solely of the lowercase letter `a`-`z`, and `*`, and `*` will be considered as position of forgotten character.

The second line of each dataset consists N tokens separated by space. Each token will be 1 to 20 characters, and are composed solely of the lowercase letter `a`-`z`. 

# Output #

Each dataset, output a single line number which kinds of passwords. If the number is greater than 1000000007 print the number mod 1000000007.

# Sample Input #

```
1 mo*
moe
3 *s*pf**
sssp spfa dp
3 **c**
hack ac scc
2 *nick****
knick wwww 
```

# Sample Output #

```
1
19551
20252
457026
```