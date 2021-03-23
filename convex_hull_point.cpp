//use double = long double

struct point
{
    double x=0,y=0;
    point(){}
    point(pair<double,double> a)
    {
        x=a.first;
        y=a.second;
    }
    point operator-(point b)
    {
        point c;
        c.x=x-b.x;
        c.y=y-b.y;
        return c;
    }
    bool operator==(point b)
    {
        return((x==b.x)&&(y==b.y));
    }
    bool operator<(point b)
    {
        if(x==b.x)
            return y<b.y;
        return x<b.x;
    }
};

double cross(point a, point b) { return a.x * b.y - a.y * b.x; }
double cross(point a, point b, point o) { return cross(a - o, b - o); }
double abs(point a) { return hypotl(a.x, a.y); }

vector<point> convex_hull(vector<point> p)
{
    sort(p.begin(),p.end());
    if(p[0]==p.back())
        return {p[0]};
    int n=p.size(),t=0;
    vector<point> h(n+1);
    for(int j=2,s=0;j--;s=--t,reverse(p.begin(),p.end()))
    {
        for (point i:p)
        {
            while(t>s+1&&cross(i,h[t-1],h[t-2])>=0)
                t--;
            h[t++]=i;
        }
    }
    return h.resize(t),h;
}
