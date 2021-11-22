

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Scanner;

public class q2_a {

	public static void main(String[] args) throws SQLException {
		
		Connection connect = null;
		Statement statement = null;
		ResultSet resultSet = null;
		
		 connect= DriverManager.getConnection("jdbc:mysql://localhost:3306/college","root" , "agrawal");
		 System.out.println("Enter the name of room  to find its classes: ");
		 Scanner scan = new Scanner(System.in);
		 String room = scan.next();
		 String rm = "'" + room + "'" ;
		 statement = connect.createStatement();
		 resultSet = statement.executeQuery("select name from class where room = " + rm );
		 
		 System.out.println("classes name: ");
		 while(resultSet.next())
		 {
			 String cname = resultSet.getString("name");
			 System.out.println(" " + cname);
		 }
		 
		 
		 
		 
		 resultSet.close();
		 statement.close();
		 connect.close();
		 System.out.println("\n Data fetched successfully!"); 
	 	 
	}

}
