# Pong-Remake-Ue5
 A rendition of Pong against an AI with randomly spawning obstacles programming in Unreal Engine 5 using C++ and Blueprints

ABoundary.cpp extends Actor
 A class to represent the Boundary of the screen in which the PongBall bounces off of, or is sent into the goal and is scored.

Brick.cpp extends Actor
 The class which represents the obstacles which spawn randomly throughout playtime. They cause the PongBall to change directions and are destroyed when hit

BrickSpawner.cpp extends Actor
 A class which takes up the area which is valid for Bricks to be spawned it. This class also handles the spawning of the Bricks.

Pong_GM.cpp extends GameModeBase
 This is the GameMode for the game. It is used to set PongPlayer as the default pawn class

PongAI.cpp extends Actor
 The class representing the player's opponent. It attempts to prevent the PongBall from passing into its goal and scoring.

PongBall.cpp extends Actor
 This is the class representing the ball in the game. When it collides with a goal it respawns in the center of the arena to continue play

PongPlayer.cpp extends Pawn
 This is the player class which can be moved up and down with the arrow keys

ScoreBoard_UI.cpp extends UserWidget
 This is the class which makes up the UI, and displays each player's scores at the top of the screen
