<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%
	String path = request.getContextPath();
	String basePath = request.getScheme() + "://"
			+ request.getServerName() + ":" + request.getServerPort()
			+ path + "/";
%>
<%
	if (request.getParameter("user_id") !=null) {
		session.setAttribute("userId", request.getParameter("user_id"));
%>
<jsp:forward page="recommend.jsp" />
<%
	}
%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>


<head>
<base href="<%=basePath%>">

<title>用户登录</title>

<meta http-equiv="pragma" content="no-cache">
<meta http-equiv="cache-control" content="no-cache">
<meta http-equiv="expires" content="0">
<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
<meta http-equiv="description" content="This is my page">
<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->


<style>
body {
	text-align: center;
	background: url(images/login.jpg);
	background-size: cover;
	background-position: center center;
	background-repeat: no-repeat;
	background-attachment: fixed;
	font-family: Helvetica;
}
</style>

<script type="text/javascript">
	function checkNull() {
		if (document.form_search.user_id.value=='') {
			return false;
		}
		return true;
	}
</script>
</head>

<body>
	<form name="form_search" method="post" action="login.jsp" onsubmit="return checkNull()">
		<ul style="float:left;margin-top:80px;">
			<input name="user_id" id="user_id" type="text" placeholder="请输入用户编号"
				style="width: 280px; height: 50px;font-size: 24px;" />
			<input name="ok_btn" id="ok_btn"type="submit" value="确定"
				style="height: 50px;color: black;font-size: 24px;background:orange;" />
		</ul>
	</form>
</body>
</html>
