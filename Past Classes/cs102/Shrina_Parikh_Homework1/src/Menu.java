import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Scanner;


public class Menu implements Serializable{
	
	public static Scanner input = new Scanner(System.in);
	
	private static String admin_user = "Admin";
	private static String admin_password = "Admin001";

	public static Student a;
	public static Admin admin = new Admin();
	public static ArrayList<Course> courses_database = new ArrayList<Course>();
	public static ArrayList<Student> students = new ArrayList<Student>();
	
	public static void main(String[] args) throws IOException {
	//serialization, reading .csv, and deserialization
		System.out.println("Is the first time this Course Registration System is being used? Please enter 'Yes' or 'No'");
		String answer = input.next();
		if(answer.equalsIgnoreCase("yes")) {
			
			readCSV(courses_database);
			
			Serialization();
			SerializationStudents();
			
			System.out.println("----------------------------------------------------");

		}
		else if(answer.equalsIgnoreCase("no")){
			Deserialization();
			DeserializationStudents();

		}
		
		
		
		
	//check if Admin or Student, then display respective Menu method
		System.out.println("Are you an Admin or a Student? Please enter 'Admin' or 'Student'");
		String user_type = input.next();
		
		if(user_type.equalsIgnoreCase("Admin")) {
			if(checkAdmin()) {
				admin =  new Admin(admin_user, admin_password);
				AdminMenu();
			}
			else {
				System.out.println("Wrong login");
			}
		}
		
		else if(user_type.equalsIgnoreCase("Student")) {
			
			System.out.println("What is your username?");
			String user = input.next();
			System.out.println("What is your password?");
			String password = input.next();
			
			if (students.size() != 0) {
				for (int i = 0; i < students.size(); i++) {
					if (students.get(i).getUsername().equals(user) && students.get(i).getPassword().equals(password)) {
						a = students.get(i);
						System.out.println(a.getFirst_name() + a.getLast_name() + a.getUsername());
						StudentMenu();
					}
				}
			}
			else {
				System.out.println("No students registered so far or student not found");
			}
		}
			

		

			
}

	

	
	
	
	
//Check admin credentials
	public static boolean checkAdmin() {
		System.out.println("What is your username?");
		String user = input.next();
		System.out.println("What is your password?");
		String password = input.next();
		
		if(user.equalsIgnoreCase(admin_user) && password.equalsIgnoreCase(admin_password)) {
			return true;
		}
		
		return false;
	}
	

//student menu
	public static void StudentMenu() {
		
		while(true) {
			System.out.println("What would you like to do? Please enter the corresponding number\n1. View all courses\n" +
					"2. View all courses that are not full\n3. Register in a course\n4. Withdraw from a course\n" +
					"5. View all courses you are currently enrolled in\n6. Exit\n" + "----------------------------------------------------");
			int choice = input.nextInt();
			if(choice == 1) {
				a.ViewAllCourses();
			} else if(choice == 2) {
				a.ViewAllOpenCourses();
			} else if(choice == 3) {
				a.Register();
			} else if(choice == 4) {
				a.Withdraw(a);
			} else if(choice == 5) {
				a.ViewEnrollment();
			} else {
				Serialization();
				SerializationStudents();
				break;
			}
			
		}
		
	}
	
//admin menu
	public static void AdminMenu() throws IOException {
		while(true) {
			System.out.println("What would you like to do? Please enter the corresponding number:\n"
					+ "1. Course Management\n2. View Reports\n" + "3. Exit\n" + "----------------------------------------------------");
			int choice = input.nextInt();
			if(choice == 1) {
				AdminCourseManagement();
			}
			else if(choice == 2) {
				AdminViewReports();
			}
			else if(choice == 3) {
				Serialization();
				SerializationStudents();
				break;
			}
		}

	}
	
	public static void AdminCourseManagement() {
		while(true) {
			System.out.println("What would you like to do? Please enter the corresponding number\n1. Create a new course\n"
					+ "2. Delete a course\n3. Edit a course\n4. Display information for a given course\n5. Register a student\n"
					+ "6. Exit\n" + "----------------------------------------------------");
			int choice = input.nextInt();
			if(choice == 1) {
				admin.create_new_course();
			} else if(choice == 2) {
				admin.delete();
			} else if(choice == 3) {
				admin.edit();
			} else if(choice == 4) {
				admin.Display();
			} else if(choice == 5) {
				admin.RegisterStudent();
			} else 
				break;
		}
			
	}
	
