<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%
	String path = request.getContextPath();
	String basePath = request.getScheme() + "://"
	+ request.getServerName() + ":" + request.getServerPort()
	+ path + "/";
%>
<jsp:useBean id="movieRecommend"
	class="experiment.db.MovieRecommendBean" scope="page" />

<%
	movieRecommend.setUserId(Integer.parseInt((String) session
	.getAttribute("userId")));
	//获取推荐的电影
	movieRecommend.getMovies();
	
	//查看电影部分：
	if(request.getParameter("movie_search")!=null)
	{
	session.setAttribute("movieName", request.getParameter("movie_search"));
	movieRecommend.setMovieName(request.getParameter("movie_search"));
	movieRecommend.searchMovie();
	}
%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.01 Transitional//EN">
<html>
<head>
<base href="<%=basePath%>">
<title>电影推荐</title>
<meta http-equiv="pragma" content="no-cache">
<meta http-equiv="cache-control" content="no-cache">
<meta http-equiv="expires" content="0">
<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
<meta http-equiv="description" content="This is my page">
<style>
body {
	text-align: center;
	background: url(images/movie_background.jpg);
	background-size: cover;
	background-position: center center;
	background-repeat: no-repeat;
	background-attachment: fixed;
	font-family: Helvetica;
}
</style>

<script type="text/javascript">
	function checkNull() {
		if (document.form_search.movie_search.value == '') {
			return false;
		}
		return true;
	}
</script>
</head>
<body>
	<div style="margin-top:20px;">
		<form name="form_search" method="post" action="recommend.jsp"
			onsubmit="return checkNull()">
			<ul style="float:right;">

				<input name="movie_search" id="movie_search" type="text"
					placeholder="电影名"
					style="width: 280px; height: 35px;font-size: 22px;" />
				<input name="search_btn" type="submit" value="Search"
					style="height: 35px;color: black;font-size: 17px;background:gray">
			</ul>
		</form>
	</div>
	<div style="margin-top:60px;">

		<img src="images/login.jpg"
			style="float:left;width: 206px; margin-left:20px; height: 249px"></img>

		<ul
			style="height: 100px; width: 529px;front-size:23px;margin-top:20px;">
			<h2 style="color: white;text-align:left;">
				movie name:<%
				if (movieRecommend.isMovieFlag()) {
					out.print(movieRecommend.getMovieName());
				}
			%>
			</h2>
			<br />
			<h3 style="color: white;text-align:left;">
				Release date:<%
				if (movieRecommend.isMovieFlag()) {
					out.print(movieRecommend.getYear());
				}
			%>
			</h3>
			<h3 style="color: white;text-align:left;">
				URL:<a
					href=<%if (movieRecommend.isMovieFlag()) {
				out.print("'" + movieRecommend.getMovieUrl() + "'");
			}%>>
					<%
						if (movieRecommend.isMovieFlag()) {
							out.print(movieRecommend.getMovieUrl());
						}
					%>
				</a>
			</h3>
		</ul>
	</div>
	<br/>
	<br/>
	<div style="margin-top:150px;">
		<h1 style="color:yellow; text-align:left;">同类型电影推荐：</h1>
		<br />
		<h3 style="color:yellow; text-align:left;margin-left:40px;">
			<%
				List<String> list = movieRecommend.getMovieList();
				for (int i = 0; i < movieRecommend.getMovieCount(); i++) {
					out.print(list.get(i)
							+ "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");
				}
			%>

		</h3>
		
</body>
</html>
