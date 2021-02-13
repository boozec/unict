size(500, 500);
background(255);
noStroke();
fill(0);

int k = 0;
for(int y = 0; y < width; y+=50) {
  k = (int)lerp(0, 255, y);
  for(int x = 0; x < height; x+=50) {
    fill(k);
    rect(x, y, 50, 50);
    k+=5;
  }
}
