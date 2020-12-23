import java.io.Serializable;
import java.util.Scanner;

public abstract class User implements Serializable{
	
	static Scanner input = new Scanner(System.in);

//vars
	protected String username;
	protected String password;
	protected String first_name;
	protected String last_name;
	
//getters and setters
	public String getUsername() {
		return username;
	}
	public void setUsername(String username) {
		this.username = username;
	}

	public String getPassword() {
		return password;
	}
	public void setPassword(String password) {
		this.password = password;
	}

	public String getFirst_name() {
		return first_name;
	}
	public void setFirst_name(String first_name) {
		this.first_name = first_name;
	}

	public String getLast_name() {
		return last_name;
	}
	public void setLast_name(String last_name) {
		this.last_name = last_name;
	}
	
//constructors
	public User() {}
	
	public User(String username, String password, String first_name, String last_name) {
		this.username = username;
		this.password = password;
		this.first_name = first_name;
		this.last_name = last_name;
	}
	
	public static int SearchCourses() {
		
		
		System.out.println("What is the course name?");
		String course_name = input.nextLine();
		System.out.println("Who is the instructor?");
		String instructor = input.nextLine();
		
		for(int i = 0; i < Menu.courses_database.size(); i++) {
			if (Menu.courses_database.get(i).getCourse_name().equals(course_name)) {
				if(Menu.courses_database.get(i).getInstructor().equals(instructor)) {
					return i;
				}
			}

		} return -1;
	}

	
//general search method for finding a student by first name and last name
//returns index of student object
	public static int SearchStudents() {
		
		int index = 0;
		
		System.out.println("What is the student's first name?");
		String first_name = input.nextLine();
		System.out.println("What is the student's last name?");
		String last_name = input.nextLine();
		
		for(int i = 0; i < Menu.students.size(); i++) {
			if(Menu.students.get(i).getFirst_name().equalsIgnoreCase(first_name) && Menu.students.get(i).getLast_name().equalsIgnoreCase(last_name)) {
				index = i;
			}
		}
		
		return index;
	}

//method overloading
	public static int SearchStudents(String username, String password) {
		
		int index = 0;
		
		for(int i = 0; i < Menu.students.size(); i++) {
			if(Menu.students.get(i).getUsername().equalsIgnoreCase(username) && Menu.students.get(i).getPassword().equalsIgnoreCase(password)) {
				index = i;
			}
		}
		
		return index;
	}
	
//print method using index of course as parameter
	public void printCourse(int i) {
		System.out.println("Course Name: " + Menu.courses_database.get(i).getCourse_name());
		System.out.println("Course ID: " + Menu.courses_database.get(i).getCourse_id());
		System.out.println("Max enrollment: " + Menu.courses_database.get(i).getMax());
		System.out.println("Current enrollment: " + Menu.courses_database.get(i).getCurrent_num());
		System.out.println("Instructor: " + Menu.courses_database.get(i).getInstructor());
		System.out.println("Section number: " + Menu.courses_database.get(i).getSection());
		System.out.println("Location: " + Menu.courses_database.get(i).getLocation());
		System.out.println("------------------------------------------");
	}
	

	
	
	
	
	
	
}
