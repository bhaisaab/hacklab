/*
Radar Screen Visualisation for Sharp GP2Y0A02
Maps out an area of what the GP2Y0A02 sees from a top down view.
Takes and displays 2 readings, one left to right and one right to left.
Displays an average of the 2 readings
Displays motion alert if there is a large difference between the 2 values.
*/
import processing.serial.*;     // import serial library
Serial myPort;                  // declare a serial port
float x, y;                     // variable to store x and y co-ordinates for vertices
int radius = 350;               // set the radius of objects
int w = 300;                    // set an arbitary width value
int degree = 0;                 // servo position in degrees
int value = 0;                  // value from sensor
int motion = 0;                 // value to store which way the servo is panning
int[] newValue = new int[181];  // create an array to store each new sensor value for each servo position
int[] oldValue = new int[181];  // create an array to store the previous values.
PFont myFont;                   // setup fonts in Processing
int radarDist = 0;              // set value to configure Radar distance labels
int firstRun = 0;               // value to ignore triggering motion on the first 2 servo sweeps
String[] commands = new String[10];
int cmdCounter = 0;

/* create background and serial buffer */
void setup(){
  for(int i=0; i < 10; i++)
    commands[i] = "";
  // setup the background size, colour and font.
  size(750+250, 450);
  background (0); // 0 = black
  myFont = createFont("verdana", 12);
  textFont(myFont);
  // setup the serial port and buffer
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil('\n');
}

/* draw the screen */
void draw(){
  fill(0);                              // set the following shapes to be black
  noStroke();                           // set the following shapes to have no outline
  ellipse(radius, radius, 750, 750);    // draw a circle with a width/ height = 750 with its center position (x and y) set by the radius
  rectMode(CENTER);                     // set the following rectangle to be drawn around its center
  rect(350,402,800,100);                // draw rectangle (x, y, width, height)
  if (degree >= 179) {                  // if at the far right then set motion = 1/ true we're about to go right to left
    motion = 1;                         // this changes the animation to run right to left
  }
  if (degree <= 1) {                    // if servo at 0 degrees then we're about to go left to right
    motion = 0;                         // this sets the animation to run left to right
  }
  /* setup the radar sweep */
  /*
  We use trigonmetry to create points around a circle.
  So the radius plus the cosine of the servo position converted to radians
  Since radians 0 start at 90 degrees we add 180 to make it start from the left
  Adding +1 (i) each time through the loops to move 1 degree matching the one degree of servo movement
  cos is for the x left to right value and sin calculates the y value
  since its a circle we plot our lines and vertices around the start point for everything will always be the center.
  */
  strokeWeight(7);                      // set the thickness of the lines
  if (motion == 0) {                    // if going left to right
    for (int i = 0; i <= 20; i++) {     // draw 20 lines with fading colour each 1 degree further round than the last
      stroke(0, (10*i), 0);             // set the stroke colour (Red, Green, Blue) base it on the the value of i
      line(radius, radius, radius + cos(radians(degree+(180+i)))*w, radius + sin(radians(degree+(180+i)))*w); // line(start x, start y, end x, end y)
    }
  } else {                              // if going right to left
    for (int i = 20; i >= 0; i--) {     // draw 20 lines with fading colour
      stroke(0,200-(10*i), 0);          // using standard RGB values, each between 0 and 255
      line(radius, radius, radius + cos(radians(degree+(180+i)))*w, radius + sin(radians(degree+(180+i)))*w);
    }
  }
  /* Setup the shapes made from the sensor values */
  noStroke();                           // no outline
  /* first sweep */
  fill(0,50,0);                         // set the fill colour of the shape (Red, Green, Blue)
  beginShape();                         // start drawing shape
    for (int i = 0; i < 180; i++) {     // for each degree in the array
      x = radius + cos(radians((180+i)))*((oldValue[i]*2)); // create x coordinate
      y = radius + sin(radians((180+i)))*((oldValue[i]*2)); // create y coordinate
      vertex(x, y);                     // plot vertices
    }
  endShape();                           // end shape
  /* second sweep */
  fill(0,110,0);
  beginShape();
    for (int i = 0; i < 180; i++) {
      x = radius + cos(radians((180+i)))*(newValue[i]*2);
      y = radius + sin(radians((180+i)))*(newValue[i]*2);
      vertex(x, y);
    }
  endShape();
  /* average */
  fill(0,170,0);
  beginShape();
    for (int i = 0; i < 180; i++) {
      x = radius + cos(radians((180+i)))*(((newValue[i]+oldValue[i])/2)*2); // create average
      y = radius + sin(radians((180+i)))*(((newValue[i]+oldValue[i])/2)*2);
      vertex(x, y);
    }
  endShape();
  /* if after first 2 sweeps, highlight motion with red circle*/
  if (firstRun >= 360) {
    stroke(150,0,0);
    strokeWeight(1);
    noFill();
      for (int i = 0; i < 180; i++) {
        if (oldValue[i] - newValue[i] > 35 || newValue[i] - oldValue[i] > 35) {
          x = radius + cos(radians((180+i)))*(newValue[i]*2);
          y = radius + sin(radians((180+i)))*(newValue[i]*2);
          ellipse(x, y, 10, 10);
        }
      }
  }
  /* set the radar distance rings and out put their values, 50, 100, 150 etc.. */
  for (int i = 0; i <=6; i++){
    noFill();
    strokeWeight(1);
    stroke(0, 255-(30*i), 0);
    ellipse(radius, radius, (100*i), (100*i));
    fill(0, 100, 0);
    noStroke();
    text(Integer.toString(radarDist+15), 380, (305-((radarDist+10*i)*2)), 50, 50); // change this to measure up to 150cm
    radarDist+=15;
  }
  radarDist = 0;
  /* draw the grid lines on the radar every 30 degrees and write their values 180, 210, 240 etc.. */
  for (int i = 0; i <= 6; i++) {
    strokeWeight(1);
    stroke(0, 55, 0);
    line(radius, radius, radius + cos(radians(180+(30*i)))*w, radius + sin(radians(180+(30*i)))*w);
    fill(0, 55, 0);
    noStroke();
    if (180+(30*i) >= 300) {
      text(Integer.toString((30*i)), (radius+10) + cos(radians(180+(30*i)))*(w+10), (radius+10) + sin(radians(180+(30*i)))*(w+10), 25,50);
    } else {
      text(Integer.toString((30*i)), radius + cos(radians(180+(30*i)))*w, radius + sin(radians(180+(30*i)))*w, 60,40);
    }
  }
  /* Write information text and values. */
  noStroke();
  fill(0);
  rect(350,402,800,100);
  fill(0, 100, 0);
  text("Degrees: "+Integer.toString(degree), 100, 380, 100, 50);         // use Integet.toString to convert numeric to string as text() only outputs strings
  text("Distance: "+Integer.toString(value), 100, 400, 100, 50);         // text(string, x, y, width, height)
  text("Radar screen", 540, 380, 250, 50);
  fill(0);
  rect(70,60,150,100);
  fill(0, 100, 0);
  text("Screen Key:", 100, 50, 150, 50);
  fill(0,50,0);
  rect(30,53,10,10);
  text("First sweep", 115, 70, 150, 50);
  fill(0,110,0);
  rect(30,73,10,10);
  text("Second sweep", 115, 90, 150, 50);
  fill(0,170,0);
  rect(30,93,10,10);
  text("Average", 115, 110, 150, 50);
  noFill();
  stroke(150,0,0);
  strokeWeight(1);
  ellipse(29, 113, 10, 10);
  fill(150,0,0);
  text("Motion", 115, 130, 150, 50);
  noStroke();
  fill(0);
  rect(850,50,300,800);
  fill(190,190,100);
  text("Speech Recognition Activity", 800, 30, 200, 40);
  for(int i = 0; i < 10; i++)
    text(commands[(cmdCounter+i)%10], 810, 60+40*i, 150, 30);
}

