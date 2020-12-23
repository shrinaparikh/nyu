import java.io.IOException;

public interface AdminInterface {	

	public void create_new_course();
	public void delete();
	public void edit();
	public void Display();
	public void RegisterStudent();
	public void ViewAllCourses();
	public void ViewFullCourses();
	public void FullCoursesToFile() throws IOException;
	public void ViewStudentsEnrolled();
	public void View_A_Students_Enrollment();
	public void SortCourses();

	
}
