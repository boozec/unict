background(0);
size(500, 500);

noStroke();
int k = 50;

for(int i = k; i < width-(k*4); i+=20) {
  fill(255, 255, 255, 100);
  rect(i, i, k*3, k*3);
}
