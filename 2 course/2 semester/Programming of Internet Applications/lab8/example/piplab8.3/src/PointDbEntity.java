import javax.persistence.*;
import java.io.Serializable;

@Entity
public class PointDbEntity implements Serializable {
  @Id
  @GeneratedValue(strategy = GenerationType.AUTO)
  private long id;

  public Double x;
  public Double y;
  public Double r;
  public Boolean result;

  public PointDbEntity() {
  }

  public PointDbEntity(Double x, Double y, Double r, Boolean result) {
    this.x = x;
    this.y = y;
    this.r = r;
    this.result = result;
  }

  public String getX() {
    return this.x.toString();
  }
  public String getY() {
    return this.y.toString();
  }
  public String getR() {
    return this.r.toString();
  }
  public String getResult() {
    return String.valueOf(this.result);
  }

/*  public void setX(Double x) {
    this.x = x;
  }
  public void setY(Double y) {
    this.y = y;
  }
  public void setR(Double r) {
    this.r = r;
  }
  public void setResult(Boolean result) {
    this.result = result;
  }*/

  @Override
  public boolean equals(Object o) {
    if (o.getClass().equals(this.getClass())) {
      PointDbEntity p = (PointDbEntity) o;
      if (this.r.equals(p.r) && this.x.equals(p.x) && this.y.equals(p.y)) {
        return true;
      }
    }
    return false;
  }

  @Override
  public int hashCode() {
    return (int)(this.r + this.x + this.y);
  }
}
