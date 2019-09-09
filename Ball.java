import bagel.*;
import java.awt.Rectangle;
public class Ball extends Gameobject{
    //Only draw the ball when it is present on screen
    private boolean present=false;
    //Assuming ball is a rectangle image in game, get its width and height
    private double width=0;
    private double height=0;
    //Get top left point of image to build rectangle
    protected double imagex;
    protected double imagey;
    //Setting up starting point of ball
    private double initialX;
    private double initialY;

    //Constructor
    public Ball(double x, double y, Image image){
        this.image=image;
        width=image.getWidth();
        height=image.getHeight();
        this.x=x;
        initialX=x;
        imagex=x-width/2;
        this.y=y;
        initialY=y;
        imagey=y-height/2;
        boundary = new Rectangle((int)imagex, (int)imagey, (int)width, (int)height);
    }
    @Override
    //Getter of x
    public double getX(){
        return this.x;
    }
    @Override
    //Getter of Y
    public double getY(){
        return this.y;
    }
    //Getter of width
    public double getWidth(){
        return this.width;
    }
    //Getter of height
    public double getHeight(){
        return this.height;
    }
    @Override
    //Setter of x
    public void setX(double x){
        this.x = x;
        imagex=x-width/2;
    }

    @Override
    //Setter of y
    public void setY(double y) {
        this.y=y;
        imagey=y-height/2;
    }

    @Override
    //Move the ball along a direction with defined velocity
    public void move(double Vx, double Vy){
        this.x+=Vx;
        this.y+=Vy;
    }
    @Override
    //Stop the ball and remove it from screen
    public void stop(){
        present=false;
        //reinitialise it to original position
        x=initialX;
        y=initialY;
    }

    @Override
    //Setter of image
    public void setImage(Image image){
        this.image=image;
        width=image.getWidth();
        height=image.getHeight();
    }
    //Getter of present
    public boolean getP(){
        return this.present;
    }
    //Setter of present
    public void setPresent(){
        this.present = !this.present;
    }
}
