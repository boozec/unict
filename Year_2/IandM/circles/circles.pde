
size(500, 500);

background(255);

line(0, height/2, width, height/2);

fill(0, 0, 0, 1);
ellipseMode(CORNER);


for (int c = 50; c < width-50; c+=50) {
  ellipse(50, height/2-(c/2), c, c);
}
