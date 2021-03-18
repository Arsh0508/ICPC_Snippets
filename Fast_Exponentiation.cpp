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
