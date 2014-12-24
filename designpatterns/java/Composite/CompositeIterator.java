import java.util.Iterator;
import java.util.Stack;
import java.lang.UnsupportedOperationException;

public class CompositeIterator implements Iterator {
    Stack s = new Stack();

    public CompositeIterator(Iterator it) {
        s.push(it);
    }

    public boolean hasNext() {
        if (s.empty()) {
            return false;
        } else {
            Iterator it = (Iterator) s.peek();
            if (it.hasNext()) {
                return true;
            } else {
                s.pop();
                return hasNext();
            }
        }
    }

    public Object next() {
        if (hasNext()) {
            Iterator it = (Iterator)  s.peek();
            MenuComponent m = (MenuComponent) it.next();
            if (m instanceof Menu) {
                s.push(m.createIterator());
            }
            return m;
        } else {
            return null;
        }
    }

    public void remove() {
        throw new UnsupportedOperationException();
    }
}
