void setup() {
  size(500, 500);
}

int th = 0;

void draw() {
  background(#ffffff);
  translate(width/2, height/2);
  rotate(radians(th++));
  stroke(0);
  noFill();
  strokeWeight(20);
  ellipseMode(RADIUS);
  ellipse(0, 0, 200, 200);
  
  noStroke();
  fill(0);
  triangle(0, -200, 180, 100, -180, 100);
}
