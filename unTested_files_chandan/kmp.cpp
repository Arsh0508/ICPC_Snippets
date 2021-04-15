class Kmp {
	public:
	vector<int> pattern; // It will store the length of matched pattern for the string after addition of pat + "$" + str.
	vector<int> kmp(string str, string ptr) {
		// It returns a vector for which each indices show the maximum length of
		// of prefix of pattern which is ending at that perticular indices in the origional string.
		int n = str.size();
		int m = ptr.size();
		str = ptr + "$" + str;
		pattern.resize(n + m + 1, 0);
		int ind = 1, siz = 0;
		while(ind < n + m + 1) {
			if(str[ind] == str[siz]) {
				siz++;
				pattern[ind] = siz;
				ind++;
			}
			else {
				if(siz > 0) {
					siz = pattern[siz - 1];
				}
				else {
					pattern[ind] = siz;
					ind++;
				}
			}
		}
		vector<int> res;
		for(int i = m + 1; i <= n + m; i++) 
			res.push_back(pattern[i]);
		return res;
	}
};

