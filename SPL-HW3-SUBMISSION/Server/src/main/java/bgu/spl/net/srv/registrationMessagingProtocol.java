package bgu.spl.net.srv;

import bgu.spl.net.Data.Admin;
import bgu.spl.net.Data.Course;
import bgu.spl.net.Data.Database;
import bgu.spl.net.Data.Student;
import bgu.spl.net.api.MessagingProtocol;

import java.util.Arrays;
import java.util.Vector;

public class registrationMessagingProtocol implements MessagingProtocol<String> {

    private boolean shouldTerminate;
    private Database db;        //accesses to the database
    private short op;           //opCode defined by the assignment's protocol
    private String username;

    public registrationMessagingProtocol(){
        shouldTerminate = false;
        db = Database.getInstance();
        op = 0;
        username = null;
    }

    /**
    *process divides the input message into two categories
    * 1. opCodes that use null char as delimiters (1,2,3,8)
    * 2. pre defined message without delimiters   (4,5,6,7,9,10,11)
    * then it sends the message to the correspondent procedure
    **/
    public String process(String msg) {

        op = findOP(msg);

        if(op == 1 || op == 2 || op == 3 || op == 8)        // Messages with zeros.
            return definedByZeros((String) msg);
        else
            return definedNotByZeros((String) msg);
    }

    /**
    *This method split the message into sub-strings and dealing
    * with the message according to the opCode
    **/
    private String definedByZeros(String msg){

        String[] data = msg.substring(2,msg.length()).split("\0");

        if(op == 1){                // ADMINREG
            if (username != null)
                return "1301";
            if (db.addAdmin(data)){
                return "1201\0";
            }
            return "1301";
        }

        else if(op == 2){           //  STUDENTREG
            if (username != null)
                return "1302";
            if (db.  addStudent(data)){
                return "1202\0";
            }
            return "1302";
        }

        else if(op == 3){           //  LOGIN
            if (username != null)
                return "1303";
            this.username = data[0];
            if (!db.containsUser(username) || !data[1].equals(db.getUser(username).getPassword()) || db.getUser(username).isLoggedIn()) {
                this.username = null;
                return "1303";
            }
            db.getUser(username).setLoggedIn(true);
            return "1203\0";
        }

        else {                      //  op=8 -> STUDENTSTAT
            if (!isLoggedInAdmin() || db.getUser(data[0]) == null) {
                return "1308";
            }
            ((Student)(db.getUser(data[0]))).sortCoursesByFileOrder();
            return "1208" + "Student: " + data[0] + "\n" + "Courses: " +
                    ((Student)(db.getUser(data[0]))).getStringCourses() + "\0";
        }
    }

