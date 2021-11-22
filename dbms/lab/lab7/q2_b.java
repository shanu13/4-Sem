

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Scanner;

public class q2_b {
	
	public static void main(String[] args) throws SQLException {
		// TODO Auto-generated method stub
		
		Connection connect = null;
		Statement statement = null;
		ResultSet resultSet = null;
		
		 connect= DriverManager.getConnection("jdbc:mysql://localhost:3306/college","root" , "agrawal");
		 System.out.println("Enter the course name to find its room no and timing☺ : ");
		 Scanner scan = new Scanner(System.in);
		 String cname = scan.nextLine();
		 
		 String cn = "'" + cname + "'" ;
		 statement = connect.createStatement();
		 resultSet = statement.executeQuery("select room , meets_at from class where name = " + cn );
		 
		 System.out.println("room\t\t time");
		 while(resultSet.next())
		 {
			 String time = resultSet.getString("meets_at");
			 String room_no = resultSet.getString("room");
			 
			 System.out.println(room_no + "\t\t" + time  );
		 }
		 
		 
		 
		 
		 resultSet.close();
		 statement.close();
		 connect.close();
		 System.out.println("\nData fetched sucessfully!"); 
		
		
		
	}

}
