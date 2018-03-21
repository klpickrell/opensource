import java.util.*;

class Hint
{
    public Hint( String text ) {
	_text = text;
    }

    public String toString() { return _text; }

    private String _text;
}

class Problem
{
    public Problem( String text, Hint hint ) {
	_text = text;
	_hint = hint;

	System.out.println( "Created Problem: " + _text + ", " + _hint );
    }

    public String getText() { return _text; }
    public Hint getHint() { return _hint; }

    // private members
    private String _text;
    private Hint   _hint;
}

class Lesson
{
    // constructors
    public Lesson( String title ) {
	_problems = new ArrayList();
	_title = title;
	System.out.println( "Created Lesson: " + _title );
    }

    // public interface
    public String toString() { return _title; }
    public String title() { return _title; }

    public void add( Problem p ) {
	_problems.add( p );
    }

    public Problem get( int idx ) {
	return (Problem)_problems.get( idx );
    }

    public int size() {
	return _problems.size();
    }

    // private members
    private String _title;
    private List _problems;
}

class Topic
{
    // constructors
    public Topic() {
	_lessons = new ArrayList();
    }

    // public interface

    public void add( Lesson p ) {
	_lessons.add( p );
    }

    public Lesson get( int idx ) {
	return (Lesson)_lessons.get( idx );
    }

    public int size() {
	return _lessons.size();
    }


    private List _lessons;
}





/**
 * Main program
 * @author Kris Pickrell
 */
public class Main
{
    /**
     * Default constructor
     */
    public Main(){}
    /**
     * Program entry point
     */
    public static void main( String[] argv )
    {

    }
}
