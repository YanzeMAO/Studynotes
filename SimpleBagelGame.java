import bagel.*;


/**
 * Project 1
 *
 * @author Yanze Mao
 */
public class SimpleBagelGame extends AbstractGame {
    private Image pegimage;
    private Image ballimage;
    private double verticalspeed=0f;
    private double horizontalspeed=0f;
    private double regularizedspeed=0f;
    private double fallspeed = 0f;
    private static final double STARTX=512;
    private static final double STARTY=32;
    private static final double velocity = 10f;
    private static final double acceleration=0.15f;
    private static final int numberofpeg = 50;

    Peg[] pegs= new Peg[numberofpeg];
    Ball ball;
    public SimpleBagelGame() {
        pegimage = new Image("res/peg.png");
        ballimage = new Image("res/ball.png");
        ball= new Ball(STARTX, STARTY, ballimage);
        //Create 50 pegs with random position in range
        for (int i = 0; i<numberofpeg ; i++){
            double randomX = Math.random() * 1024;
            double randomY = Math.random() * 668+100;
            pegs[i]=new Peg(randomX,randomY, pegimage);
        }
    }
    /**
     * The entry point for the program.
     */
    public static void main(String[] args) {
        SimpleBagelGame game = new SimpleBagelGame();
        game.run();
    }


    /**
     * Performs a state update. This simple example shows an image that can be controlled with the arrow keys, and
     * allows the game to exit when the escape key is pressed.
     */
    @Override
    public void update(Input input) {
        //Draw the pegs
        for (int i = 0; i<numberofpeg ; i++){
            Peg p = pegs[i];
            //Destroy the peg if it collide with the ball
            p.setDestroyed(ball);
            //Only draw the ball that are not destroyed yet
            if (!p.getD()){
                pegimage.draw(p.getX(), p.getY());
            }
        }
        //Create the ball and move the ball towards where mouse is clicked
        if (input.isDown(MouseButtons.LEFT)&&!ball.getP()){
            //Add ball into game
            ball.setPresent();
            //Initialise its speed
            horizontalspeed=(input.getMouseX()-ball.getX());
            verticalspeed=(input.getMouseY()-ball.getY());
            //Regularise its speed
            regularizedspeed=velocity/Math.sqrt(horizontalspeed*horizontalspeed+(verticalspeed)*(verticalspeed));
            horizontalspeed*=regularizedspeed;
            verticalspeed*=regularizedspeed;
        }
        //move the ball from its last state once it is created
        if (ball.getP()){
            //Remove the ball after it falls out of the screen
            if (ball.getY()>=768+ball.getHeight()/2){
                fallspeed=0;
                verticalspeed=0;
                horizontalspeed=0;
                ball.stop();
            }
            //Bounce back when it hit right side or left side of screen
            if (ball.getX()>=1024-ball.getWidth()/2 ||ball.getX()<=ball.getWidth()/2){
                horizontalspeed*=-1;
            }
            //Increment fall speed
            fallspeed+=acceleration;
            //move the ball
            ball.move(horizontalspeed, verticalspeed+fallspeed);
            ballimage.draw(ball.getX(),ball.getY());
        }

    }
}
