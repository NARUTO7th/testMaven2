<%@ page import="com.testEnvironment.pojo.Employee" %>
<%@ page import="java.util.List" %><%--
  Created by IntelliJ IDEA.
  User: 昊
  Date: 2020/7/18
  Time: 16:13
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>主页面</title>
</head>

<%
    String name = "";
    if(session==null){
        name = "";
    }

//取出用户数据
name = (String)session.getAttribute("name");

//String name = request.getParameter("username");
List<Employee> employees = (List<Employee>) request.getAttribute("employees");

String a = "";
String b = "";
Object c = request.getAttribute ("status");
Object r = request.getAttribute ("isDelete");
if(c != null){
if((boolean)c) {
    a = " 添加成功 ！！！";
}else a = "添加失败！！！";
}

    if(r != null){
        if((boolean)r) {
            b = " 删除成功 ！！！";
        }else b = "删除失败！！！";
    }
%>
<body>

<p>欢迎你，<%=name%></p>
<p>这是所有的员工信息</p>


    <%if (employees==null){%>
    没有数据！
    <%}else{%>
    <table border="1" cellspacing="0">
        <tr>
            <th>员工编号</th>
            <th>员工姓名</th>
            <th>员工生日</th>
            <th>员工工资</th>
            <th colspan="2">操作</th>
        </tr>
        <%for(Employee e:employees){%>
        <tr>
            <td><%=e.getE_no()%></td>
            <td><%=e.getName()%></td>
            <td><%=e.getBirthday()%></td>
            <td><%=e.getSalary()%></td>
            <td><button onclick="del(<%=e.getId()%>)">删除</button></td>
            <td><button onclick="upd(<%=e.getId()%>)">更新</button></td>
        </tr>
        <%}%>
    </table>
    <%}%>

    <a href="add.jsp">添加用户</a>
    <p><%=a%></p>
    <p><%=b%></p>


</body>
<script>
    function del(id) {
        window.location.href="${pageContext.request.contextPath}/employee?method=del&id="+id;
    }
    function upd(id) {
        window.location.href="${pageContext.request.contextPath}/employee?method=toUpdate&id="+id;
    }
</script>
</html>