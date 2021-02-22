void setup() {
  size(500, 500);
  rectMode(CENTER);
}
int[] th = {0, 0, 0};
int[] y = {0, 0, 0};
int[] x = {0, 0, 0};
void draw() {
  background(255);
  
  fill(#1ADFE8);
  
  line(10, height-100, width-10, height-100);
  
  pushMatrix();
  if (th[0] >= 90) th[0] = y[0] = x[0] = 0;
  translate(width/2+(x[0]--), height-150);
  rotate(radians(th[0]++));
  rect(0, y[0]--, 100, 100);
  popMatrix();

  pushMatrix();
  if (th[1] <= -90) th[1] = y[1] = x[1] = 0;
  translate(width/2+(x[1]++), height-250);
  rotate(radians(th[1]--));
  rect(0, y[1]--, 100, 100);
  popMatrix();

  pushMatrix();
  if (th[2] >= 90) th[2] = y[2] = x[2] = 0;
  translate(width/2+(x[2]--), height-350);
  rotate(radians(th[2]++));
  rect(0, y[2]--, 100, 100);
  popMatrix();
}
