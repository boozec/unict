ArrayList<Heart> hearts = new ArrayList<Heart>();
void setup() {
  size(512, 512);
  background(#011146);
  frameRate(60);
}
void draw() {
  fill(#011146, 100);
  rect(0, 0, width, height);

  if ((int)random(1, 101) <= 5) {
    Heart tmp = new Heart((int)random(0, width), height/2+10);
    hearts.add(tmp);
  }

  for (Heart h : hearts) {
    h.draw();
  }
}

void mouseClicked() {
  for (Heart h : hearts) {  
    if (dist(h.positionx(), h.positiony(), mouseX, mouseY) < 30) {
      h.die();
    }
  }
}
