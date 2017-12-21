//1-based with lazy-updates, range sum query
struct node {
    int val, sum, lazy, prior, size;
    node *l, *r;
};
const int N = 2e5;
node pool[N]; int poolptr=0;
typedef node* pnode;
int sz(pnode t) { return t?t->size:0; }
void upd_sz(pnode t) { if(t) t->size = sz(t->l) + 1 + sz(t->r); }
void lazy(pnode t) {
    if(!t || !t->lazy) return;
    t->val+=t->lazy;
    t->sum+=t->lazy*sz(t);
    if(t->l)t->l->lazy+=t->lazy;
    if(t->r)t->r->lazy+=t->lazy;
    t->lazy = 0;
}
void reset(pnode t) {
    if(t) t->sum=t->val;
}
void combine(pnode& t, pnode l, pnode r) {
    if(!l || !r) return void(t=l?l:r);
    t->sum = l->sum + r->sum;
}
void operation(pnode t) {
    if(!t) return;
    reset(t);
    lazy(t->l); lazy(t->r);
    combine(t,t->l,t); combine(t,t,t->r);
}
void split(pnode t, pnode& l, pnode& r, int pos, int add = 0) {
    if(!t) return void(l=r=NULL);
    lazy(t); int curr_pos = add + sz(t->l);
    if(curr_pos<pos) split(t->r,t->r,r,pos,curr_pos+1),l=t;
    else split(t->l,l,t->r,pos,add),r=t;
    upd_sz(t); operation(t);
}
void merge(pnode& t, pnode l, pnode r) {
    lazy(l); lazy(r);
    if(!l || !r) t = l?l:r;
    else if(l->prior > r->prior) merge(l->r,l->r,r),t=l;
    else merge(r->l, l, r-> l), t=r;
    upd_sz(t); operation(t);
}
pnode init(int val) {
    pnode ret = &(pool[poolptr++]);
    ret->prior = rand(); ret->size = 1;
    ret->val = val; ret->sum = val; ret->lazy = 0;
    return ret;
}
int query(pnode t, int l, int r) {
    pnode L,mid,R;
    split(t, L, mid, l-1); split(mid, t, R, r-l);
    int ans = t->sum;
    merge(mid, L, t); merge(t, mid, R);
    return ans;
}
void upd(pnode t, int l, int r, int val) {
    pnode L, mid, R;
    split(t, L, mid, l-1); split(mid, t, R, r-l);
    t->lazy += val;
    merge(mid, L, t); merge(t, mid, R);
}
void insert(pnode& t, ll val, int pos) {
    pnode l;
    split(t,l,t,pos-1); merge(l,l,init(val)); merge(t,l,t);
}