/* get values from serial port */
void serialEvent (Serial myPort) {
  String xString = myPort.readStringUntil('\n');  // read the serial port until a new line
  xString = trim(xString);
  println(xString);

  // Update SR data
  if (xString != null && xString.indexOf('^') >=0 && xString.indexOf('$') >= 0)
  {
    String srCmd = "";
    int pos = xString.indexOf('$');
    int i = xString.indexOf('^')+1;
    for(;i<pos;i++)
    {
      if(i==1)
      switch(xString.charAt(i))
      {
        case '0':
          srCmd += "Action "; break;
        case '4':
          srCmd += "Look "; break;
        case '6':
          srCmd += "Stop "; break;
        case '7':
          srCmd += "Hello "; break;
        case '3':
          srCmd += "Run "; break;
        case '1':
          srCmd += "Move "; break;
      }

      if(i==2)
      switch(xString.charAt(i))
      {
        case '0':
          srCmd += "Left "; break;
        case '1':
          srCmd += "Right "; break;
        case '4':
          srCmd += "Forward "; break;
        case '5':
          srCmd += "Backward "; break;
      }

      if(i==3)
        srCmd += "0x"+xString.charAt(i);
    }
    commands[cmdCounter] = srCmd;
    cmdCounter = (cmdCounter + 1) % 10;
  }
  // Update Radar data
  if (xString != null && xString.indexOf('^') < 0 && xString.indexOf('$') < 0 && xString.indexOf('X') >= 0)
  {  // if theres data in between the new lines
    xString = trim(xString); // get rid of any whitespace just in case
    String getX = xString.substring(1, xString.indexOf("V")); // get the value of the servo position
    String getV = xString.substring(xString.indexOf("V")+1, xString.length()); // get the value of the sensor reading
    degree = Integer.parseInt(getX); // set the values to variables
    value = Integer.parseInt(getV);
    /*
      If our values are outside either end of the sensors range then convert them to the max/min for a better display without the spikes
    */
    if (value > 150) {
     value = 150;
    }
    if (value < 20) {
      value = 20;
    }
    oldValue[degree] = newValue[degree]; // store the values in the arrays.
    newValue[degree] = value;
    /* sets a counter to allow for the first 2 sweeps of the servo */
    firstRun++;
    if (firstRun > 360) {
      firstRun = 360; // keep the value at 360
    }
  }
}
