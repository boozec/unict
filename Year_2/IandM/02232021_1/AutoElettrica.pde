class AutoElettrica extends Auto {
  private int MYCOLOR = (int)random(0, 255);
  private boolean triangle_turn = true;

  AutoElettrica(float velx) {
    super.velx = velx/2;
    super.posx = -60;
    super.posy = 512*2/3;
  }

  void draw() {
    rectMode(CORNER);
    noStroke();
    fill(this.MYCOLOR);
    rect(super.posx, super.posy, 60, 30);
    super.posx += super.velx;

    fill(#EFFC38); // triangle color, this is yellow

    if (this.triangle_turn) {
      triangle(super.posx+30, super.posy, super.posx+60, super.posy+30, super.posx, super.posy+30);
    }
    
    if (super.posx >= 512) {
      super.posx = -60;
      this.triangle_turn = !this.triangle_turn;
    }
  }
}
