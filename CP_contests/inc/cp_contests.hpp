#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

/* constants */
const int INF = 1e9;
const long long INFLL = 1e18;
const int MOD = 1e9 + 7;

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
typedef vector<vll> vvll;
typedef deque<ll> dqll;
typedef deque<pll> dqpll;
typedef priority_queue<int> pqi;
typedef priority_queue<pii> pqpii;
typedef stack<int> stki;
typedef queue<int> qi;

/* macros for loops */
#define loop(i,s,N) for(int i=(s);i<(N);++i)
#define loopr(i,N) for(int i=(N-1);i>=0;--i) /*loop reverse*/
#define itrfe(c, itr) for(auto itr:c) /*forward iteration on container elements*/
#define itrf(c, itr) for(auto itr=c.begin(); itr!=c.end(); itr++) /*forward iteration on container*/
#define itrr(c, itr) for(auto itr=c.rbegin(); itr!=c.rend(); itr++) /*forward iteration on container*/

/* macros for names*/
#define allc(c) (c).begin(),(c).end() /*all element in container*/
#define fi first
#define se second
#define be begin()
#define en end()
//#define ll long long

/* macros for push, sort, insert, erase*/
#define pb(v, val) v.push_back(val) /* push back vector or sting*/
#define pbp(v, val1, val2) v.push_back({val1,val2}) /*push back vector pair*/
#define sorta(c) sort(allc(c)) /* sort ascending/forward vector or sting*/
#define sortr(c) sort(allc(c), greater<int>()) /*sort reverse/descend*/
#define sorta_rng(v, idx1, idx2) sort((v).begin()+idx1,(v).begin()+idx2) /* sort a range*/
#define insertv(v, val, pos) v.insert(v.begin()+pos, val) /*insert value in vector, string*/
#define inserts(s, val) s.insert(val) /*insert value in set*/
#define erasev(v, pos) v.erase(v.begin()+pos) /*erase a pos in vector*/
#define erasev_rng(v, pos1, pos2) v.erase(v.begin()+pos1, v.begin()+pos2) /*erase a pos in vector*/
#define erases(s, val) s.erase(val) /*erase a val in set*/
//#define removev(v, val) remove(allc(v), val) /*remove matched val in vector*/

/* macros for memset, fill, resize */
#define mset(buf, val) memset(buf,val,sizeof(buf)) /*Note: use for 0 or -1*/
void mseti_fn(int *buf, int val, int lpcnt){loop(i,0,lpcnt){buf[i]=val;}}
#define mseti(buf, val) mseti_fn((int*)buf, val, sizeof(buf)/sizeof(int))
void msetll_fn(ll *buf, ll val, ll lpcnt){loop(i,0,lpcnt){buf[i]=val;}}
#define msetll(buf, val) msetll_fn((ll*)buf, val, sizeof(buf)/sizeof(ll))
#define fillv(v, val) fill(allc(v), val) /*fill vector with a value*/
#define resizev(v, sz) v.resize(sz) /*resize vector*/

/* macros for max, min, find*/
#define maxe(v) *max_element(allc(v)) /* max element in vector*/
#define mine(v) *min_element(allc(v)) /* min element in vector*/
#define maxp(v) max_element(allc(v)) /* max pointer*/
#define minp(v) min_element(allc(v)) /* min pointer*/
#define maxe_rng(v,id1,id2) *max_element((v).be+id1,(v).be+id2) /* max element in vector*/
#define mine_rng(v,id1,id2) *min_element((v).be+id1,(v).be+id2) /* max element in vector*/
#define maxs(s) *max_element((s).begin()) /* max element in set*/
#define mins(s) *min_element((s).rbegin()) /* min element in set*/
/* macros for sets */
#define finds(s, val) s.find(val) /*finds val in set, returns iterator; use member fn instead of global fn find*/
#define presents(s, val) (s.find(val)!=s.end())
#define nexts(s, idx) next(s.begin()+idx) /* next element in set*/

/* macros for binary search*/
#define bs(v, val) binary_search(allc(v), val)
#define bs_rng(v, val, idx1, idx2) binary_search(v.begin()+idx1, v.begin()+idx2, val) /*binary search in a range*/
#define lb(v, val) lower_bound(allc(v), val)
#define ub(v, val) upper_bound(allc(v), val)
//#define mp(val1, val2) make_pair(val1, val2) /*simply use {val1, val2}*/
#define bitcnt __builtin_popcount /*number of bits in a value*/

/* macros for sum, gc, rotate, reverse*/
#define sumv(v) accumulate(allc(v), 0LL) /*sum all values in vector*/
#define sumv_rng(v,idx1,idx2) accumulate((v).be+idx1, (v).be+idx2, 0LL) /*sum range of values in vector*/
#define gcd(a,b) __gcd(a,b)
#define lcm(a,b)  (a/__gcd(a,b))*b
#define rotatev(v, it) rotate((v).begin(), it, (v).end()) /*rotate values, element at iterator becomes first */
#define reversev(v) reverse(allc(v)) /*reverse the order of elements*/
#define countv(v, val) count(allc(v), val) /*counts occuranaces of val*/

/* macros for opertions on sorted containers*/
    /* Note: input containers must be soreted.
             inserter is used for output to insert (otherwise, output should be created with enough size)*/
#define mergec(c1,c2,c3) merge(allc(c1),allc(c2),inserter(c3,c3.be)) /*merges all values (inlcuding duplicates)*/
#define unionc(c1,c2,c3) set_union(allc(c1),allc(c2),inserter(c3,c3.be)) /*merges all unique values */
#define intersectc(c1,c2,c3) set_intersection(allc(c1),allc(c2),inserter(c3,c3.be)) /*intersection of 2 sets */
#define difc(c1,c2,c3) set_difference(allc(c1),allc(c2),inserter(c3,c3.be)) /*unique elements in set1 not present in set2 */

//compare 2 strings lexographic, true if first is smaller
#define lexcomp(s1, s2) lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end());
#define nextperm(s) next_permutation(s.begin(), s.end())
/* heap algorithms*/
#define makeheap(v) make_heap(allc(v))
#define pushheap(v) push_heap(allc(v))
#define popheap(v) pop_heap(allc(v))
#define sortheap(v) sort_heap(allc(v))

/* simply disable DEBUG it to avoid effort removing debug code*/
#define DEBUG 1
#if DEBUG
#define coutm(msg) cout << "\n" << msg << "\n";
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
#define cout6(x,y,z,a,b,c)
#define coutvec(v)
#endif

//Note: Avoid passing containers as arguments (ptrs ok), mainly in recursion

//IMP: Return long long: for large values (CHECK return type)
