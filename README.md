# The Maze
### Creating a 3D maze with raycasting


### Environment
This game uses Simple DirectMedia Layer (SDL2) and Raycasting
- [SDL2](https://www.libsdl.org/download-2.0.php) and [SDL2_image](https://www.libsdl.org/projects/SDL_image/) are required to compile and use this program
-----

### Installation
- Clone this repository: `git clone "https://github.com/amanabay/The_Maze"`
- Access The Maze directory: `cd Maze-Game`
- Compile the files with: `make `
- Run the maze: `./maze` or `./maze maps/<map_name>`
- Disable textures: `./maze flat` or `./maze maps/<map_name> flat`

-----

### Usage
This Maze uses raycasting to draw the walls, utilizes [LodeV's](http://lodev.org/cgtutor/raycasting.html) method of using vectors to calculate ray length. 

#### Controls
- `W` or `↑` : move forward
- `S` or `↓` : move backward
- `A` or `←` : rotate camera left
- `D` or `→` : rotate camera right
- `Q` : left
- `E` : right
- `ESC` : quit


### To-Do
- Enemies 
- Rain
