import com.sun.org.apache.xpath.internal.operations.Bool;

public class Point {
  private Double x;
  private Double y;

  public Point(double x, double y) {
    this.x = x;
    this.y = y;
  }

  public Double X() {
    return this.x;
  }

  public Double Y() {
    return this.y;
  }

  @Override
  public boolean equals(Object o) {
    if (o.getClass().equals(this.getClass())) {
      Point p = (Point) o;
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
