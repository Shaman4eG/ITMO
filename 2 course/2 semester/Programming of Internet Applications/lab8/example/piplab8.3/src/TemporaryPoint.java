public class TemporaryPoint {
  public Double x;
  public Double y;
  public Boolean fits;

  public TemporaryPoint(double x, double y, Boolean fits) {
    this.x = x;
    this.y = y;
    this.fits = fits;
  }

  public String getX() {
    return this.x.toString();
  }
  public String getY() {
    return this.y.toString();
  }
  public String getFits () {
    return String.valueOf(this.fits);
  }

  @Override
  public boolean equals(Object o) {
    if (o.getClass().equals(this.getClass())) {
      TemporaryPoint p = (TemporaryPoint) o;
      if (this.x.equals(p.x) && this.y.equals(p.y)) {
        return true;
      }
    }
    return false;
  }

  @Override
  public int hashCode() {
    return (int)(this.x + this.y);
  }
}
