package lab1;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;


class Employee{
    String emp_id,name,city,dept_id;

    Employee(String empid ,String name ,String city ,String deptid){
        this.emp_id = empid;
        this.name = name;
        this.city = city;
        this.dept_id = deptid;
    }

    String getEmpId(){
        return this.emp_id;
    }
    String getName(){
        return this.name;
    }
    String getCity(){
        return this.city;
    }
    String getDeptId(){
        return this.dept_id;
    }

}

class Department {
    String dept_id,dept_name,dept_budget;

    Department(String deptid,String name, String budget){
        this.dept_id = deptid;
        this.dept_name = name;
        this.dept_budget = budget;
    }

    String getId(){
        return this.dept_id;
    }
    String getName(){
        return this.dept_name;
    }
    String getBudget(){
        return this.dept_budget;
    }
}



public class a1 {

  


    public static void main(String[] args) {
        List<Employee> employeeList = new ArrayList<Employee>();
        System.out.print("Hello World");
        FileReader empfile = new FileReader("Department.txt");
        BufferedReader reademp = new BufferedReader(empfile); 
        String line = reademp.readLine();
        while(line!= null)

        // employeeList.add(new Employee("111","shantanu","tikamgarh","115"));
    }
}