    /**
    *This method dealing with the pre defined messages
    * according to the opCode (no delimiters)
    **/
    private String definedNotByZeros(String msg){
        if(op == 4){            //LOGOUT
            if(username == null)
                return "1304";
            else{
                db.getUser(username).setLoggedIn(false);
                username = null;
		shouldTerminate = true;
                return "1204\0";
            }
        }

        else if(op == 5){       //COURSEREG
            if (!isLoggedInStudent()){
                return "1305";
            }
            else {
                int courseNum = FindCourseNum(msg.substring(2));
                if (db.getCourse(courseNum) != null
                        && (db.getCourse(courseNum).isAvailabale())
                        && !(((Student)db.getUser(username)).hasCourse(courseNum))
                        && (hasKdam(username,courseNum))) {

                    ((Student)db.getUser(username)).takeCourse(db.getCourse(courseNum));
                    db.getRegisteredStudents(db.getCourse(courseNum)).add(((Student)db.getUser(username)));
                    return "1205\0";
                }
                else
                    return "1305";
            }
        }
        else if(op == 6){       //  KDAMCHECK
            if (username == null || db.getCourse(FindCourseNum(msg.substring(2))) == null){
                return "1306";
            }
            else {
                int courseNum = FindCourseNum(msg.substring(2));
                String message = "1206";
                Course c = db.getCourse(courseNum);
                int[] CourseKdam = c.getCourseKdam();
                if (CourseKdam.length == 0)
                    return message + "\0";
                return message + Arrays.toString(CourseKdam) + "\0";
            }
        }
        else if(op == 7){       //COURSESTAT
            if (!isLoggedInAdmin()){
                return "1307";
            }
            else {
                String message = "1207Course: ";
                int courseNum = FindCourseNum(msg.substring(2));
                Course c = db.getCourse(courseNum);
                message += "(" + courseNum + ") " + c.getCourseName() +"\nSeats Available: " +
                        (c.getCourseMaxSize()-c.getCurrentSize()) + "/" + c.getCourseMaxSize() + "\n";
                Vector<Student> v = db.getRegisteredStudents(db.getCourse(courseNum));
                String[] sortedStudentsNames = sortNames(v);
                message += "Students Registered: " + Arrays.toString(sortedStudentsNames) + "\0";
                return message;
            }
        }
        else if (op == 9){      //ISREGISTERED
            if (!isLoggedInStudent()){
                return "1309";
            }
            boolean b = ((Student)db.getUser(username)).hasCourse(FindCourseNum(msg.substring(2)));
            if (b)
                return "1209REGISTERED\0";
            else
                return "1209NOT REGISTERED\0";
        }
        if (op == 10){      //UNREGISTER
            if (username == null || !db.containsUser(username) || !db.getUser(username).isLoggedIn() || !((Student)db.getUser(username)).hasCourse(FindCourseNum(msg.substring(2)))){
                return "1310";
            }
            db.getRegisteredStudents(db.getCourse(FindCourseNum(msg.substring(2)))).remove(((Student)db.getUser(username)));
            ((Student) db.getUser(username)).removeCourse(FindCourseNum(msg.substring(2)));
            return "1210\0";
        }
        else if (op == 11){     //MYCOURSES
            if (username == null || !db.containsUser(username) || !db.getUser(username).isLoggedIn()){
                return "1311";
            }
            return "1211" + ((Student)db.getUser(username)).getStringCourses() + "\0";
        }
        return null;
    }

    /**
    *this method check if a student has registered to a specific course
    * i.e, he have this course as a kdam
    **/
    private boolean hasKdam(String username, int courseNum) {
        Course course = db.getCourse(courseNum);
        int[] kdams = course.getCourseKdam();
        for (int i: kdams){
            if (!(((Student)db.getUser(username)).hasCourse(i)))
                return false;
        }
        return true;
    }

    /**
    *this method send an message string as an input
    * and returning the course's number as an int
    **/
    private int FindCourseNum(String msg) {
        byte[] b = new byte[2];
        b[0] = (byte) msg.charAt(0);
        b[1] = (byte) msg.charAt(1);
        return bytesToShort(b);
    }

    /**
    *This method extracting the op code from the input string
    **/
    private short findOP(String msg){
        return Short.parseShort(msg.substring(0,2));
    }

    /**
    *This method check if a username is login to the server
    * and also admin
    **/
    private boolean isLoggedInAdmin(){
        if(username == null || !db.getUser(username).isLoggedIn() || !(db.getUser(username) instanceof Admin))
            return false;
        return true;
    }

    /**
    *This method check if a username is login to the server
    * and also student
    **/
    private boolean isLoggedInStudent(){
        if(username == null || !db.getUser(username).isLoggedIn() || !(db.getUser(username) instanceof Student))
            return false;
        return true;
    }

    /**
    *This method sort a vector of student according
    * to an lexicographic order
    **/
    private String[] sortNames(Vector<Student> std){
        String[] s = new String[std.size()];
        int j = 0;
        for(Student i:std){
            s[j] = i.getUsername();
            j++;
        }
        Arrays.sort(s);
        return s;
    }

    @Override
    public boolean shouldTerminate(){
        return shouldTerminate;
    }

    /**
    *Converting a byte array to short
    **/
    public short bytesToShort(byte[] byteArr){
        short result = (short)((byteArr[0] & 0xff) << 8);
        result += (short)(byteArr[1] & 0xff);
        return result;
    }

    /**
    *Converting short to a byte array
    **/
    public static byte[] shortToBytes(short num){
        byte[] bytesArr = new byte[2];
        bytesArr[0] = (byte)((num >> 8) & 0xFF);
        bytesArr[1] = (byte)(num & 0xFF);
        return bytesArr;
    }
}


