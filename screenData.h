///Initializing different obstacle objects.
Obstacle one(1,450);
Obstacle two(2,400);
Obstacle three(3,470);
Obstacle four(4,390);

///Function to load the main menu. This is called at the beginning of the program or when user ends a game.
float startScreen(HDC hDC, float theta)
{
    displayText(-0.2,0.4,1,1,0,"RIVAL RUN");
    displayText(-0.2,-0.0,0,1,0,"press Space to start.");
    displayText(-0.2,-0.2,0,1,0,"press A for About.");
    displayText(-0.2,-0.4,0,1,0,"press H for Help.");
    displayText(-0.2,-0.6,0,1,0,"press Q to Quit.");
}

///Function to load the main game area. It includes loading players.
float gameGround(HDC hDC)
{
    png.dPNG("game.png"); // Loads the PNG data to a 2D texture.
//   glRotatef ( game.heroOnePosition(), -0.875f, -0.475f, 0.0f);
    if (game.heroOnePosition())   glTranslatef (-0.0f, -0.25f, 0.0f);
//    glColor3f(1.0, 1.0, 1.0); /* green */ //
    game.drawQuad(0.9,0.85,0.7,0.475);

    png.dPNG("h22.png");
//    glRotatef ( game.heroTwoPosition(), -0.875f, -0.475f, 0.0f);
    if (game.heroTwoPosition()) glTranslatef (-0.0f, 0.25f, 0.0f);
    game.drawQuad(0.9, 0.85, -0.7, -0.475);

    // bar above
    png.dPNG("b11.png");
    game.drawQuad(-1, 1, 0.45, 0.5);

    // bar below
    png.dPNG("b22.png");
    game.drawQuad(-1, 1, -0.45, -0.5);


    if (!game.obstacleLoaded())
    {
        one.reset();
        two.reset();
        three.reset();
        four.reset();

        game.obstacleLoaded(1);
    }

    one.load();
    two.load();
    three.load();
    four.load();

    displayText(-0.1,-0.9,1,1,0,"Press M to Quit and return to Main Menu.");

}
///Display to load the game result after a game ends.
void summary ()
{

    displayText(-0.8,0.8,0,1,1,"Rival Run :: Game Summary");
    if (game.Winner()==1)
    {
        displayText(-0.6,0.3,0,1,0,"Player 1 wins!!");
    };
    if (game.Winner()==2)
    {
        displayText(-0.6,0.3,0,1,0,"Player 2 wins!!");
    };
    displayText(-0.1,-0.9,1,1,0,"Press M for Main Menu.");





}
///Function to display help information.
void help()
{

    displayText(-0.8,0.8,0,1,1,"Rival Run :: Help");
    displayText(-0.6,0.5,0,1,0,"Press Space and Zero from keypad");
    displayText(-0.6,0.3,0,1,0,"to switch the player position.");
    displayText(-0.1,-0.9,1,1,0,"Press M for Main Menu.");
}
///Function to display about information.
void about ()
{
    picopng("sal.png");
    game.drawQuad(1,-1,-1,1);

    displayText(-0.8,0.8,0,1,1,"Rival Run :: About");
    displayText(-0.6,0.5,0,1,0,"CPP Project of ");
    displayText(-0.6,0.3,0,1,0,"072 BCT 531/ 544 ");
    displayText(-0.6,0.1,0,1,0,"Central Campus, Pulchowk");
    displayText(-0.6,-0.1,0,1,0,"Institute of Engineering, Tribhuwan University ");
    displayText(-0.6,-0.33,0,1,0,"CC BY 4.0");
    displayText(-0.6,-0.6,0,1,0,"072BCT544@ioe.edu.np");
    displayText(-0.1,-0.9,1,1,0,"Press M for Main Menu.");


}
