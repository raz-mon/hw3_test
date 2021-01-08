package bgu.spl.net.Data;

import java.util.Arrays;

public class Course {
    private final int courseNum;
    private final String courseName;
    private final int[] courseKdam;
    private final int courseMaxSize;
    private int currentSize;
    private int indexInCoursesFile;

    public Course(int courseNum, String courseName, int[] courseKdam, int courseMaxSize, int ind){
        this.courseNum = courseNum;
        this.courseName = courseName;
        this.courseKdam = courseKdam;
        this.courseMaxSize = courseMaxSize;
        this.currentSize = 0;
        this.indexInCoursesFile = ind;
    }

    public int getCourseNum(){
        return this.courseNum;
    }

    public String getCourseName(){
        return this.courseName;
    }

    public int[] getCourseKdam(){
        return this.courseKdam;
    }

    public int getCourseMaxSize(){
        return this.courseMaxSize;
    }

    public int getCurrentSize(){
        return this.currentSize;
    }

    public int getCourseIndexInCoursesFile(){
        return this.indexInCoursesFile;
    }

    /**
     * add one student to this course (if it can)
     * This method is synchronize due to the possibility that another
     * thread will check the size while increasing.
     */
    public synchronized void addToSize(){
        if(currentSize < courseMaxSize)
            currentSize++;
        else
            throw new IllegalArgumentException("Course already reached max size capacity");
    }

    /**
     * lower course student's size by 1
     */
    public synchronized void reduceSize(){
        if(currentSize > 0)
            currentSize--;
        else
            throw new IllegalArgumentException("Course size capacity can not be negative");
    }

    /**
     * check if there is a available spot in this course
     * @return true if a student can register to this course (else false)
     * This method is synchronize due to the possibility that another
     * thread will increase the size while checking the condition of return value.
     */
    public synchronized boolean isAvailabale(){
        return courseMaxSize > currentSize;
    }

    public String toString(){
        return "course number: " + courseNum + "\n" + "courseName: " + courseName + "\n" + "courseKdam: " + Arrays.toString(courseKdam) + "\n" +
                "courseMaxSize: " + courseMaxSize + "\n" + "currentSize: " + currentSize;
    }
}
