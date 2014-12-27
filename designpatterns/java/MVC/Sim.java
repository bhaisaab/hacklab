public class Sim {
    public static void main(String[] args) {
        //fetch student record based on his roll no from the database
        StudentModel model  = retriveStudentFromDatabase();

        //Create a view : to write student details on console
        StudentView view = new StudentView();

        StudentController controller = new StudentController(model, view);

        controller.updateView();

        //update model data
        controller.setStudentName("John");

        controller.updateView();
    }

   private static StudentModel retriveStudentFromDatabase(){
      StudentModel student = new StudentModel();
      student.setName("Robert");
      student.setRollNo("10");
      return student;
   }
}
