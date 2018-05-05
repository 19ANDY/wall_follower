# wall_follower
Following Walls
In order to follow walls, you need at least two sensors (2 bits of information) to handle the four potential situations the robot could be in. One sensor has to be in the front, and the second could be on the left or right of the robot. The more sensors you use, the more information you have, so you can make better judgements about what is going on. For this example, I just used two. The robot cannot find the wall, so you have to place the robot next to the wall. If you placed it in the middle of the room, it would just drive in circles.

Truth Table
Front   Sensor	Right Sensor	Situation	Action
Off	    Off   	Robot is driving away from wall.	Come back to wall, turn right.
On	    Off   	Robot is away from wall but headed towards a wall or obstacle.	Turn hard left to get back parallel with the wall.
Off 	  On	    Robot is following the wall.	Drive forward.
On	    On	    The robot is at a corner.	Turn hard left.
In order to work, I had to add code to turn hard left. Hard left just means I only turn on the right wheel so the robot basically turns in place rather than continue to move forward while turning. I couldn't just turn slowly like the line follower because you have no idea how close the robot is to the wall. This is a limitation of the sensor I chose, because the sensor reflects differently based on the surface. Additionally, the logic is set up to only be binary because there is no way to tell the distance based on the sensor. If you knew distance, you could add additional logic to vary the speed based on the distance to make the robot travel around the room faster. I actually couldn't get the sensor to reflect at all off a black surface, so in the video you'll see I had to put a white surface in front of the dishwasher.
