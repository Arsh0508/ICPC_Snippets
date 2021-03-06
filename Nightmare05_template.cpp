//Nightmare05

#pragma GCC optimize("O3")
#pragma GCC target("sse4")
// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>

using namespace std;

#define sp << " " <<
#define mod 1000000007
#define mp make_pair
#define pb push_back
#define int long long
#define double long double
#define INF (1e18 + 13)
#define mod2 998244353
//#define PI 3.1415926535898

int power(int p, int j)
{
	int res = 1;
	p = p % mod;
	while (j > 0)
	{
		if (j & 1)
			res = (res * p) % mod;
		j = j >> 1;
		p = (p * p) % mod;
	}
	return res;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int dice(int d, int p)
{
	uniform_int_distribution<int> uid(d, p);
	return uid(rng);
}
/*
int read()
{
	   int cc = getc(stdin);
	   for (;cc < '0' || cc > '9';)  cc = getc(stdin);
	   int dp = 0;
	   for (;cc >= '0' && cc <= '9';)
	   {
		  dp = dp * 10 + cc - '0';
		  cc = getc(stdin);
	   }
	  return dp;
}

inline void print(int n)
{
  if (n == 0)
  {
	putchar('0');
	putchar('\n');
  }
  else if (n == -1)
  {
	putchar('-');
	putchar('1');
	putchar('\n');
  }
  else
  {
	char buf[20];
	buf[19] = '\n';
	int i = 18;
	while (n)
	{
	  buf[i--] = n % 10 + '0';
	  n /= 10;
	}
	while (buf[i] != '\n')
	  putchar(buf[++i]);
  }
}

int n;

vector<vector<int>> mat_mul(vector<vector<int>> a,vector<vector<int>> b)
{
	int n=2;
	vector<vector<int>> dp2(n,vector<int>(n,0));
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			for(int k=0;k<n;k++)
			{
				dp2[i][j]+=((a[i][k]*b[k][j])%mod);
				dp2[i][j]%=mod;
			}
		}
	}
	return dp2;
}

vector<vector<int>> pow_mat(vector<vector<int>> mat_a,int p)
{
	if(p==1)
		return mat_a;
	vector<vector<int>> temp=pow_mat(mat_a,p/2);
	vector<vector<int>> res=mat_mul(temp,temp);
	if(p&1)
		res=mat_mul(res,mat_a);
	return res;
}
*/

int32_t main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	//freopen("elimination_validation_input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	return 0;
}
