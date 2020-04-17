import java.util.Collection;

public class RootNode extends Node {
    private int minValue;
    private int maxValue;
    private  Collection<Node> RootOrLeaf;

    RootNode(int min, int max, Collection<Node> nodes){
        this.minValue = min;
        this.maxValue = max;
        this.RootOrLeaf = nodes;
    }

    public int getMinValue() {
        return minValue;
    }

    public int getMaxValue() {
        return maxValue;
    }

    Collection<Node> getRootOrLeaf() {
        System.out.println ("Now, coming into a rootNode," +
                " and it's scope is from "+ this.getMinValue ()+" to "+this.getMaxValue ());
        return RootOrLeaf;
    }
}
