int x = 0;
int y = 250;
int j = 0;
int ys = 250;
int xs = 0;
int st = 0;
void setup() {
  size(500, 500);
  background(#015B6C);
}

void draw() {
  if (x >= width) {
    background(#015B6C);
    x = 0;
  }

  stroke(#1AFF3E);
  strokeWeight(3);
  if (j < 50) {
    line(x, y, x++, y);
  } else {
    if (st == 0) {
      ys = ys-(int) random(10, 70);
      line(x, y, x+=5, ys);
      st++;
      y = ys;
    } else if (st == 1) {
      ys = y+(int) random(75, 130);
      line(x, y, x+=5, ys);
      st++;
      y = ys;
    } else {
      line(x, y, x+=3, height/2);
      y = height/2;
      st = 0;
      j = 0;
      ys = y;
    }
  }

  ++j;
}
