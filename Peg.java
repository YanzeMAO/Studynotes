import bagel.Image;

import java.awt.*;

public class Peg extends Gameobject{
    //Assuming peg is a rectangle image in game, get its width and height
    private double width=0;
    private double height = 0;
    //Get top left point of image to build rectangle
    protected double imagex;
    protected double imagey;
    //Only draw the peg if it is not destroyed yet
    private boolean destroyed=false;
    //Constructor
    public Peg(double x, double y, Image image){
        this.image=image;
        width=image.getWidth();
        height=image.getHeight();
        this.x=x;
        imagex=x-width/2;
        this.y=y;
        imagey=y-height/2;
        boundary = new Rectangle((int)imagex, (int)imagey, (int)width, (int)height);
    }
    @Override
    //Getter of x
    public double getX(){
        return this.x;
    }
    @Override
    //Getter of y
    public double getY(){
        return this.y;
    }

    @Override
    //etter of x
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
    public void move(double Vx, double Vy){ }
    @Override
    public void stop(){}

    @Override
    //Setter of image
    public void setImage(Image image){
        this.image=image;
        width=image.getWidth();
        height=image.getHeight();
    }
    //Getter of destroyed
    public boolean getD(){
        return this.destroyed;
    }
    //Setter of destroyed
    public void setDestroyed(Ball ball){
        //get the min distance of centre when two rectangles don't collide yet
        double hDistance = (ball.getWidth()+this.width)/2;
        double vDistance = (ball.getHeight()+this.height)/2;
        //Rectangle pos = ball.boundary;
        if (ball.getX()-getX()<hDistance && ball.getX()-getX()>-hDistance
                && ball.getY()-getY()<vDistance && ball.getY()-getY()>-vDistance
                //this.boundary.intersects(pos)
        ){
            this.destroyed = true;
        }
    }
}