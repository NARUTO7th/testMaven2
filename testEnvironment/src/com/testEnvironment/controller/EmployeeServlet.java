package com.testEnvironment.controller;

import com.testEnvironment.pojo.Employee;
import com.testEnvironment.serivce.EmployeeService;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class EmployeeServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        doPost (req,resp);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String method = request.getParameter ("method");
        //---------------------------------------------
        System.out.println ("The operation is " + method);

        try{
            Method declaredMethod = getClass ().getDeclaredMethod (method, HttpServletRequest.class, HttpServletResponse.class);
            declaredMethod.invoke (this,request,response);
        } catch (Exception e) {
            e.printStackTrace ();
        }
    }

    public void login(HttpServletRequest request,HttpServletResponse response)throws ServletException, IOException{
        String username = request.getParameter ("username");
        String password = request.getParameter ("password");

        //---------------------------------------------
        //System.out.println (username + "  " +password);

        HttpSession session = request.getSession ();

        EmployeeService employeeService = new EmployeeService ();
        boolean result = employeeService.checkLogin (username,password);

        //System.out.println ("Exist? " + result);
        if(result){
            request.setAttribute ("employees", employeeService.getEmployees ());

            session.setAttribute ("name",username);

            RequestDispatcher requestDispatcher = request.getRequestDispatcher ("/main.jsp");
            requestDispatcher.forward (request,response);
        }else{
            //获取项目根目录：/testEnvironment/
            String contextPath = request.getContextPath ();
            response.sendRedirect (contextPath + "/error.jsp");
        }
    }

    public void del(HttpServletRequest request,HttpServletResponse response)throws ServletException, IOException{
        int id = Integer.parseInt (request.getParameter ("id"));
        //System.out.println ("This is del function, id = " + id);

        EmployeeService es = new EmployeeService ();
        if(es.deleteEmployee (id)){
            request.setAttribute ("isDelete",true);
            request.setAttribute ("employees", es.getEmployees ());
            RequestDispatcher requestDispatcher = request.getRequestDispatcher ("main.jsp");
            requestDispatcher.forward (request,response);
        }else{
            request.setAttribute ("isDelete",false);
            request.setAttribute ("employees", es.getEmployees ());
            RequestDispatcher requestDispatcher = request.getRequestDispatcher ("main.jsp");
            requestDispatcher.forward (request,response);
        }
    }

    public void add(HttpServletRequest request,HttpServletResponse response)throws ServletException, IOException{
        String e_no = request.getParameter ("e_no");
        String username = request.getParameter ("username");
        String password = request.getParameter ("password");
        String s1 = request.getParameter ("birthday");
        //ystem.out.println (s1);

        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
        Date parse = null;
        try {
            parse = sdf.parse(s1);
        } catch (ParseException e) {
            e.printStackTrace ();
        }

        String s2 = request.getParameter ("salary");
        Double salary = Double.valueOf (s2);
        EmployeeService employeeService = new EmployeeService ();

        //System.out.println ("This is EmployeeServlet！！");

        if (employeeService.addEmployee (e_no, username, password, parse, salary)) {
            request.setAttribute ("status",true);
            request.setAttribute ("employees", employeeService.getEmployees ());
            RequestDispatcher requestDispatcher = request.getRequestDispatcher ("main.jsp");
            requestDispatcher.forward (request,response);
        }else {request.setAttribute ("status",false);
        request.setAttribute ("employees", employeeService.getEmployees ());
        RequestDispatcher requestDispatcher = request.getRequestDispatcher ("main.jsp");
        requestDispatcher.forward (request,response);}
    }

    public void toUpdate(HttpServletRequest request, HttpServletResponse response)throws ServletException, IOException{
        String id = request.getParameter("id");
        //request.setAttribute ("id",id);

        HttpSession session = request.getSession ();
        session.setAttribute ("id",id);
        EmployeeService employeeService = new EmployeeService ();
        Employee employee = employeeService.showEmployeeById (Integer.valueOf(id));
        request.setAttribute("employee",employee);
        RequestDispatcher requestDispatcher = request.getRequestDispatcher("/update.jsp");
        requestDispatcher.forward(request,response);
    }

    public void update(HttpServletRequest request,HttpServletResponse response)throws ServletException, IOException{
        //String s3 = request.getParameter ("id");
        HttpSession session = request.getSession ();
        String s3 = (String) session.getAttribute ("id");
        System.out.println ("id = " + s3);
        int id = Integer.parseInt (s3);
        String e_no = request.getParameter ("e_no");
        String username = request.getParameter ("username");
        String password = request.getParameter ("password");
        String s1 = request.getParameter ("birthday");


        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
        Date parse = null;
        try {
            parse = sdf.parse(s1);
        } catch (ParseException e) {
            e.printStackTrace ();
        }

        String s2 = request.getParameter ("salary");
        Double salary = Double.valueOf (s2);

        Employee employee = new Employee ();
        employee.setId (id);
        employee.setE_no (e_no);
        employee.setName (username);
        employee.setPassword (password);
        employee.setBirthday (parse);
        employee.setSalary (salary);
        EmployeeService employeeService = new EmployeeService ();

        if(employeeService.isUpdate (employee)){
            request.setAttribute ("isUpdated",true);
            request.setAttribute ("employees", employeeService.getEmployees ());
            RequestDispatcher requestDispatcher = request.getRequestDispatcher ("main.jsp");
            requestDispatcher.forward (request,response);
        }else {
            request.setAttribute ("isUpdated",false);
            request.setAttribute ("employees", employeeService.getEmployees ());
            RequestDispatcher requestDispatcher = request.getRequestDispatcher ("update.jsp");
            requestDispatcher.forward (request,response);
        }
    }
}
