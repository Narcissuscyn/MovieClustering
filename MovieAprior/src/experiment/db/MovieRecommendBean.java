package experiment.db;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

import experiment.util.DBUtil;

public class MovieRecommendBean {
	private DBUtil db = new DBUtil();
	private String sql;
	private Statement stmt = null;
	private ResultSet rs = null;
	private String movieName = null;
	private String year = null;
	private String movieUrl = "";
	private List<String> movieList;
	private int movieCount = 0;

	/**
	 * @return the movieCount
	 */
	public int getMovieCount() {
		return movieCount;
	}

	/**
	 * @param movieCount
	 *            the movieCount to set
	 */
	public void setMovieCount(int movieCount) {
		this.movieCount = movieCount;
	}

	/**
	 * @return the movieList
	 */
	public List<String> getMovieList() {
		return movieList;
	}

	/**
	 * @param movieList
	 *            the movieList to set
	 */
	public void setMovieList(List<String> movieList) {
		this.movieList = movieList;
	}

	/**
	 * @return the movieUrl
	 */
	public String getMovieUrl() {
		return movieUrl;
	}

	/**
	 * @param movieUrl
	 *            the movieUrl to set
	 */
	public void setMovieUrl(String movieUrl) {
		this.movieUrl = movieUrl;
	}

	int userId;
	private boolean movieFlag = false;

	/**
	 * @return the movieFlag
	 */
	public boolean isMovieFlag() {
		return movieFlag;
	}

	/**
	 * @param movieFlag
	 *            the movieFlag to set
	 */
	public void setMovieFlag(boolean movieFlag) {
		this.movieFlag = movieFlag;
	}

	/**
	 * @return the userId
	 */
	public int getUserId() {
		return userId;
	}

	/**
	 * @param userId
	 *            the userId to set
	 */
	public void setUserId(int userId) {
		this.userId = userId;
		System.out.println("设置用户id为：" + userId);
	}

	/**
	 * @return the movieName
	 */
	public String getMovieName() {
		return movieName;
	}

	/**
	 * @param movieName
	 *            the movieName to set
	 */
	public void setMovieName(String movieName) {
		this.movieName = movieName;
		System.out.println("" + movieName);
	}

	/**
	 * @return the stmt
	 */
	public Statement getStmt() {
		return stmt;
	}

	/**
	 * @return the rs
	 */
	public ResultSet getRs() {
		return rs;
	}

	/**
	 * @return the sql
	 */
	public String getSql() {
		return sql;
	}

	/**
	 * @param stmt
	 *            the stmt to set
	 */
	public void setStmt(Statement stmt) {
		this.stmt = stmt;
	}

	/**
	 * @param rs
	 *            the rs to set
	 */
	public void setRs(ResultSet rs) {
		this.rs = rs;
	}

	/**
	 * @param sql
	 *            the sql to set
	 */
	public void setSql(String sql) {
		this.sql = sql;
	}

	public boolean searchMovie() {
		sql = "SELECT movieId,date,url FROM movies WHERE movieName='"
				+ movieName + "'";
		Connection cn = db.getConn();

		try {
			stmt = cn.createStatement();
			if (stmt != null)
				rs = stmt.executeQuery(sql);

		} catch (SQLException e) {
			e.printStackTrace();
		}
		System.out.println("rs生成");
		if (rs == null) {
			System.out.println("rs为空，没有该电影");
			return false;
		}
		System.out.println("rs生不为空");
		try {
			if (!rs.next()) {
				System.out.println("rs没有数据");
				return false;
			}
		} catch (SQLException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		System.out.println("rs有next");
		try {
			setMovieFlag(true);
			setYear(rs.getString("date") + 0);
			System.out.println(getYear());
			setMovieUrl(rs.getString("url"));
			System.out.println(getMovieUrl());
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return true;
	}

	/**
	 * @return the year
	 */
	public String getYear() {
		return year;
	}

	/**
	 * @param year
	 *            the year to set
	 */
	public void setYear(String year) {
		this.year = year;
	}

	// public void

	/**
	 * 获取推荐的电影
	 */
	public void getMovies() {
		sql = "SELECT movieId FROM recommendation WHERE userId=" + userId;
		movieList = new ArrayList<String>();
		Connection cn = db.getConn();

		try {
			stmt = cn.createStatement();
			if (stmt != null)
				rs = stmt.executeQuery(sql);

		} catch (SQLException e) {
			e.printStackTrace();
		}
		System.out.println("rs生成");
		if (rs == null) {
			System.out.println("rs为空，没有该电影");
			return;
		}
		System.out.println("rs生不为空");
		try {
			while (rs.next()) {
				movieCount++;
				int movie_id = rs.getInt("movieId");
				movieList.add(searchMovieById(movie_id));
			}
			System.out.println(movieCount);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	
	public String searchMovieById(int movie_id) {
		sql = "SELECT movieName FROM movies WHERE movieId=" + movie_id;
		Connection cn = db.getConn();
		 Statement stmt1 = null;
		 ResultSet rs1 = null;
		try {
			stmt1 = cn.createStatement();
			if (stmt1 != null)
				rs1 = stmt1.executeQuery(sql);

		} catch (SQLException e) {
			e.printStackTrace();
		}
		System.out.println("rs生成");
		if (rs1 == null) {
			System.out.println("rs为空，没有该电影");
			return null;
		}
		System.out.println("rs生不为空");
		try {
			if (rs1.next()) {
				return rs1.getString("movieName");
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;
	}
}
