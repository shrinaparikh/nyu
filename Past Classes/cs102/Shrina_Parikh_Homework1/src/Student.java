import java.util.ArrayList;
import java.util.Scanner;
import java.io.Serializable;


public class Student extends User implements Serializable, StudentInterface {
	
	static Scanner input = new Scanner(System.in);	

//each student has an arraylist of courses he/she is taking
	private ArrayList<Course> student_courses = new ArrayList<Course>();
	
//constructors
	public Student() {}
	
	private String username;
	private String password;
	private String first_name;
	private String last_name;

	
	public Student(String username, String password, String first_name, String last_name, ArrayList<Course> student_courses) { 
		this.username = username;
		this.password = password;
		this.first_name = first_name;
		this.last_name = last_name;
		this.student_courses = student_courses;

	}
	
	public ArrayList<Course> getStudent_courses() {
		return student_courses;
	}
	
	public void setStudent_courses(ArrayList<Course> student_courses) {
		this.student_courses = student_courses;
	}

//Course Management: view all courses
	public void ViewAllCourses() {
		for(int i = 0; i < Menu.courses_database.size(); i++) {
			Menu.courses_database.get(i).printCourse();
			System.out.println("------------------------------------------");
		}
	}
	
//Course Management: view all courses that are NOT full
	public void ViewAllOpenCourses() {
		for(int i = 0; i < Menu.courses_database.size();i++) {
			if(Menu.courses_database.get(i).getCurrent_num() != Menu.courses_database.get(i).getMax()) {
				Menu.courses_database.get(i).printCourse();
				System.out.println("------------------------------------------");
			}
		}
	}
	
//Course Management: register in a particular course
	public void Register() {
		Student student = Menu.students.get(User.SearchStudents());
		Course course = Menu.courses_database.get(User.SearchCourses());
		if(course.getStudents_enrolled() == null) {
			course.setStudents_enrolled(new ArrayList<String>());
		}
		
		course.enrollStudent(student.getFirst_name(), student.getLast_name());
		
		student_courses.add(course); 
		
		int num = course.getCurrent_num();
		course.setCurrent_num(num + 1);

	}
	
	
//Course Management: withdraw from a course 
	public void Withdraw(Student a) {
		Student student = Menu.students.get(User.SearchStudents());
		Course course = Menu.courses_database.get(User.SearchCourses());
		if(course.getStudents_enrolled() == null) {
			course.setStudents_enrolled(new ArrayList<String>());
		}
		course.getStudents_enrolled().remove(student.getFirst_name() + " " + student.getLast_name());
		int num = course.getCurrent_num();
		course.setCurrent_num(num - 1);
		student.getStudent_courses().remove(course);
		
	}
	
//Course Management: view courses student is currently enrolled in
	public void ViewEnrollment() { 
		for(int i = 0; i < student_courses.size(); i++) {
			System.out.println(student_courses.get(i).getCourse_name());
		}
	}



	
	
	

}
