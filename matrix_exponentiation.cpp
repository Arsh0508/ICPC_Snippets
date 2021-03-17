vector<vector<int>> mat_mul(vector<vector<int>> a,vector<vector<int>> b)
{
	int n=a.size();
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
