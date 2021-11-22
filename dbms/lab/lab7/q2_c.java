

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Scanner;

public class q2_c {

	public static void main(String[] args) throws SQLException {
		// TODO Auto-generated method stub
		
		Connection connect = null;
		Statement statement = null;
		ResultSet resultSet = null;
		
		 connect= DriverManager.getConnection("jdbc:mysql://localhost:3306/college","root" , "agrawal");
		 System.out.println("Enter the name of faculty to find courses taught by him: ");
		 Scanner scan = new Scanner(System.in);
		 String fname = scan.nextLine();
		 
		 String fn = "'" + fname + "'" ;
		 statement = connect.createStatement();
		 resultSet = statement.executeQuery("select c.name from class c , faculty f where c.fid = f.fid and fname = " + fn );
		 
		 System.out.println("courses: ");
		 while(resultSet.next())
		 {
			 String cname = resultSet.getString("name");
			 
			 
			 System.out.println(" " +cname );
		 }
		 
		 
		 
		 	
		 resultSet.close();
		 statement.close();
		 connect.close();
		 System.out.println("\nData fetched sucessfully!"); 
	}

}
