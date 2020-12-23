import java.util.*; 
import java.lang.*; 
import java.io.*;

//idea and implementation for sort method/this class is taken from GeeksforGeeks
public class SortbyEnrollment implements Comparator<Course>{
    public int compare(Course a, Course b) 
    { 
        return a.getCurrent_num() - b.getCurrent_num(); 
    }
}
