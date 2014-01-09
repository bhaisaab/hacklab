public class QuickUnionTest {

    public static void main(String[] args) {
        System.out.println("QuickUnion Program");

        //IQuickUnion qu = new QuickUnionUF(10);
        IQuickUnion qu = new QuickFindUF(10);
        qu.union(1, 9);
    }

}
