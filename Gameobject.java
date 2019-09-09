import bagel.Image;
import java.awt.*;
//An abstract game object to enhance delegation
public abstract class Gameobject{
    protected double x;
    protected double y;
    protected Image image;
    protected Rectangle boundary;
    public abstract void move(double x, double y);
    public abstract void stop();
    public abstract double getX();
    public abstract double getY();
    public abstract void setX(double x);
    public abstract void setY(double y);
    public abstract void setImage(Image image);
}
