import java.util.Collection;

public class LeafNode extends Node {
    private Collection<Integer> numbers;

    Collection<Integer> getNumbers() {
        System.out.print("Now, coming into a leafNode, and the set of values is : ");
        Integer[] values = numbers.toArray (new Integer[0]);
        for (Integer value : values) {
            System.out.print (value + " ");
        }
        System.out.println (" ");
        return numbers;
    }

    public void setNumbers(Collection<Integer> numbers) {
        this.numbers = numbers;
    }

    LeafNode(Collection<Integer> values){
        this.numbers = values;
    }
}