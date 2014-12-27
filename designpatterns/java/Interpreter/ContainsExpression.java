public class ContainsExpression implements Expression {
    public String data;

    public ContainsExpression(String data) {
        this.data = data;
    }

    public boolean interpret(String context) {
        return context.contains(data);
    }
}
