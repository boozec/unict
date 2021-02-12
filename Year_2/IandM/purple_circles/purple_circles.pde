size(1000, 400);
background(255);
fill(255);

stroke(255, 0, 255);
strokeWeight(7);

ellipseMode(CORNER);

for (int i = 70, s = 100; i < width-50 && s > 0; i+=150, s-=15) {
  ellipse(i, height/2-(s/2), s, s);
}
