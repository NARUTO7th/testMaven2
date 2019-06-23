import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

public class TestTree {
    public static void main(String[] args) {
//----------to build a tree
        RootNode rootNode = SampleTree();
//----------to search tree
        FindTree f = new FindTree ();
        boolean result = f.findTree (1200,rootNode,null,-1);
        System.out.println ("The Searching result is " + result);
    }

    private static RootNode SampleTree(){
        LeafNode n1 = new LeafNode (new ArrayList<> (Arrays.asList (300,320,340,360)));
        RootNode n2 = new RootNode(300,390,new ArrayList<> (Collections.singletonList (n1)));
        LeafNode n3 = new LeafNode (new ArrayList<> (Arrays.asList (200,220,240,260)));
        LeafNode n4 = new LeafNode (new ArrayList<> (Arrays.asList (100,120,140,160)));
        RootNode n5 = new RootNode (200,399,new ArrayList<> (Arrays.asList (n2,n3)));
        RootNode n6 = new RootNode(100,199,new ArrayList<> (Collections.singletonList (n4)));

        return new RootNode (1,1000,new ArrayList<> (Arrays.asList (n5,n6)));
    }

}
