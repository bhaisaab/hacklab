public class AndExpression implements Expression {
    Expression p1;
    Expression p2;
    public AndExpression(Expression p1, Expression p2) {
        this.p1 = p1;
        this.p2 = p2;
    }

    public boolean interpret(String context) {
        return p1.interpret(context) && p2.interpret(context);
    }
}
