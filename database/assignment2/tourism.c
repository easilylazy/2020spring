

Student(S#, name, gender, birthdate, tel, QQ);
Course(C#, name, department, hours, credits);
Grade(S#, C#, name, date, result);

interface Student (key S#)
{	
	attribute string S#;
	attribute string name;
	attribute string gender;
	attribute string birthdate;
	attribute string tel;
	attribute string QQ;
	

	relationship Set<Course> choose
		inverse Course::chosedBy;
	relationship List<Exam> attend
		inverse Exam::attendedBy;
}
interface Course (key C#)
{
	attribute string C#;
	attribute string name;
	attribute string department;
	attribute float hours;
	attribute float credits;

	relationship Set<Student> chosedBy
		inverse Student::choose;
	relationship List<Exam>  hold
		inverse Exam heldBy

}
interface Exam 
{
	attribute string date;
	attribute float result;


	relationship Course heldBy
		inverse Course::hold;
	relationship Set<Student>::attendedBy
		inverse Student::attend;				
}

