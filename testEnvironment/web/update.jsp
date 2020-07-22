<%@ page import="com.testEnvironment.pojo.Employee" %><%--
  Created by IntelliJ IDEA.
  User: 昊
  Date: 2020/7/18
  Time: 16:13
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>添加用户</title>
</head>
<%
    Employee employee = (Employee) request.getAttribute("employee");
%>
<body>

<form action="${pageContext.request.contextPath}/employee" method="POST">
    <input type="hidden" name="method" value="update"/>
    用户编号：<input type="text" name="e_no" value="<%=employee.getE_no()%>"/><br/>
    用户名：<input type="text" name="username" value="<%=employee.getName()%>"/><br/>
    密码：<input type="text" name="password" value="<%=employee.getPassword()%>"/><br/>
    生日：<input type="date" name="birthday"  value="<%=employee.getBirthday().toString()%>"/><br/>
    薪水：<input type="text" name="salary" value="<%=employee.getSalary()%>"/><br/>
    <input type="submit" value="更新"/>
</form>
</body>
</html>