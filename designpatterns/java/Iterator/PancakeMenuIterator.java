import java.util.Iterator;
public class PancakeMenuIterator implements Iterator {
    MenuItem[] items;
    int position = 0;

    public PancakeMenuIterator(MenuItem[] items) {
        this.items = items;
    }

    public boolean hasNext() {
        if (position < items.length && items[position] != null) {
            return true;
        }
        return false;
    }

    public Object next() {
        Object nextItem = items[position];
        position++;
        return nextItem;
    }

    public void remove() {
        if (position <= 0) {
            throw new IllegalStateException("Cannot remove item, need at least one to remove");
        }
        if (items[position-1] != null) {
            for (int i = position-1; i < items.length-1; i++) {
                items[i] = items[i+1];
            }
            items[items.length-1] = null;
            position--;
        }
    }

}
