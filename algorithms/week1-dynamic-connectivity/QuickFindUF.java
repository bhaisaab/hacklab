// Eager solution
public class QuickFindUF implements IQuickUnion {

    private int[] id;

    // O(N)
    public QuickFindUF(int N) {
        id = new int[N];
        for (int i = 0; i < N; i++) {
            id[i] = i;
        }
    }

    // O(1)
    public boolean connected(int p, int q) {
        return id[p] == id[q];
    }

    // O(N) -- all p values should now be q values
    public void union(int p, int q) {
        int pid = id[p];
        int qid = id[q];
        for (int i = 0; i < id.length; i++) {
            if (id[i] == pid) id[i] = qid;

        }
    }
}
