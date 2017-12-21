typedef vector<vi> vvi;
const int N = 2000 * 1005;
map<char, int> go[N];
int par[N], occ[N], sz = 1, fail[N], ans[1005] = {};
char pc[N];
void add(string& s, int i ) {
    int cur = 0;
    for(char c : s) {
        auto it = go[cur].find(c);
        if(it == go[cur].end()) {
            par[sz] = cur;
            pc[sz] = c;
            cur = go[cur][c] = sz++;
        } else cur = it->ss;
    }
    occ[cur]++;
}
int nxt(int cur, char c) {
    auto it = go[cur].find(c);
    if(it == go[cur].end()) {
        if(fail[cur] == -1) {
            if(!cur || !par[cur]) return fail[cur] = 0;
            fail[cur] = nxt(par[cur], c);
            occ[cur] += occ[fail[cur]]];
        } else return fail[cur];
    } else return it->ss;
}