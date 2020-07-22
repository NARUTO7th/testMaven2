<%--
  Created by IntelliJ IDEA.
  User: 昊
  Date: 2020/7/18
  Time: 16:13
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
  <head>
    <title>登录</title>
  </head>
  <body>

  <form action="${pageContext.request.contextPath}/employee" method="POST">
    <input type="hidden" name="method" value="login"/>
    用户名：<input type="text" name="username"/><br/>
    密码：<input type="password" name="password"/>
    <input type="submit" value="登录"/>
  </form>
  </body>
</html>
