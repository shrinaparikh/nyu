import java.util.ArrayList;
import java.io.Serializable;

public class Course implements Serializable {
	
//course data fields: course_name, course_id, max, current_num, ArrayList of students_enrolled, instructor, section, location
	private String course_name;
	private String course_id;
	private int max;
	private int current_num;
	ArrayList<String> students_enrolled = new ArrayList<String>();
	private String instructor;
	private int section;
	private String location;
	
//getters and setters
	
	public void setCourse_name(String course_name) {
		this.course_name = course_name;
	}
	public String getCourse_name() {
		return course_name;
	}
	
	public void setCourse_id(String course_id) {
		this.course_id = course_id;
	}
	public String getCourse_id() {
		return course_id;
	}
	
	public void setMax(int max) {
		this.max = max;
	}
	public int getMax() {
		return max;
	}
	
	public void setCurrent_num(int current_num) {
		this.current_num = current_num;
	}
	public int getCurrent_num() {
		return current_num;
	}
	
	public void setInstructor(String instructor) {
		this.instructor = instructor;
	}
	public String getInstructor() {
		return instructor;
	}
	
	public void setSection(int section) {
		this.section = section;
	}
	public int getSection() {
		return section;
	}
	
	public void setLocation(String location) {
		this.location = location;
	}
	public String getLocation() {
		return location;
	}
	
	public ArrayList<String> getStudents_enrolled() {
		if(students_enrolled == null)
		{
			students_enrolled = new ArrayList<String>();
		}
		return students_enrolled;
	}

	public void setStudents_enrolled(ArrayList<String> students) {
		students_enrolled = students;
	}
	
//null constructor
	public Course() {

	}
	
	public Course(String course_name, String course_id, int max, int current_num, ArrayList<String> students_enrolled, String instructor, int section, String location) {
		this.course_name = course_name;
		this.course_id = course_id;
		this.max = max;
		this.current_num = current_num;
		this.students_enrolled = students_enrolled;
		this.instructor = instructor;
		this.section = section;
		this.location = location;
	
	}
	
//add student method
	public void enrollStudent(String first_name, String last_name) {
		String student = first_name + " " + last_name;
		if(students_enrolled.size() < max) {
			students_enrolled.add(student);
		}
		else 
			System.out.println("Course is full!");
	}
	


	
//print statements -> everything besides the students enrolled
	public void printCourse() {
		System.out.println("Course Name: " + this.course_name);
		System.out.println("Course ID: " + this.course_id);
		System.out.println("Max enrollment: " + this.max);
		System.out.println("Current enrollment: " + this.current_num);
		System.out.println("Instructor: " + this.instructor);
		System.out.println("Section number: " + this.section);
		System.out.println("Location: " + this.location);
		System.out.println("------------------------------------------");
	}
	


		
}
