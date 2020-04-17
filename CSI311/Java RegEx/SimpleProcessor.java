import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

/**
*
*@ClassName: SimpleProcessor
*@Description: This class can analyze regular expression containing "+,*,[]“, and find if the text file
 * contain string match this regular expression.
*@author Tang Hao
*@data 2019/3/11
*@version 1.0
*/

public class SimpleProcessor {

/**
*
* @Description This is driver.
* @param args Something can receive parameter from command.
* @return Nothing
**/

    public static void main(String[] args) throws IOException {
//construct a class of BufferedReader to read file
        File f = new File("E:\\REProcessor\\src\\test");
        BufferedReader br = new BufferedReader (new FileReader (f));

        Scanner sc = new Scanner (System.in);
        System.out.println ("Please enter a formatted regular expression: ");

        String RE = sc.nextLine ();

        String line;
        int numOfLine = 1;

        ArrayList<String> setOfRE = ExprAnalyze (RE);

        while((line = br.readLine()) != null){
            assert setOfRE != null;
            ExprMatch (numOfLine,line,setOfRE);
        }
    }

/**
*
* @Description This method will analyze a regular expression and split it ,and store them into
 * an ArrayList meanwhile.
* @param expression A regular expression
* @return An ArrayList contained the form of "a+", "a*", "[sdds]"
**/

    public static ArrayList<String> ExprAnalyze(String expression){
        //set a new array list
        ArrayList<String> store = new ArrayList<> ();


        //Set a String variable could temporally store the spilt String
        String temp,temp1;


        // LOOP for splitting and storing the expression
        for (int i = 0; i < expression.length (); i++) {

            if(expression.length () != 0) {
                //get the length of this string
                int length = expression.length ();

                //get each of character of this String according to the index named "i"
                char present = expression.charAt (i);

                //determine if it is '*' or '+' or "[]"
                if (present == '*') {

                    //to prevent this case that "ega*" from index over the length of String
                    if ((i - 1) > 0) {

                        //this case will happen when there are more than one letter before the *
                        temp = expression.substring (0, i - 1);
                        temp1 = expression.substring (i - 1, i + 1);

                        //add this String to array list
                        store.add (temp);
                        store.add (temp1);
                        //to avoid this case "*ksn"
                    } else if (i == 0) {
                        return null;
                    } else {
                        //this case will happen only when there are one letter before the +
                        temp = expression.substring (0, 2);
                        //add this String to array list
                        store.add (temp);
                    }
                    //remove the string which were added into the array list
                    expression = expression.substring (i + 1, length);

                    //reset the i to 0
                    i = -1;

                } else if (present == '+') {

                    //to avoid this case "+ksn"
                    if (i == 0) {
                        return null;
                        //to prevent this case that "ega+" from index over the length of String
                    } else if ((i - 1) > 0) {

                        //this case will happen when there are more than one letter before the + or *
                        temp = expression.substring (0, i - 1);
                        temp1 = expression.substring (i - 1, i + 1);

                        //add this String to array list
                        store.add (temp);
                        store.add (temp1);

                    } else {
                        //this case will happen only when there are one letter before the + or *
                        temp = expression.substring (0, 2);
                        //add this String to array list
                        store.add (temp);
                    }
                    //remove the string which were added into the array list
                    expression = expression.substring (i + 1, length);

                    //reset the i to 0
                    i = -1;

                    //to avoid this case "s+db]sd*"
                } else if (present == ']') {
                    return null;
                } else if (present == '[') {
                    // if present element is '[', find whether exists ']',
                    // if not arrayList will be returned as null

                    //A mark to determine if exists ']'
                    String mark = null;

                    //This index will help substring method to determine where is the end
                    int endIndex = 0;

                    for (int j = 0; j < length; j++) {
                        if (expression.charAt (j) == ']') {
                            mark = "right";
                            endIndex = j;
                        }
                        //in case to prevent that the when the mark
                        // is not null any more but there still have more'[',']'
                        if (mark != null) {
                            break;
                        }
                    }

                    if (mark == null) {
                        return null;
                    } else {
                        //in case to prevent index out of the array
                        int aIndex = 0;
                        if (endIndex + 1 == length) {

                            aIndex = endIndex;

                        } else aIndex = endIndex + 1;

                        //To prevent the situation that "[abc]*",after square parentheses there next '*'
                        if (expression.charAt (aIndex) != '*') {
                            //to prevent this case that ']' is in front of '['
                            if (i == 0) {

                                //this case will happen only when there are one letter before the +
                                temp = expression.substring (0, endIndex + 1);
                                //add this String to array list
                                store.add (temp);
                                //to avoid this case "*ksn"
                            } else {
                                //this case will happen when there are more than one letter before the [
                                temp = expression.substring (0, i);
                                temp1 = expression.substring (i, endIndex + 1);

                                //add this String to array list
                                store.add (temp);
                                store.add (temp1);
                            }

                            //remove the string which were added into the array list
                            expression = expression.substring (endIndex + 1, length);

                            //reset the i to 0
                            i = -1;
                            //-----------------------------------------------------------for"[abc]*"----------------------------------------------
                        } else if(expression.charAt (aIndex) == '+'){
                            if (i == 0) {
                                temp = expression.substring (0, endIndex + 2);
                                store.add (temp);
                            } else {
                                temp = expression.substring (0, i);
                                temp1 = expression.substring (i, endIndex + 2);

                                store.add (temp);
                                store.add (temp1);
                            }

                            expression = expression.substring (endIndex + 2, length);

                            i = -1;
                        }else {
                            if (i == 0) {
                                temp = expression.substring (0, endIndex + 2);
                                store.add (temp);
                            } else {
                                temp = expression.substring (0, i);
                                temp1 = expression.substring (i, endIndex + 2);

                                store.add (temp);
                                store.add (temp1);
                            }

                            expression = expression.substring (endIndex + 2, length);

                            i = -1;
                        }
                        //----------------------------------------------------------------------------------------------------------
                    }
                }
            }
        }
        if(expression.length () != 0) {
            //add rest of the expression which have not '+','*','[',']' symbol
            store.add (expression);

        }
        return store;
    }

