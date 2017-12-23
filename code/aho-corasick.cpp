const int N = 2000 * 1005;
map<char, int> go[N];
int par[N], occ[N], sz = 1, fail[N];
char parc[p];
void add(string& s, int i) {
    int cur = 0;
    for(char c : s) {
        if(!go[cur][c])
            parc[sz]=c,par[sz]=cur,cur=go[cur][c] = ++sz;
        else
            cur=go[cur][c];
    }
    occ[cur]++;
}
int getlink(int p) {
    if(!link[p]) {
        if(p==1 || par[p]==1) link[p]=1;
        else {
            link[p]=go(getlink(par[p],parc[p]));
            occ[p] += occ[link[p]];
        }
    }
    return link[p];
}
int nxt(int cur, char c) {
    auto it = go[cur].find(c);
    if(it == go[cur].end()) {
        if(fail[cur] == -1) {
            if(!cur || !par[cur]) return fail[cur] = 0;
            fail[cur] = nxt(par[cur], c);
            occ[cur] += occ[fail[cur]]];
        }
        return fail[cur];
    } else return it->ss;
}