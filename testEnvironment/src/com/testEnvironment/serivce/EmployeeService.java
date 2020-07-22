package com.testEnvironment.serivce;

import com.testEnvironment.dao.EmployeeDao;
import com.testEnvironment.pojo.Employee;

import java.util.Date;
import java.util.List;

public class EmployeeService {
    private EmployeeDao ed;

    public EmployeeService(){
        ed = new EmployeeDao ();
    }

    public boolean checkLogin(String name,String password){
        if(ed.findEmployeeByNameAndPwd (name,password) != null){
            return true;
        }
        return false;
    }

    public List<Employee> getEmployees(){
        if(ed.findEmployees ()!=null){
            return ed.findEmployees ();
        }else
            return null;
    }

    public boolean addEmployee(String e_no, String name, String password, Date birthday, double salary){
        return ed.addEmployee (e_no,name,password,birthday,salary);
    }

    public boolean deleteEmployee(int id){
        return ed.deleteEById (id);
    }

    public Employee showEmployeeById(int id){
        return ed.findEmployeeById (id);
    }

    public boolean isUpdate(Employee employee){
        return ed.updateEmployee (employee);
    }
}
