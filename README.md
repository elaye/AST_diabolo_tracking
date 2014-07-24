Diabolo tracking for AST interactrive diabolo project
=====================================================

Installation
------------
This programs uses a Kinect so you need to install all the drivers necessary to its usage on a computer.
Moreover you need to install OpenNI and the boost library.
It also depends on the following openFrameworks addons:

- ofxOpenNI
- ofxOpenCv
- ofxOsc

`cd your_OpenFrameworks_directory/apps/myApps`  
`git clone https://github.com/elaye/diabolo_tracking`  
`cd diabolo_tracking`
`make`
`make run`

Usage
-----
The program uses a Kinect to track the positions of the diabolo and the arms of the juggler.
The diabolo is tracked by a simple color tracking and the arms are tracked using OpenNI skeleton's recognition.
The positions are sent via OSC to two programs: one that creates visual effects (available at [https://github.com/elaye/AST_diabolo_particles](https://github.com/elaye/AST_diabolo_particles)) and the other that generates sounds according to tricks realized by the juggler (SuperCollider patch available at [???](???)).
You can record diabolo tricks and trigger specific events when the program recognizes.
Sequence of tricks can be designed thanks to a timeline provided by the GUI.

The tricks recognition is done by Dynamic Time Warping thanks to the [GRT](http://www.nickgillian.com/software/grt) library.

