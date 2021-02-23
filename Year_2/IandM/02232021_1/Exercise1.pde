Auto a = new Auto();
AutoElettrica ea = new AutoElettrica(a.velx());

void setup() {
  size(512, 512);
}

void draw() {
  background(255);
  a.draw();
  ea.draw();
}

void keyPressed() {
  if(key == 'R' || key == 'r') {
    a = new Auto();
    ea = new AutoElettrica(a.velx());
  }
}
