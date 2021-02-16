int x = 0;
int y = 500/2;

void setup() {
  size(500, 500);
  frameRate(1000);

  line(x, y, x+10, y);
  x = x+10;
}

void draw() {
  fill(255, 100);
  x = x+1;
  int ys = y+(int) random(-3, 3);
  line(x, y, x+1, ys);
  y = ys;

  if (x >= width) {
    noStroke();
    rect(0, 0, width, height);
    fill(255, 0, 0);
    rectMode(RADIUS);

    rect(x-10, y-2, 10, 2);
    x = 0;
    stroke(0);
  }
}
