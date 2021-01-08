package bgu.spl.net.Data;

import java.util.Comparator;
import java.util.Vector;

public class Student extends User {

    private Vector<Course> courses;

    public Student(String username, String password) {
        super(username, password);
        courses = new Vector<Course>(0,1);
    }

    public void takeCourse(Course course){
        courses.add(course);
        courses.sort(Comparator.comparingInt(Course::getCourseIndexInCoursesFile));
        course.addToSize();
    }

    public boolean hasCourse(int courseNum){
        for(Course c:courses){
            if(c.getCourseNum() == courseNum)
                return true;
        }
        return false;
    }

    public void sortCoursesByFileOrder(){
        courses.sort(Comparator.comparingInt(Course::getCourseIndexInCoursesFile));
    }

    public String getStringCourses(){
        StringBuilder res = new StringBuilder();
        res.append("[");
        for(Course c: courses){
            res.append(c.getCourseNum());
            res.append(",");
        }
        String out = res.toString();
        if (out.length()>1)
            out = out.substring(0,out.length()-1);
        out = out + "]";
        return out;
    }

    public Vector<Course> getCourses(){
        return this.courses;
    }

    public void removeCourse(int courseNum){
        for(Course c:courses){
            if(c.getCourseNum() == courseNum) {
                courses.remove(c);
                c.reduceSize();
                break;
            }
        }
    }

}
