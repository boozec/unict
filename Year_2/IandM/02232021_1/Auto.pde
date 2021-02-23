class Auto {
  private int posx;
  private int posy;
  
  private float velx = random(2, 10); // [2, 10);
  
  private int MYCOLOR = #007CA0; // this is blue
  
  public Auto() {
    this.posx = -60;
    this.posy = 512/3;
  }
  
  public float velx() {
    return this.velx;
  }
  
  void draw() {
    rectMode(CORNER);
    noStroke();
    fill(this.MYCOLOR);
    rect(posx, posy, 60, 30);
    posx += velx;
    
    if(posx >= 512) {
      posx = -60;
    }
  }
}
