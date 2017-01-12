#include "png.h"
/// Include prototypes for functions srand and rand.
#include <cstdlib>
/// For seed value of random function using time().
#include<ctime>

using namespace std;

///Class to represent PNG image actions.
class PNG
{
public:
    unsigned long width, height;
    char *argv;

    void  dPNG(char *arg) const
    {
        picopng(arg);
        glPushMatrix ();
    };

    PNG (char *arg)
    {
        argv = arg;
        picopng(argv);
        glPushMatrix ();
    };

private:
    unsigned long Width()
    {
        return width;
    }
    unsigned long Height()
    {
        return height;
    }
} ;

PNG png("");

///Game class for defining game property.
class Game
{
private:
    int started;
    int level;
    int heroOnePositionAngle;
    int heroTwoPositionAngle;
    int help;
    int about;
    int winner;
    float theta;
    int obstacleload;


public:

    int obstacleLoaded()
    {

        return obstacleload;

    }
    int obstacleLoaded( int n)
    {

        obstacleload=n;
    }

    /// Function to check if the game has started.
    int ifStarted()
    {
        return started; // return 0 if the screen is home
    }
    /// Function to start the game.
    void start()
    {
        theta=0;
        over(0);
        started = 1;//sets the value to 1 if game starts
        heroOnePositionAngle=1;
        heroTwoPositionAngle=0;
        obstacleLoaded(0);
    }
    /// Function to end the game.
    void over()
    {
        started = 0; //sets the value to 0 as if game is going to start
        help=0;
        about=0;
        theta=0;

    }
    /// Function to end the game with a winner.
    void over(int n)
    {
        winner = n;
        obstacleLoaded(0);
        over();
    }
    /// Function to return the current level.
    int Level()
    {
        return level;
    }
    /// Function to set the level.
    void setLevel(int m)
    {
        level=m;
    }
    ///Function to flip the player from the current position.
    void flip(int n)
    {
        if (n==1) heroOnePositionAngle+=1;
        if (n==2) heroTwoPositionAngle+=1;

    }
    /// Function to get current position of first player.
    float heroOnePosition()
    {
        heroOnePositionAngle%=2;
        return heroOnePositionAngle;
    }
    /// Function to get current position of second player.
    float heroTwoPosition()
    {
        heroTwoPositionAngle%=2;
        return heroTwoPositionAngle;
    }
/// Function to see if user is in help window.
    int Help()
    {
        return help;

    }
/// Function to show help.
    int Help(int n)
    {
        help=n;
    }
/// Function to see if user is in about window.
    int About()
    {
        return about;

    }
    /// Function to show about information.
    int About(int n)
    {
        about=n;
    }
    /// Function to show winner.
    int Winner ()
    {

        return winner;
    }
    /// Function to get the value of angle which is always increasing with time.
    float Theta()
    {
        return theta;
    }
    /// Function to set the value of angle.
    float Theta(float n)
    {
        theta=n;
//        if (theta==360) theta=0;
    }
    /// Constructor for Game class to initialize values.
    Game()
    {
        started = 0;
        level =0;
        winner=0;
        theta=0.0f;
    }

    void drawQuad(float a, float b, float c, float d)
    {
        glBegin(GL_QUADS);
        glTexCoord2d(-a, c);
        glVertex2f(-a, c);
        glTexCoord2d(-b, c);
        glVertex2f(-b, c);
        glTexCoord2d (-b, d);
        glVertex2f (-b, d);
        glTexCoord2d (-a, d);
        glVertex2f (-a, d);
        glEnd();
        glPopMatrix ();
    }
    float drawObstacle(float a, float b, float c, float d, int position, float location, Game & thisGame, char * argv, int id)
    // flip position and x -axis location
    {
//        if (location > 4) thisGame.Theta(0);
        png.dPNG(argv);
        drawQuad(location+a,  location+b,  c,  d);

        // difference calculation
        if ((location+b>=0.85)&&(position==0)&& ((location)<=1.8) )
        {
            Sleep(500);
            cout<< "Crashed"<<endl;
            thisGame.over(id);
            return 0;

        }
        return 1;
    }
    int rand(int upper, int lower)
    {
        srand( time( 0 ) );
        int val= ( upper +  std:: rand() % lower );
        cout<< val<< endl;
        return val;
    }

} ;

/// Initializing a new Game object.
Game game; //Game Object Initialization -- global for all funcs ---- try to include in main

/// Obstacle class for defining property of obstacles.
class Obstacle
{

private:
    int speed;
    int id;
    int exists;
    float Location;

public:
    ///Resets the position of obstacles.
    void reset()
    {
        Location= 0;
    }
    /// Constructor to initialize obstacle class.
    Obstacle(int ID, float Speed)
    {
        id=ID;
        speed= Speed;
        Location=0;
        load();
    }

    /// Function to load refreshed obstacles.
    void load()
    {
        if (Location/speed>3) Location=0;
        cout<< "Last ma aakoo"<< endl;
        cout<<Location/speed<< " "<< Location<< endl;
        switch (id)
        {
        case 1:
        {
            if (game.drawObstacle(-0.9,-0.85, 0.65, 0.5,game.heroOnePosition(), Location/speed, game, "h11.png", 2)) Location+=5;
            else
            {
                Location=0;
                cout<< "Collided with 1"<<endl;
            };

            break;
        }
        case 2:
        {
            if(game.drawObstacle(-0.9,-0.85, 0.3, 0.45,1-game.heroOnePosition(), Location/speed, game, "h22.png", 2)) Location+=5;
            else Location=0;
            break;
        }
        case 3:
        {
            if(game.drawObstacle(-0.9,-0.85, -0.3, -0.45,1-game.heroTwoPosition(), Location/speed, game, "h33.png", 1)) Location+=5;
            else Location=0;
            break;
        }
        case 4:
        {
            if ( game.drawObstacle(-0.9,-0.85, -0.65, -0.5,game.heroTwoPosition(), Location/speed, game, "h44.png", 1)) Location+=5;
            else Location=0;
            break;
        }
        }
    }



};
