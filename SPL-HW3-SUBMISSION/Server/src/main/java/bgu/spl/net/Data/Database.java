package bgu.spl.net.Data;

import java.util.Arrays;
import java.util.Scanner;
import java.util.Vector;
import java.util.concurrent.ConcurrentHashMap;
import java.io.*;

/**
 * Passive object representing the Database where all courses and users are stored.
 * <p>
 * This class must be implemented safely as a thread-safe singleton.
 * You must not alter any of the given public methods of this class.
 * <p>
 * You can add private fields and methods to this class as you see fit.
 */

public class Database {

	private static Database database;                                       //use for singelton
	private ConcurrentHashMap<String,User> Users;                           //hash map between names to users
	private ConcurrentHashMap<Integer, Course> courseMap;                   //relating keys to courses
	private ConcurrentHashMap<Course, Vector<Student>> studentsRegistered;  //relating students to a course

	//to prevent user from creating new Database
	private Database() {
		// Here we shall initialize all
		this.courseMap = new ConcurrentHashMap<>(0);
		this.Users = new ConcurrentHashMap(0);
		this.studentsRegistered = new ConcurrentHashMap(0);
		initialize("./Courses.txt");
	}

	/**
	 * Retrieves the single instance of this class.
	 */
	public static Database getInstance() {		// Synchronize? Noone calls this before multi-threading -> problem if not synched.
		if (database == null)
			database = new Database();
		return database;
	}

	/**
	 * lodes the courses from the file path specified
	 * into the Database, returns true if successful.
	 */
	public boolean initialize(String coursesFilePath) {
		// initialize all fields with courses.txt file data.
		File file = new File(coursesFilePath);
		try {
			Scanner sc = new Scanner(file).useDelimiter("[|\r\n]");
			int ind = 1;
			while (sc.hasNext()){
				int key;		//course number
				String s = sc.next();

				if (s.equals(""))
					key = sc.nextInt();
				else
					key = Integer.parseInt(s);
				String name = sc.next();		//course name

				//Dealing kdam's array
				String preArray = sc.next();
				String[] strings = preArray.substring(1,preArray.length() - 1).split(",");
				if(strings[0].equals(""))
					strings = new String[0];
				int[] kdamArray = Arrays.stream(strings).mapToInt(Integer::parseInt).toArray();

				int maxSize = sc.nextInt();		//course max size

				Course course = new Course(key,name,kdamArray,maxSize,ind);
				ind++;

				studentsRegistered.put(course,new Vector<>());
				courseMap.put(key,course);
			}
		}catch (FileNotFoundException e){
			return false;
		}
		return true;
	}

    /**
     *Adding an admin to database and returning true/false if the addition succeed
     */
	public boolean addAdmin(String[] admin){
		synchronized (Users){
			if(!Users.containsKey(admin[0])){
				Users.put(admin[0], new Admin (admin[0], admin[1]));
				return true;
			}
			else{
				return false;
			}
		}
	}

    /**
     *Adding an student to database and returning true/false if the addition succeed
     */
	public boolean addStudent(String[] student){
		synchronized (Users) {
			if (!Users.containsKey(student[0])) {
				Users.put(student[0], new Student(student[0], student[1]));
				return true;
			} else {
				return false;
			}
		}
	}

    /**
     *returnig the wanted user by his name
     */
	public User getUser(String name){
		return this.Users.get(name);
	}

    /**
     *returning a course by it's name
     */
	public Course getCourse(int courseNum){
		if (!courseMap.containsKey(courseNum))
			return null;
		return this.courseMap.get(courseNum);

	}

    /**
     *Check if a user is in the database
     */
	public boolean containsUser(String name){
		return Users.containsKey(name);
	}
    /**
     *returning the registered students for a specified course
     */
	public Vector<Student> getRegisteredStudents(Course course){
		return studentsRegistered.get(course);
	}
}