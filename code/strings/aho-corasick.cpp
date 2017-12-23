const int N = 500*5005;
map<char, int> nxt[N], go[N];
int par[N], occ[N], sz = 1, link[N];
char parc[N];
void add(string& s, int i) {
    int cur = 1;
    for(char c : s) {
        if(!nxt[cur][c]) {
            sz++;
            parc[sz]=c,par[sz]=cur,nxt[cur][c]=sz,cur=sz;
        }
        else cur=nxt[cur][c];
    }
    occ[cur]++;
}
int GO(int p, char c);
int getlink(int p) {
    if(!link[p]) {
        if(p==1 || par[p]==1) link[p]=1;
        else {
            link[p]=GO(getlink(par[p]),parc[p]);
            occ[p] += occ[link[p]];
        }
    }
    return link[p];
}
int GO(int p, char c) {
    auto it = nxt[p].find(c);
    if(it == nxt[p].end()) {
        auto it = go[p].find(c);
        if (it==go[p].end())
            return (go[p][c]= p==1 ? 1: GO(getlink(p),c));
        else return it->ss;
    } else return it->ss;
}