

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Scanner;

public class q1 {

	public static void main(String[] args) throws SQLException {
	
		Connection connect = null;
		Statement statement = null;
		ResultSet resultSet = null;
		
		 connect= DriverManager.getConnection("jdbc:mysql://localhost:3306/college","root" , "agrawal");
		 
		 
			 System.out.println("list of tables: \n1.student \n2.class \n3.faculty \n4.enrolled\n");
			 System.out.println("Enter a table name to view: ");
			 Scanner scan = new Scanner(System.in);
			 String collection = scan.next();
			 
			 statement = connect.createStatement();
			 resultSet = statement.executeQuery("select * from " + collection);
			 
			 while (resultSet.next()) 
			 	{
				 	if(collection.equalsIgnoreCase("student")){
				 		int id = resultSet.getInt("snum");
				 		String name = resultSet.getString("sname");
				 		String major = resultSet.getString("major");
				 		String level = resultSet.getString("level");
				 		int age = resultSet.getInt("age");
				 		
				 		
				 		 
				 		
				 		System.out.println(id + "\t\t" + name + "\t\t" + major + "\t\t" + level + "\t\t" + age );
				 						 		
				 	}
				 	else if(collection.equalsIgnoreCase("class")){
				 		
				 		
				 		String name = resultSet.getString("name");
				 		String meets_at = resultSet.getString("meets_at");
				 		String room = resultSet.getString("room");
				 		int fid = resultSet.getInt("fid");
				 		
				 		
				 		 System.out.println(name + "\t\t" + meets_at + "\t\t" + room + "\t\t" + fid  );
				 						 		
				 	}
				 	else if(collection.equalsIgnoreCase("faculty")){
						 
				 		String fname = resultSet.getString("fname");
				 		int deptid =resultSet.getInt("deptid");	
				 		int fid = resultSet.getInt("fid");
				 		
				 		
				 		 System.out.println(fid+ "\t\t" + fname + "\t\t" +deptid  );
				 						 		
				 	}
				 	else if(collection.equalsIgnoreCase("enrolled")){
						 
				 		String cname = resultSet.getString("cname");
				 		int snum = resultSet.getInt("snum");
		
				 		 System.out.println(snum+ "\t\t" + cname   );
				 						 		
				 	}
				 }
				
			 
		
			 resultSet.close();
			 statement.close();
			 connect.close();
			 System.out.println("\n Data successfully fetched"); 
		 
	}

}
