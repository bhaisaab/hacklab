public class WeightedQuickUnion  implements IQuickUnion {

    private int[] id;
    private int[] sz;

    public WeightedQuickUnion(int N) {
        id = new int[N];
        sz = new int[N];
        for (int i = 0; i < N; i++) {
            id[i] = i;
            sz[i] = 1;
        }
    }

    private int root(int i) {
        while (i != id[i]) {
            // path compression
            id[i] = id[id[i]];
            i = id[i];
        }
        return i;
    }

    public boolean connected(int p, int q) {
        return root(p) == root(q);
    }

    // root of p is root of j; p belongs to q's connected component group
    public void union(int p, int q) {
        int pid = root(p);
        int qid = root(q);
        if (pid == qid) return;
        if (sz[pid] < sz[qid]) {
            id[pid] = qid; sz[qid] += sz[pid];
        } else {
            id[qid] = pid; sz[pid] += sz[qid];
        }
    }

}
