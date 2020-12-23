import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Serializable;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

public class Admin extends User implements AdminInterface, Serializable{
	
	static Scanner input = new Scanner(System.in);
	
//constructors
	public Admin() {
		super();
	}
	
	public Admin(String username, String password) {
		this.username = username;
		this.password = password;
	}
	
//Course Management: create a new course
	public void create_new_course() {
		System.out.println("Enter the course name");
		String course_name = input.nextLine();
		System.out.println("Enter the course id");
		String course_id = input.nextLine();
		System.out.println("Enter the max enrollment");
		int max = input.nextInt();
		System.out.println("Enter the current enrollment");
		int current_num = input.nextInt();
		input.nextLine();
		System.out.println("Enter the instructor");
		String instructor = input.nextLine();
		System.out.println("Enter the section number");
		int section = input.nextInt();
		input.nextLine();
		System.out.println("Enter the location");
		String location = input.nextLine();
		
		ArrayList<String> students_enrolled = new ArrayList<String>();
		
		Course x = new Course(course_name, course_id, max, current_num, students_enrolled, instructor, section, location);
		
		Menu.courses_database.add(x);
		
		Menu.Serialization();
	}
	
//method overloading 
	public void create_new_course(String course_name, String course_id, int max, int current_num, String instructor, int section, String location) {
		
		ArrayList<String> students_enrolled = new ArrayList<String>();
		
		Course x = new Course(course_name, course_id, max, current_num, students_enrolled, instructor, section, location);
		
		Menu.courses_database.add(x);
		
		Menu.Serialization();
	}
	
//Course Management: Delete a course
	public void delete() {
		System.out.println("What is the name of the course you wish to delete?");
		String name = input.nextLine();
		input.nextLine();
		System.out.println("What is the section number?");
		int sec = input.nextInt();
		for (int i = 0; i < Menu.courses_database.size(); i++) {
			if (Menu.courses_database.get(i).getCourse_name().equals(name) && Menu.courses_database.get(i).getSection() == sec) {
				Menu.courses_database.remove(i);
			}
		}
	}
	
//Course Management: Edit a course, everything EXCEPT course_id and course_name
//Admin may edit students_enrolled by registering students in courses, which is in a different method
	public void edit() {
		
		System.out.println("What is the name of the course you wish to edit?");
		
		String name = input.nextLine();
		
		input.nextLine(); 
		
		System.out.println("What is the section number?");
		int sec = input.nextInt();
		
		for(int i = 0; i < Menu.courses_database.size(); i++) {
			if (Menu.courses_database.get(i).getCourse_name().equals(name) && Menu.courses_database.get(i).getSection() == sec) {
				while(true) {
					System.out.println("What would you like to edit?\n" + "1. Maximum enrollment\n" + "2. Current number of students enrolled\n" +
							"3. Instructor\n" + "4. Section\n" + "5. Location\n" + "6. Done editing this course\n" + 
							"-------------------------------------------------");
					int choice = input.nextInt();
					if(choice == 1) {
						System.out.println("What would you like the new max to be?");
						int max = input.nextInt();
						Menu.courses_database.get(i).setMax(max);
					}
					else if(choice == 2) {
						System.out.println("What is the current number of students enrolled in this class?");
						int enrollment = input.nextInt();
						Menu.courses_database.get(i).setCurrent_num(enrollment);
					}
					else if(choice == 3) {
						input.nextLine();
						System.out.println("Who is the new instructor?");
						String instructor = input.nextLine();
						Menu.courses_database.get(i).setInstructor(instructor);
					}
					else if(choice == 4) {
						System.out.println("What is the new section number?");
						int section_new = input.nextInt();
						Menu.courses_database.get(i).setSection(section_new);
						System.out.println("You must re-enter the course to continue editing.");
					}
					else if(choice == 5) {
						input.nextLine();
						System.out.println("What is the new location?");
						String location = input.nextLine();
						Menu.courses_database.get(i).setLocation(location);
					}
					else if(choice == 6) {
						break;
					}
				}
				Menu.Serialization();
			}
	}
	}		
		
	
//Course Management: Display Information for a given course by course_id
	public void Display() {
		
		System.out.println("Enter the course id");
		String course_id = input.next();

		for(int i = 0; i < Menu.courses_database.size(); i++) {
			if (Menu.courses_database.get(i).getCourse_id().equalsIgnoreCase(course_id)) {
				printCourse(i);
			}
		}
		
	}

	
//Course Management: Register a student
//Admin can add students name and temporary username and password
	public void RegisterStudent() {
		System.out.println("Enter student first name");
		String first_name = input.next();
		System.out.println("Enter student last name");
		String last_name = input.next();
		System.out.println("Enter the student's username");
		String username = input.next();
		System.out.println("Enter the student's password");
		String password = input.next();
		
		Student x = new Student();
		x.setFirst_name(first_name);
		x.setLast_name(last_name);
		x.setUsername(username);
		x.setPassword(password);
		x.setStudent_courses(new ArrayList<Course>());
		
		Menu.students.add(x);
		
		
		for(int i = 0; i < Menu.students.size(); i++) {
			System.out.println(Menu.students.get(i).getFirst_name()); 
		}
		Menu.SerializationStudents();
	
	}
	
//Reports: Admin can view every course
	public void ViewAllCourses() { 
		for(int i = 0; i < Menu.courses_database.size(); i++) {
			printCourse(i);
		}
	}
	
	
	
//overrides print method in User class
@Override
	public void printCourse(int i) {
		System.out.println("Course: " + Menu.courses_database.get(i).getCourse_name());
		System.out.println("Course id: " + Menu.courses_database.get(i).getCourse_id());
		System.out.println("Current Enrollment Number: " + Menu.courses_database.get(i).getCurrent_num());
		System.out.println("Max Enrollment: " + Menu.courses_database.get(i).getMax());

		System.out.println("----------------------------------------------------");
}

//Reports: View all courses that are full
	public void ViewFullCourses() {
		
		for(int i = 0; i < Menu.courses_database.size(); i++) {
			if(Menu.courses_database.get(i).getCurrent_num() == Menu.courses_database.get(i).getMax()) {
				System.out.println(Menu.courses_database.get(i).getCourse_name());
			}
		}
	}
	
//Reports: Write to a file the list of courses that are full
	public void FullCoursesToFile() throws IOException {
		String fullcourses_string = "";
		
		for(int i = 0; i < Menu.courses_database.size(); i++) {
			if(Menu.courses_database.get(i).getCurrent_num() == Menu.courses_database.get(i).getMax()) {
				fullcourses_string = fullcourses_string + Menu.courses_database.get(i).getCourse_name() + "\n";
				BufferedWriter writer = new BufferedWriter(new FileWriter("FullCourses.txt"));
				writer.write(fullcourses_string);
				writer.close();
			}
		}
	}


//Reports: View names of students enrolled in a specific course
	public void ViewStudentsEnrolled() {
		
		int index = SearchCourses();
		Course x = Menu.courses_database.get(index);

		
		if(x.getStudents_enrolled() != null) {
			for (int i = 0; i < x.getStudents_enrolled().size(); i++) {
				System.out.println(x.students_enrolled.get(i));
			}
			System.out.println("----------------------------------------------------");
		}
		else {
			System.out.println("no students enrolled\n");
		}
		
	}
	
//Reports: view the list of courses a particular student is enrolled in
	public void View_A_Students_Enrollment() {
		int index = SearchStudents();
		Menu.students.get(index).ViewEnrollment();
	}
	
	
//Sort courses based on current number of students enrolled
	
	public void SortCourses() {
		Collections.sort(Menu.courses_database, new SortbyEnrollment());
		for(int i=0; i < Menu.courses_database.size(); i++) {
			printCourse(i);
		}
	}
	
	

}
