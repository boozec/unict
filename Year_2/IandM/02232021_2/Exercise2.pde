void setup() {
  size(768, 256);
  PImage img = loadImage("monkey.jpg");
  img.resize(256, 256);
  img.filter(GRAY);

  image(img, 0, 0);

  PImage revimg = rev(img);
  image(revimg, 256, 0);
  
  int random_number = (int)random(5, 15); // [5, 15)
  image(mass(revimg, random_number), 512, 0);
}

PImage rev(PImage I) {
  PImage out = I.copy();
  int t;

  for (int row = 0; row < out.width; ++row) {
    for (int i = 0, j = out.width-1; i < out.width/2; ++i, --j) {
      t = out.get(i, row);
      out.set(i, row, out.get(j, row));
      out.set(j, row, t);
    }
  }

  // yellow pixels
  for (int i = 0; i < out.width; ++i)
    out.set(i, i, color(#EFFC38));


  return out;
}

PImage mass(PImage I, int n) {
  PImage out = createImage(I.width, I.height, RGB);
  
  // image and array aux
  PImage tmp;
  float[] tarr = new float[n*n];
  
  int off = n/2;
  
  for(int i = 0; i < out.width; ++i) {
    for(int j = 0; j < out.height; ++j) {
      tmp = I.get(i-off, j-off, n, n);
      
      tmp.loadPixels();
      for(int k = 0; k < tmp.pixels.length; ++k) {
        tarr[k] = red(tmp.pixels[k]);
      }
        
      out.set(i, j, color(max(tarr)));
    }
  }
  
  return out;
}