	public static void AdminViewReports() throws IOException {
		while(true) {
			System.out.println("What would you like to do? Please enter the corresponding number\n1. View all courses\n"
					+ "2. View all full courses\n3. Write to a file the list of courses that are full\n"
					+ "4. View the list of students registered in a specific course\n"
					+ "5. View the list of courses a given student is registered in\n"
					+ "6. Sort the list of courses by amount of students enrolled\n7. Exit\n" 
					+ "----------------------------------------------------");
			int choice = input.nextInt();
			if(choice == 1) {
				admin.ViewAllCourses();
			} else if(choice == 2) {
				admin.ViewFullCourses();
			} else if(choice == 3) {
				admin.FullCoursesToFile();
			} else if(choice == 4) {
				admin.ViewStudentsEnrolled();
			} else if(choice == 5) {
				admin.View_A_Students_Enrollment();
			} else if(choice == 6) {
				admin.SortCourses();
			} else
				break;
		}
	}
	
	
//read in CSV information and put it into array
	public static void readCSV(ArrayList courses_database) {
		String filename = "src/MyUniversityCourses.csv";
		File file = new File(filename); //creates a new file
		try {
			Scanner inputStream = new Scanner(file);
			inputStream.nextLine();
			while(inputStream.hasNextLine()) {
				String data = inputStream.nextLine(); //use next or nextline? //does this ignore the header line?
				String[] values = data.split(",");
				String course_name = values[0];
				String course_id = values[1];
				int max = Integer.parseInt(values[2]);
				int current_num = Integer.parseInt(values[3]);
				ArrayList<String> students_enrolled = new ArrayList<String>();
				String instructor = values[5];
				int section = Integer.parseInt(values[6]);
				String location = values[7];
				Course x = new Course(course_name, course_id, max, current_num, students_enrolled, instructor, section, location);
				courses_database.add(x);
			}
			inputStream.close();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
	}
	

//performs serialization of courses_database
		public static void Serialization() {
			
			try {
				
				FileOutputStream fos = new FileOutputStream("courses_database.ser");
				
				ObjectOutputStream oos = new ObjectOutputStream(fos);
				
				oos.writeObject(courses_database); 
				
				oos.close();
				fos.close();
			
			}
			catch (IOException ioe){
				ioe.printStackTrace(); 
			}	
		}
	
		

//performs Serialization of Students arraylist
	public static void SerializationStudents() {
			
		try {
			
			
			FileOutputStream fos = new FileOutputStream("students.ser");
				
			ObjectOutputStream oos = new ObjectOutputStream(fos);
				
			oos.writeObject(students); 
				
			oos.close();
			fos.close();
			
		}
		catch (IOException ioe){
			ioe.printStackTrace(); 
		}	
	}
		

//performs deserialization of courses_database		
		public static void Deserialization() { 
			 try{
				 
				 FileInputStream fis = new FileInputStream("courses_database.ser"); 
				 
				 ObjectInputStream ois = new ObjectInputStream(fis);
				 
				 courses_database = (ArrayList<Course>)ois.readObject();
				 ois.close();
				 fis.close();
				 
				 
			    }
			    catch(IOException ioe) {
			       ioe.printStackTrace();
			       return;
			    }
			 catch(ClassNotFoundException cnfe) { 
			       cnfe.printStackTrace();
			       return;
			     }

			 }
	
//performs deserialization of students 
		public static void DeserializationStudents() { 
			 try{
				 
				 FileInputStream fis = new FileInputStream("students.ser"); 
				 
				 ObjectInputStream ois = new ObjectInputStream(fis);
				 
				 students = 	(ArrayList<Student>)ois.readObject();
				 ois.close();
				 fis.close();
			    }
			    catch(IOException ioe) {
			       ioe.printStackTrace();
			       return;
			    }
			 catch(ClassNotFoundException cnfe) { 
			       cnfe.printStackTrace();
			       return;
			     }

			 }
	
	
	

}
