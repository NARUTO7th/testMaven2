package com.testEnvironment.util;

import java.sql.*;

public class DBUtils {
    private static String NAME = "root";
    private static String PWD = "123456";
    private static String DRIVER = "com.mysql.cj.jdbc.Driver";
    private static String URL = "jdbc:mysql://localhost:3306/test_e?charactorEncoding=utf-8&serverTimezone=GMT%2B8";

    static{
        try {
            //将driver类加载到JVM中并注册
            Class.forName (DRIVER);
        } catch (ClassNotFoundException e) {
            e.printStackTrace ();
        }
    }

    public Connection getConnection() throws SQLException {
    //这里直接在方法上抛出异常，调用它的方法来处理异常
        Connection connection = DriverManager.getConnection (URL,NAME,PWD);
        return connection;
    }

    public void close(Connection conn, PreparedStatement ps,ResultSet rs){
        try{
            if(conn != null)
                conn.close ();
            if(ps != null)
                ps.close ();
            if(rs != null)
                rs.close ();
        }catch (SQLException e) {
            e.printStackTrace ();
        }
    }

    public void close(Connection conn, Statement st,ResultSet rs){
        try{
            if(conn != null)
                conn.close ();
            if(st != null)
                st.close ();
            if(rs != null)
                rs.close ();
        }catch (SQLException e) {
            e.printStackTrace ();
        }
    }
}
