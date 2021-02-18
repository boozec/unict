float n3 = 1/9.0;
float[][] nbox3 = {{n3, n3, n3}, 
  {n3, n3, n3}, 
  {n3, n3, n3}};

float n5 = 1.0/25;
float[][] nbox5 = {{n5, n5, n5, n5, n5}, 
  {n5, n5, n5, n5, n5}, 
  {n5, n5, n5, n5, n5}, 
  {n5, n5, n5, n5, n5}, 
  {n5, n5, n5, n5, n5}};

float[][] lapl = {{-1, 0, -1}, 
  {0, 4, 0}, 
  {-1, 0, -1}};

float[][] sobx = {{-1, -2, -1}, 
  {0, 0, 0}, 
  {1, 2, 1}};

float[][] sharp = {{-1, 0, -1}, 
  {0, 5, 0}, 
  {-1, 0, -1}};

void setup() {
  size(768, 512);
  PImage img = loadImage("lena.png");
  img.resize(256, 256);
  img.filter(GRAY);

  image(img, 0, 0);
  image(convert(convolution(img, nbox3)), 256, 0);
  image(convert(convolution(img, nbox5)), 512, 0);
  image(convert(convolution(img, lapl)), 0, 256);
  image(convert(convolution(img, sobx)), 256, 256);
  image(convert(convolution(img, sharp)), 512, 256);
}


PImage convert(float[][] mat) {
  PImage out = createImage(mat[0].length, mat.length, RGB);
  float res = 0;

  for (int x = 0; x < out.width; ++x) {
    for (int y = 0; y < out.height; ++y) {
      res = constrain(abs(mat[y][x]), 0, 255);
      out.set(x, y, color(res));
    }
  }

  return out;
}

float[][] convolution(PImage I, float[][] kernel) {
  float[][] out = new float[I.height][I.width];
  int n = kernel[0].length;
  int m = kernel.length;
  PImage tmp;

  for (int x = 0; x < I.width; ++x) {
    for (int y = 0; y < I.height; ++y) {
      tmp = I.get(x-n/2, y-m/2, n, m);
      float res = 0;
      for (int p = 0; p < n; ++p)
        for (int q = 0; q < m; ++q)
          res+=red(tmp.get(p, q)) * kernel[q][p];

      out[y][x] = res;
    }
  }

  return out;
}
