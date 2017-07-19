# Read from the file words.txt and output the word frequency list to stdout.
awk '
{
	for (i = 1; i <= NF; i++)
		a[$i]++;
}
END {
	for (i in a)
		print i " " a[i];
}' words.txt | sort -nr -k 2
