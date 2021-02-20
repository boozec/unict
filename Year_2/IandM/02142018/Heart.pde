
class Heart {
  private boolean status;
  private int posx;
  private int posy;
  private float speedx;
  private float speedy;
  private int Q = 1948;

  public Heart(int posx, int posy) {
    this.status = true;
    this.posx = posx;
    this.posy = posy;
  }

  public boolean is_alive() {
    return this.status;
  }

  private float f() {
    return (this.Q%21)/80;
  }

  public void die() {
    this.status = false;
  }

  public void draw() {
    smooth();
    noStroke();
    if (this.is_alive()) {
      fill(#C41212);
    } else {
      fill(#DDDDDD);
    }
    this.speedx = random(-5, 6.0);
    this.speedy = random(3, 8.0);
    if (!this.is_alive()) {
      this.speedy += 0.1+this.f();
      this.posy += this.speedy;
    } else {
      this.posy -= this.speedy;
    }

    this.posx -= this.speedx;

    pushMatrix();
    translate(-30+this.posx, -5+this.posy);

    beginShape();
    vertex(50, 15);
    bezierVertex(50, -5, 90, 5, 50, 40);
    vertex(50, 15);
    bezierVertex(50, -5, 10, 5, 50, 40);
    endShape();

    popMatrix();
  }

  public int positionx() {
    return this.posx;
  }

  public int positiony() {
    return this.posy;
  }
}
