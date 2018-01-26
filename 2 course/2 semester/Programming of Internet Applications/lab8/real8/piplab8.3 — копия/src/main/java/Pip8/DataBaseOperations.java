package Pip8;

import com.vsaf.common.Point;

import java.util.ArrayList;
import java.util.List;
import java.sql.*;


public class DataBaseOperations {

    private Connection connection = null;
    PreparedStatement add_statement = null;
    PreparedStatement delete_statement = null;
    PreparedStatement readall_statement = null;
	
	
    private void open_connection(){

	
	
        if(connection == null){

            try {   

                Class.forName("org.postgresql.Driver");

            } catch (ClassNotFoundException e) {

                System.out.println("No PostgreSQL JDBC Driver?");
                e.printStackTrace();
                return;

            }

            System.out.println("PostgreSQL JDBC Driver registering");

            try {
                connection = DriverManager.getConnection("jdbc:postgresql://127.0.0.1:6090/postgres", "s208070","yxu697");
                String insertTableSQL = "INSERT INTO point"
                        + "(x, y, r, contained) VALUES"
                        + "(?,?,?,?)";
                add_statement = connection.prepareStatement(insertTableSQL);  
                delete_statement = connection.prepareStatement("DELETE FROM points");  
                readall_statement = connection.prepareStatement("SELECT * FROM points");  

            } catch (SQLException e) {

                System.out.println("Connection Failed! Check output console");
                e.printStackTrace();
                return;

            }
        }
    }

    private void close_connection(){
        try{
            if(connection != null){
                connection.close();
            }  
        } catch (SQLException ex){

        }
    }


    public void addPoint(Point point){

        open_connection();
        if (connection != null) {

            try {
            
                if(add_statement != null){
                    System.out.println("Adding values x:" + point.getX() + "y:" + point.getY() + "r:" + point.getRadius());
                    add_statement.setFloat(1, point.getX());//x
                    add_statement.setFloat(2, point.getY());//y
                    add_statement.setFloat(3, point.getRadius());//r
                    add_statement.setBoolean(4, point.isIncluded());//included

                    add_statement.executeUpdate();
                }
                else {
                    System.out.println("no statement");
                }

            }catch (Exception e){}

        } else {
            System.out.println("Failed to make connection");
        }


    }

    public void deleteAllPoints(){
        open_connection();
        if (connection != null) {

            try {
            
                if(delete_statement != null){
                    delete_statement.executeUpdate();
                }
                else {
                    System.out.println("no statement");
                }

            }catch (Exception e){}

        } else {
            System.out.println("Failed to make connection");
        }

    }


    public ArrayList<Point> readAllTable(){

        open_connection();
        ArrayList<Point> points = new ArrayList<Point>();
        if (connection != null) {

            try {
            
                if(readall_statement != null){
                    ResultSet rs = null;
                    
                    rs = add_statement.executeQuery();
                    while(rs.next()){
                        points.add(new Point(rs.getFloat("x"),rs.getFloat("y"),rs.getFloat("x")));
                    }
                }
                else {
                    System.out.println("no statement");
                }

            }catch (Exception e){}

        } else {
            System.out.println("Failed to make connection");
        }
        return points;
    }

}
