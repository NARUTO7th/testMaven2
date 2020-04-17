import java.util.Arrays;

class FindTree {

    boolean findTree(int value, RootNode r, Node[] na, int count){
        count++;
//----------------------------------------
        if(r.getRootOrLeaf ()!=null) {
            if(na == null) {
                na = r.getRootOrLeaf ().toArray (new Node[0]);
            }
        }else return false;
//----------------------------------------
        if(count >= na.length){
            return false;
        }
//----------------------------------------
        if(na[count].getClass ().getName ().equals ("LeafNode")){

            Integer[] values = na[count].getNumbers ().toArray (new Integer[0]);
            boolean result = (Arrays.binarySearch (values, value) >= 0);
            if(!result){
                return findTree (value,r,na,count);
            }return result;
        }else if(na[count].getClass ().getName ().equals ("RootNode")){
            if((value >= na[count].getMinValue ())&&(value <= na[count].getMaxValue ())){
//-----------------------------------------
                return findTree (value, (RootNode) na[count],null,-1);
            }else return findTree (value,r,na,count);
        }
        return false;
    }
}