    /**
    *
    * @Description This method will be used to match the text by regular expression
    * @param line A line of String
     * @param ReguExper A regular expression
    * @return Nothing
    **/

    public static void ExprMatch(int numberOfLine, String line, ArrayList<String> ReguExper){
        //go through every character in the string

        int k = 0;
        //int index = 0;
        //The number of index that the matched string begin
        int startNum = 0;
        //The number of index that the matched string end
        int endNum;
        //****The total number for the states
        int statesNum = ReguExper.size ();
//**********keep the original line
        String oriLine = line;

//****the number of went through states
        int throNum = 0;

//*********keep all the valid text
        ArrayList<String> validStr = new ArrayList<> ();
        String valid;
//**********TO exclude the situation that the text could be nothing
        char operater;
        String line2;
        int f = 0;
        for (int i = 0; i < ReguExper.size (); i++) {
            line2 = ReguExper.get (i);
            operater = line2.charAt (line2.length () - 1);
            if (operater != '*') {
                f = 1;
                break;
            }
        }
        if(f == 0&&line.length () == 0){
            System.out.println ("Match found on line " + numberOfLine +", starting at position "
                    + 1 + " and ending at position " + 1 + ": " );
        }
        //lengthOfUsed

        int LOU = 0;

        line2 = ReguExper.get (ReguExper.size () - 1);
        operater = line2.charAt (line2.length () - 1);

        while(k < line.length ()){


            //the length of the line
            int lenOfLine = line.length ();

//**************one of the character of the string
            char present = line.charAt (k);

//This is the mark to determine if we need to change the value of k
            int vakueK = 0;

//----------------------------------------------state machines--------------------------------------------------------//
//*********** reset the amount of through stages
            if(throNum == statesNum){
                throNum = 0;
            }

            String reguExper = ReguExper.get (throNum);


            //convert expression to array to through every character
            char now[] = reguExper.toCharArray ();
            //mark to judge which kind of this piece that regular expression is
            //1 is '*',2 is '+',3 is "[]"
            int mark = 0;

//----------------regular expression determine whether the text is satisfying-----------------------------------------//

            //assign different mark for different situation in order to choose
            if(now[0] != '[' && now[now.length - 1] == '*'){
                mark = 1;
            }else if(now[now.length - 1] == '+'){
                mark = 2;
            }else if(now[0] == '[' && now[now.length - 1] == ']'){
                mark = 3;
            }else if(now[0] == '[' && now[now.length - 1] == '*'){
                mark = 4;
            }else if(now[0] == '[' && now[now.length - 1] == '+'){
                mark = 5;
            }

            //depends on different situations determine if it's matched
            if(mark == 0){
                //get the length of this string of letters
                int len = now.length;
                //to prevent out of index
                if(len > lenOfLine||(k + len) > line.length ()){
                    break;
                }
                //as a duplication of a part of line
                String str = line.substring (k, k + len);
                if(reguExper.equals (str)){

                    //get one piece of valid string
                    validStr.add (str);

                    line = line.substring (now.length + k, lenOfLine);

                    LOU = LOU + now.length + k;

                    //to move to next piece of regular expression
                    //index++;
                    throNum++;
                    vakueK = 1;

                }else {
                    throNum = 0;
                    validStr.clear ();
                }

//-------------'*'-------
            }else if(mark == 1){
                //the symbol in front of the '*'
                char symbol = now[0];

                //judge the first one of the line if is the symbol
                if(symbol == present){
                    int i = k;
                    //The * could more than zero
                    while(line.charAt (i) == symbol){
                        i++;
                        if(i == line.length ()){break;}
                    }

                    //get one piece of valid string
                    valid = line.substring (k, i);
                    validStr.add (valid);

                    line = line.substring (i,lenOfLine);

                    LOU = LOU + i;

                    //to move to next piece of regular expression
                    throNum++;
                    vakueK = 1;
                //The *could be zero
                }else{
                    //keep point to first character of this line of string,
                    // and use the next pieces of regular expression

                    throNum++;
                    //make sure that after filed first part the k will add 1
                    if(statesNum == 1){
                        throNum = 0;
                    }else vakueK = 2;
                }
//-------------'+'-------
            }else if(mark == 2){
                //the symbol in front of the '+'
                char symb = now[0];
                //judge the first one of the line if is the symbol
                if(symb == present){

                    int j = k;
                    while(line.charAt (j) == symb){
                        j++;
                        if(j == line.length ()){break;}
                    }
                    //get one piece of valid string
                    valid = line.substring (k, j);
                    validStr.add (valid);

                    line = line.substring (j,lenOfLine);

                    LOU = LOU + j;

                    throNum ++;
                    vakueK = 1;
                } else{
                    throNum = 0;
                    validStr.clear ();
                }

//--------------'[',']'-------------
            }else if(mark == 3){
                String newReguExper = reguExper.substring (1,reguExper.length () - 1);
                char []selection = newReguExper.toCharArray ();
                //A mark to determine whether this line contain the character"[abc]"
                int flag = 0;
                for(int i = 0;i < selection.length;i++){
                    if(selection[i] == present){
                        flag = 1;
                    }
                }

                if(flag == 1){
                    //get one piece of valid string
                    validStr.add (Character.toString (present));

                    line = line.substring (k + 1,lenOfLine);

                    LOU = LOU + k + 1;

                    throNum++;
                    vakueK = 1;

                } else {
                    throNum = 0;
                    validStr.clear ();
                }
//--------------'[',']','*'----------
            }else if(mark == 4){
                //"[abc]*"
                String Content = reguExper.substring (1,reguExper.length () - 2);
                char []selection = Content.toCharArray ();

                //make sure that the first character is satisfying or not
                int flag1 = 0;
                //every characters can be determine if they are satisfying
                int mark1 = 0;
                //this  index is used as the last index of this matched text or the beginning of the remnant
                int startIndex = 0;

                for(int i = 0;i < selection.length;i++){
                    if(selection[i] == present){
                        flag1 = 1;
                    }
                }

                if(flag1 == 1){

                    int j = k + 1;
                    while(j < lenOfLine){
                        for(int i = 0;i < selection.length;i++){
                            if(selection[i] == line.charAt (j)){
                                mark1 = 1;
                                break;
                            }else mark1 = 0;
                        }
                        //determine if it is the end of the matched text
                        if(mark1 == 1){
                            j++;
                            if(j == line.length ()){
                                startIndex = j;
                                break;
                            }
                        }else {
                            //the index after the end of the matched text
                            startIndex = j;
                            break;
                        }
                    }
                    //get one piece of valid string
                    valid = line.substring (k, startIndex);
                    validStr.add (valid);

                    line = line.substring (startIndex,lenOfLine);

                    LOU = LOU + startIndex;
                    throNum++;
                    //k = 0;
                    vakueK = 1;

                //the result of the "[abc]*" can be nothing
                }else{

                    throNum++;

                    if(statesNum == 1){
                        throNum = 0;
                    } else vakueK = 2;
                    //k = 0;



                }
//--------------------'[',']','+'----------------
            }else{
                String Content = reguExper.substring (1,reguExper.length () - 2);
                char []selection = Content.toCharArray ();

                int flag2 = 0;
                int mark2 = 0;
                int startIndex = 0;
                for(int i = 0;i < selection.length;i++){
                    if(selection[i] == present){
                        flag2 = 2;
                    }
                }

                if(flag2 == 2){

                    int j = k + 1;
                    while(j < lenOfLine){
                        for(int i = 0;i < selection.length;i++){
                            if(selection[i] == line.charAt (j)){
                                mark2 = 2;
                                break;
                            }else mark2 = 0;
                        }
                        //determine if it is the end of the matched text
                        if(mark2 == 2){
                            j++;
                            if(j == line.length ()){break;}
                        }else {
                            //the index after the end of the matched text
                            startIndex = j;
                            break;
                        }
                    }
                    //get one piece of valid string
                    valid = line.substring (k, startIndex);
                    validStr.add (valid);

                    line = line.substring (startIndex,lenOfLine);

                    LOU = LOU + startIndex;

                    throNum++;
                    //k = 0;
                    vakueK = 1;

                    //the result of the "[abc]+" can be nothing
                }else{
                    throNum = 0;
                    validStr.clear ();
                }
            }
            if(vakueK == 0){
                k++;
            }else if(vakueK == 1){
                k = 0;
            }

            if((throNum == statesNum) || (statesNum == throNum + 1&&line.length () == 0&&operater == '*')){
//get the valid text from array list
                String satisfiedStr = "";
                for(int n = 0; n < validStr.size ();n++){
                    satisfiedStr = satisfiedStr.concat (validStr.get (n));
                }

                //startNum = oriLine.indexOf (satisfiedStr) + 1;
//for find some repeatedly occuring characters
                if(statesNum == 1 && mark == 3){
                    String e = ReguExper.get (ReguExper.size () - 1);
                    char[] anow = e.substring (1,e.length () - 1).toCharArray ();
                    for(int p = 0; p < anow.length;p++){
                        readWord (oriLine,anow[p],0,numberOfLine);
                    }
                    line = "";
                }else{
                    //endNum = startNum + satisfiedStr.length () - 1;
                    endNum = LOU;
                    startNum = endNum - satisfiedStr.length () + 1;


//make sure if the text is already matched
                    if(throNum == statesNum || (statesNum == throNum + 1&&line.length () == 0&&operater == '*')){
                        System.out.println ("Match found on line " + numberOfLine +", starting at position "
                                + startNum + " and ending at position " + endNum + ": " + satisfiedStr);
                    }
                }
                validStr.clear ();
            }
        }
    }

/**
 *
 * @Description Find the location of every signal required characters
 * @param input Obtaining the word
 * @param word The character that are searched
 * @param offset The temporary variable to store the location of word
 * @param numOfLine The digits of the line
 * @return Nothing
 **/

public static void readWord ( String input, char word, int offset, int numOfLine ){
    offset = input.indexOf (word, offset);
    if (offset != -1)
    {
        System.out.println ("Match found on line " + numOfLine +", starting at position "
                + (offset + 1) + " and ending at position " + (offset + 1) + ": " + word);
        readWord (input, word, ++offset, numOfLine);
    }
}
}
