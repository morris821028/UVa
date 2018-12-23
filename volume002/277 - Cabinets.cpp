#include <bits/stdc++.h> 
using namespace std;

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (getchar() != '\n');
	while (getchar() != '\n');
	while (testcase--) {
		puts("Item Id,Item Desc,Item Price");
		char s[1024];
		map<int, string> style_group;
		while (fgets(s, 1024, stdin))	{
			if (s[0] == '\n')
				break;
			int style_code = 0;
			string style_name = "";
			string desc = "";
			string ext = "";
			int price = 0;
			char *last = s;
			for (int i = 0, col = 0; s[i]; i++) {
				if (s[i] == ',' || s[i] == '\n' || s[i+1] == '\0') {
					s[i] = '\0';
//					printf("%s\n", last);
					if (col == 0) {
						style_code = atoi(last);
					} else if (col == 1) {
						style_name = last;
					} else if (col == 2) {
						desc = last;
					} else if (col == 3) {
						ext = last;
					} else {
						price = atoi(last);
					}
					last = s+i+1, col++;
				}
			}
//			printf("%d\n%s\n%s\n%s\n%d\n", style_code, style_name.c_str(), desc.c_str(), ext.c_str(), price);
			
			if (style_group.find(style_code) == style_group.end())
				style_group[style_code] = style_name;

			char buf[1024];
			sprintf(buf, "%03d%s", style_code, desc.c_str());
			if (strlen(buf) > 13)
				continue;
			string item_id = buf;
			if (style_name.length() == 0) {
				if (style_group.find(style_code) == style_group.end())
					continue;
				else
					style_name = style_group[style_code];
				if (style_name.length() == 0)
					continue;
			}

			string item_desc = "";
			if (ext.length() == 0)
				item_desc = style_name;
			else
				item_desc = style_name + "-" + ext;
			if (item_desc.length() > 30)
				item_desc = item_desc.substr(0, 30);

			printf("%s,%s,%d.%02d\n", item_id.c_str(), item_desc.c_str(), price/100, price%100);
		}
		if (testcase)
			puts("");
	}
	return 0;
}
