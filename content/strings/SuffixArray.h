/**
 * Author: 罗穗骞, chilli
 * Date: 2019-04-11
 * License: Unknown
 * Source: Suffix array - a powerful tool for dealing with strings
 * (Chinese IOI National team training paper, 2009)
 * Description: Builds suffix array for a string.
 * \texttt{sa[i]} is the starting index of the suffix which
 * is $i$'th in the sorted suffix array.
 * The returned vector is of size $n+1$, and \texttt{sa[0] = n}.
 * The \texttt{lcp} array contains longest common prefixes for
 * neighbouring strings in the suffix array:
 * \texttt{lcp[i] = lcp(sa[i], sa[i-1])}, \texttt{lcp[0] = 0}.
 * The input string must not contain any zero bytes.
 * Time: O(n \log n)
 * Status: stress-tested
 */
#pragma once

struct SuffixArray {
	vi sa, lcp;
	string str;
	SuffixArray(string& s, int lim=256) { // or basic_string<int>
		str = s;
		int n = sz(s) + 1, k = 0, a, b;
		vi x(all(s)+1), y(n), ws(max(n, lim)), rank(n);
		sa = lcp = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j, iota(all(y), n - j);
			rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(all(ws), 0);
			rep(i,0,n) ws[x[i]]++;
			rep(i,1,lim) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		rep(i,1,n) rank[sa[i]] = i;
		for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
			for (k && k--, j = sa[rank[i] - 1];
					s[i + k] == s[j + k]; k++);
	}

	ii stringMatching(string &p) { // O(m log n)
		int lo = 0, hi = sz(sa)-1, mid = lo;
		while (lo < hi) { // find lower bound
			mid = (lo+hi) / 2;
			int res = string_view(str.data()+sa[mid]).compare(string_view(p.data()));
    		(res >= 0) ? hi = mid : lo = mid+1;
  		}
  		//if (strncmp(T+SA[lo], P, m) != 0) return ii(-1, -1);
		if (string_view(str.data()+sa[lo]) != string_view(p.data())) return ii(-1, -1);
  		ii ans; ans.first = lo;
  		lo = 0; hi = sz(sa)-1; mid = lo;
		while (lo < hi) { // find upper bound
			mid = (lo+hi) / 2;
			//int res = strncmp(T+SA[mid], P, m);
			int res = string_view(str.data()+sa[mid]).compare(string_view(p.data()));
			(res > 0) ? hi = mid : lo = mid+1;
		}
  		//if (strncmp(T+SA[hi], P, m) != 0) --hi;
		if (string_view(str.data()+sa[hi]) != string_view(p.data())) --hi;
  		ans.second = hi;
  		return ans;
}

	ii LRS() {  // longest repeated substring: O(n)
		int i, idx = 0, maxLCP = -1;
		for (i = 1; i < sz(lcp); ++i)
			if (lcp[i] > maxLCP)
				maxLCP = lcp[i], idx = i;
		return ii(maxLCP, idx);
	}


	// owner describes which string the substring belongs to
	// add code to ctor for index of special split character
	// the check if idx < index
	// int owner(int idx) { return (idx < n-m-1) ? 1 : 2; }

	ii LCS() {
		// returns longest common substring between two strings: O(n)
		// assumes strings terminated by different special characters
		int i, idx = 0, maxLCP = -1;
		for (i = 1; i < sz(lcp); ++i)
			if (owner(sa[i]) != owner(sa[i-1]) && lcp[i] > maxLCP)
				maxLCP = lcp[i], idx = i;
		return ii(maxLCP, idx);
	}
};
