public class Sim {
    public static void main(String[] args) {
        Expression s1 = new ContainsExpression("dog");
        Expression s2 = new ContainsExpression("cat");

        Expression sa = new OrExpression(s1, s2);
        System.out.println(sa.interpret("People love dogs"));

        Expression sb = new AndExpression(s1, s2);
        System.out.println(sb.interpret("People love dogs"));
    }
}
