# SFML-Boids
Implementation of Craig Reynold's Boids in C++11 with SFML2. Features placeable boids, scatter mode, predators, zooming and multithreading (enabling more boids to be simulated).

Compiling
---------

You will need an installation of SFML compatible with SFML-2.3.2. If you run Debian or derivatives, you can install SFML by doing
```
sudo apt-get install libsfml-dev
```
After you've done that, you can compile by just doing
```
make
```
in the project directory. This will compile with gcc/g++. If you want a smaller executable (without debugging symbols), you can remove the `-g` option from the Makefile.

Running
-------

To run the simulation, do
```
./sfml-boids <boid count>
```
where boid count is the initial number of boids. If omitted, it will default to 40.

Controls
--------

* `a`: enable/disable rendering of velocity arrows/vectors of boids.
* `s`: enable/disable scatter mode. In scatter mode the boids will scatter instead of flock.
* Left click: place a new boid
* Right click: place a predator boid. Ordinary boids will flee from predators.
* Mouse wheel/scrolling: zoom in/out, effectively increasing the space the boids can move in.

Screenshots
-----------

![Screenshot 1](https://i.imgur.com/UOhFwDG.png)
![Screenshot 2](https://i.imgur.com/hpMpOJf.png)
![Screenshot 3](https://i.imgur.com/iFr4C0u.png)
![Screenshot 4](https://i.imgur.com/YVaJHSV.png)
![Screenshot 5](https://i.imgur.com/MBoYXF5.png)
