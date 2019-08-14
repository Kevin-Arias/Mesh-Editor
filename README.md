# Mesh Editor

![](http://cs184.eecs.berkeley.edu/cs184_sp17_content/article_images/9_2.jpg)


I have implemented a way to build Bezier curves and surfaces using de Casteljau's algorithm, manipulate half-edge meshes, and perform loop subdivision! This mesh editor allows you to load and edit COLLADA mesh files that are now used by many major modeling packages and real time graphics engines. 


## Using the GUI

You can run the executable on any single COLLADA file (.dae, .bzc, .bez):

```
./meshedit <PATH_TO_COLLADA_FILE>
```

For example you will be able to load Bezier curves by running a command such as:

```
./meshedit ../bzc/curve1.bzc
```

And you will be able to load Bezier surfaces by running a command such as:

```
./meshedit ../bez/teapot.bez
```


![](http://cs184.eecs.berkeley.edu/cs184_sp17_content/article_images/9_3.jpg)

As you move the cursor around the screen, you'll notice that mesh elements (faces, edges, and vertices) under the cursor get highlighted. Clicking on one of these elements will display some information about the element and its associated data.

Here is the full specification on keyboard controls for the GUI:

|Key | Action|
|:---------------:|------|
|<kbd>F</kbd>     | Flip the selected edge |
|<kbd>S</kbd>     | Split the selected edge|
|<kbd>U</kbd>     | Upsample the current mesh |
|<kbd>I</kbd>     | Toggle information overlay |
|<kbd>N</kbd>     | Select the next halfedge |
|<kbd>T</kbd>     | Select the twin halfedge |
|<kbd>W</kbd>     | Switch to GLSL shaders |
|<kbd>0-9</kbd>   | Switch between GLSL shaders |
|<kbd>Q</kbd>     | Toggle using area-averaged normals |
|<kbd>R</kbd>     | Recompile shaders |
|<kbd>SPACE</kbd> | Reset camera to default position |

There are also a few mouse commands:

* **Click and drag a vertex** to change its position
* **Click and drag the background** or **right click** to rotate the camera.
* **Scroll** to adjust the camera zoom.


There will be several commands which will allow you to modify the mesh in a variety of ways.

1. Local flip (**F**) and split (**S**) operations, which modify the mesh in a small neighborhood around the currently selected mesh element. 
2. Loop subdivision (**U**), which refines and smooths the entire mesh. 

Note that each COLLADA file may contain multiple mesh objects. More generally, a COLLADA file describes a __scene graph__ (much like SVG) that is a hierarchical representation of all objects in the scene (meshes, cameras, lights, etc.), as well as their coordinate transformations. Global resampling methods will be run on whichever mesh is currently selected.

The following website goes into extreme detail about each part of the mesh editor and displays a variety of the possible reults that can be made using the mesh editor: https://kevin-arias.github.io/Mesh-Editor/
