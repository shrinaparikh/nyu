import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.function.*;
import java.util.regex.*;
import java.util.stream.*;
import static java.util.stream.Collectors.joining;
import static java.util.stream.Collectors.toList;

class Result {

    /*
     * Complete the 'CoinGameValue' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts INTEGER_ARRAY V as parameter.
     */

    public static int CoinGameValue(List<Integer> V) {
        
        int s = V.size();
        int i, j, x, y, q;
 
        
        ///half of the table is empty
        int[][] arr = new int[s][s]; 
        
        for(j = 0; j < s; j++) {
            arr[j][j] = V.get(j); //fills diagonal of arr, the base cases 
        }     
        for(j = 0; j < s - 1; j++) {
            arr[j][j+1] = Math.max(V.get(j), V.get(j+1)); //pick max of two elements when only two left
        }
  
        //for rest of table
        for (i = 2; i < s; i++) { 
            for (j = 0; j + i < V.size(); j++) { 
                
                q = arr[j+1][j+i-1]; //to avoid mult calculations
                
                x = V.get(j) + Math.min(arr[j+2][j+i], q);
                y = V.get(j+i) + Math.min(q, arr[j][j+i-2]);
                
                arr[j][j+i] = Math.max(x,y);
            } 
        } 
  
        return arr[0][s - 1]; 
    // Determine the maximum payoff of the given array of coins V for the first player

    }

}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int n = Integer.parseInt(bufferedReader.readLine().trim());

        List<Integer> V = Stream.of(bufferedReader.readLine().replaceAll("\\s+$", "").split(" "))
            .map(Integer::parseInt)
            .collect(toList());

        int m = Result.CoinGameValue(V);

        bufferedWriter.write(String.valueOf(m));
        bufferedWriter.newLine();

        bufferedReader.close();
        bufferedWriter.close();
    }
}