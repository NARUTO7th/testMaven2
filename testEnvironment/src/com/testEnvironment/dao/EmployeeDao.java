package com.testEnvironment.dao;

import com.testEnvironment.pojo.Employee;
import com.testEnvironment.util.DBUtils;

import java.sql.*;
import java.util.Date;
import java.util.ArrayList;
import java.util.List;

public class EmployeeDao {
    private DBUtils dbUtils;

    public EmployeeDao(){
        dbUtils = new DBUtils ();
    }
    public Employee findEmployeeByNameAndPwd(String name, String password){
        String sql = "select * from tb_employee where name=? and password=?";
        Connection connection = null;
        PreparedStatement ps = null;
        ResultSet rs = null;

        try{
            connection = dbUtils.getConnection ();
            ps = connection.prepareStatement (sql);
            //修改sql语句中的通配符,下标从1开始
            ps.setString(1,name);
            ps.setString (2,password);

            rs = ps.executeQuery ();

            if(rs.next ()){
                Employee employee = new Employee();
                employee.setId (rs.getInt ("id"));
                employee.setE_no (rs.getString ("e_no"));
                employee.setName (rs.getString ("name"));
                employee.setPassword (rs.getString ("password"));
                employee.setBirthday (rs.getDate ("birth"));
                employee.setSalary (rs.getDouble ("salary"));
//--------------------------------------
                //System.out.println (employee.getName () + " " +employee.getPassword ());

                return employee;
            }


        }catch (SQLException e) {
            e.printStackTrace ();
        }finally{
            dbUtils.close (connection,ps,rs);
        }

        return null;
    }

    public List<Employee> findEmployees(){
        String sql = "select * from tb_employee";
        Connection connection = null;
        Statement st = null;
        ResultSet rs = null;
        List<Employee> list = null;

        try{
            connection = dbUtils.getConnection ();
            st = connection.createStatement ();
            rs = st.executeQuery (sql);

            list = new ArrayList<Employee> ();

            while(rs.next ()){
                Employee employee = new Employee();
                employee.setId (rs.getInt ("id"));
                employee.setE_no (rs.getString ("e_no"));
                employee.setName (rs.getString ("name"));
                employee.setPassword (rs.getString ("password"));
                employee.setBirthday (rs.getDate ("birth"));
                employee.setSalary (rs.getDouble ("salary"));
                list.add (employee);
            }


            return list;
        }catch (SQLException e) {
            e.printStackTrace ();
        }finally{
            dbUtils.close (connection,st,rs);
        }

        return list;
    }

    public boolean addEmployee(String e_no,String name,String password,Date birthday,double salary ){
        String sql = "insert into tb_employee(e_no,name,password,birth,salary) values(?,?,?,?,?);";
        Connection connection = null;
        PreparedStatement ps = null;
        try{
            connection = dbUtils.getConnection ();
            ps = connection.prepareStatement (sql);
            //修改sql语句中的通配符,下标从1开始
            ps.setString(1,e_no);
            ps.setString (2,name);
            ps.setString (3,password);
            ps.setDate (4,new java.sql.Date (birthday.getTime ()));
            ps.setDouble (5,salary);

            int lines = ps.executeUpdate ();
            if(lines != 0){
                return true;
            }
        } catch (SQLException e) {
            e.printStackTrace ();
        }finally{
            try{
                connection.close ();
                ps.close ();
            } catch (SQLException e) {
                e.printStackTrace ();
            }
        }
        return false;
    }

    public boolean deleteEById(int id){
        String sql = "delete from tb_employee where id=?";
        Connection connection = null;
        PreparedStatement ps = null;
        try{
            connection = dbUtils.getConnection ();
            ps = connection.prepareStatement (sql);
            ps.setInt(1,id);

            int lines = ps.executeUpdate ();
            if(lines != 0){
                return true;
            }
        } catch (SQLException e) {
            e.printStackTrace ();
        }finally{
            try{
                connection.close ();
                ps.close ();
            } catch (SQLException e) {
                e.printStackTrace ();
            }
        }
        return false;
    }

    public Employee findEmployeeById(int id){
        String sql = "select * from tb_employee where id=?";
        Connection connection = null;
        PreparedStatement ps = null;
        ResultSet rs = null;

        try{
            connection = dbUtils.getConnection ();
            ps = connection.prepareStatement (sql);
            //修改sql语句中的通配符,下标从1开始
            ps.setInt(1,id);

            rs = ps.executeQuery ();

            if(rs.next ()){
                Employee employee = new Employee();
                employee.setId (rs.getInt ("id"));
                employee.setE_no (rs.getString ("e_no"));
                employee.setName (rs.getString ("name"));
                employee.setPassword (rs.getString ("password"));
                employee.setBirthday (rs.getDate ("birth"));
                employee.setSalary (rs.getDouble ("salary"));
//--------------------------------------
                //System.out.println (employee.getName () + " " +employee.getPassword ());

                return employee;
            }

        } catch (SQLException e) {
            e.printStackTrace ();
        }finally{
            dbUtils.close (connection,ps,rs);
        }

        return null;
    }

    public boolean updateEmployee(Employee employee){
        String sql = "update tb_employee set e_no=?,name=?,password=?,birth=?,salary=? where id=?";
        Connection connection = null;
        PreparedStatement ps = null;
        try{
            connection = dbUtils.getConnection ();
            ps = connection.prepareStatement (sql);
            //修改sql语句中的通配符,下标从1开始
            ps.setString(1,employee.getE_no ());
            ps.setString (2,employee.getName ());
            ps.setString (3,employee.getPassword ());
            ps.setDate (4,new java.sql.Date (employee.getBirthday ().getTime ()));
            ps.setDouble (5,employee.getSalary ());
            ps.setInt (6,employee.getId ());

            int lines = ps.executeUpdate ();
            if(lines != 0){
                return true;
            }
        } catch (SQLException e) {
            e.printStackTrace ();
        }finally{
            try{
                connection.close ();
                ps.close ();
            } catch (SQLException e) {
                e.printStackTrace ();
            }
        }
        return false;
    }
}
