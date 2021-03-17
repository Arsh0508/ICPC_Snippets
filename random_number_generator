mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int dice(int d, int p)
{
	uniform_int_distribution<int> uid(d, p);
	return uid(rng);
}
