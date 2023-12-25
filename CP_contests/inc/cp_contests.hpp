#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

/* alias */
using ll = long long;
using ld = long double;
using ull = unsigned long long;

/* typedefs */
typedef unordered_set<int> usi;
typedef unordered_set<string> uss;
typedef unordered_set<ll> usll;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, string> umis;
typedef unordered_map<string, int> umsi;
typedef unordered_map<string, string> umss;
typedef unordered_map<ll, ll> umll;
typedef vector<int> vi;
typedef vector<string> vs;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;
typedef multiset<int> msi;
typedef multiset<string> mss;
typedef multimap<int, int> mmii;
typedef multimap<int, string> mmis;
typedef multimap<string, int> mmsi;
typedef pair<int,int> pii;
typedef pair<int,string> pis;
typedef pair<ll,ll> pll;
typedef pair<string, string> pss;
typedef vector<pii> vpii;
typedef vector<pis> vpis;
typedef vector<pll> vpll;
typedef vector<pss> vpss;
typedef vector<pair<int, pii>> vpipii;
typedef vector<vi> vvi; /*vector of vectors*/
typedef vector<vpii> vvpii;
typedef vector<vs> vvs;
typedef deque<ll> dqll;
typedef deque<pll> dqpll;
typedef priority_queue<int> pqi;
typedef priority_queue<pii> pqpii;
typedef stack<int> stki;
typedef queue<int> qi;

/* macros */
//#define ll long long
#define pb(v, val) v.push_back(val) /* push back vector or sting*/
#define pbp(v, val1, val2) v.push_back({val1,val2}) /*push back vector pair*/
#define loop(i,s,N) for(int i=(s);i<(N);++i)
#define loopr(i,N) for(int i=(N-1);i>=0;--i) /*loop reverse*/
#define sort_all(v) sort((v).begin(),(v).end()) /* sort vector or sting*/
#define sortr(v) sort((v).begin(),(v).end(), greater<int>()) /*sort reverse*/
#define sort_few(v, idx1, idx2) sort((v).begin()+idx1,(v).begin()+idx2) /* sort a portion*/
#define findv(v, val) find(v.begin(), v.end(), val)
#define insertv(v, pos, val) v.insert(v.begin()+pos, val) /*insert value in vector, string*/
//#define insert(v, size, val) v.insert(v.begin(), size, val) /*insert value in vector*/
#define mset(buf, val) memset(buf,val,sizeof(buf))
#define fillv(v, val) fill(v.begin(), v.end(), val) /*fill vector with a value*/
#define resizev(v, sz) v.resize(sz) /*resize vector*/
#define maxe(v) *max_element((v).begin(),(v).end())
#define mine(v) *min_element((v).begin(),(v).end())
#define bs(v, val) binary_search(v.begin(), v.end(), val)
#define lb(v, val) lower_bound(v.begin(), v.end(), val)
#define ub(v, val) upper_bound(v.begin(), v.end(), val)
//#define mp(val1, val2) make_pair(val1, val2) //simply use {val1, val2}
#define allv(v) (v).begin(),(v).end()
#define fi first
#define se second
#define bitcnt __builtin_popcount /*number of bits in a value*/

/* macros: more utility functions */
#define sumv(x) accumulate(x.begin(), x.end(), 0LL) /*sum all values in vector*/
#define gcd(a,b) __gcd(a,b)
#define lcm(a,b)  (a/__gcd(a,b))*b
#define mreverse(v) reverse((v).begin(),(v).end()) /*reverse the order of elements*/
#define mrotate(v, it) rotate((v).begin(), it, (v).end()) /*rotate values, element at it becomes first */
#define removev(v, val) remove((v).begin(),(v).end(), val) /*remove matched val in vector*/
//compare 2 strings lexographic, true if first is smaller
#define lexcomp(s1, s2) lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end());
#define nextperm(s) next_permutation(s.begin(), s.end())
// heap algorithms
#define makeheap(v) make_heap(v.begin(), v.end())
#define pushheap(v) push_heap(v.begin(), v.end())
#define popheap(v) pop_heap(v.begin(), v.end())
#define sortheap(v) sort_heap(v.begin(), v.end())

/* constants */
const int INF = 1e9;
const ll INFLL = 1e18;
const int MOD = 1e9 + 7;

/* simply disable DEBUG it to avoid effort removing debug code*/
#define DEBUG 1
#if DEBUG
#define coutm(msg) cout << "\n" << msg;
#define cout1(x) cout << #x << ":" << (x) << "\n"
#define cout2(x,y) cout << #x << ":" << (x) << ", " << #y << ":" << (y) << "\n"
#define cout3(x,y,z) cout << #x << ":" << (x) << ", " << #y << ":" << (y) << ", " << #z << ":" << (z) << "\n"
#define cout4(x,y,z,a) cout << #x << ":" << (x) << ", " << #y << ":" << (y) << ", " << #z << ":" << (z) << ", " << #a << ":" << (a) << "\n"
#define cout5(x,y,z,a,b) cout << #x << ":" << (x) << ", " << #y << ":" << (y) << ", " << #z << ":" << (z) << ", " << #a << ":" << (a) << ", " << #b << ":" << (b) << "\n"
#define cout6(x,y,z,a,b,c) cout << #x << ":" << (x) << ", " << #y << ":" << (y) << ", " << #z << ":" << (z) << ", " << #a << ":" << (a) << ", " << #b << ":" << (b) << ", " << #c << ":" << (c) << "\n"
#define coutvec(v) loop(cntrr,0,v.size()){cout << v[cntrr] << ", "; if(cntrr==v.size()-1) cout<<"\n";}
#else
#define coutm(msg)
#define cout1(x)
#define cout2(x,y)
#define cout3(x,y,z)
#define cout4(x,y,z,a)
#define cout5(x,y,z,a,b)
#define cout6(x,y,z,a,c)
#define coutvec(v)
#endif

//Note: Avoid passing containers as arguments (ptrs ok), mainly in recursion

//IMP: Return long long: for large values (CHECK return type)