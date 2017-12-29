import org.primefaces.event.SlideEndEvent;

import javax.faces.application.FacesMessage;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.ManagedProperty;
import javax.faces.bean.SessionScoped;
import javax.faces.context.FacesContext;
import java.util.*;

@ManagedBean(name = "pointBean", eager = true)
@SessionScoped
public class PointBean {
  private Double r;
  private Double x;
  private Double y;

  private Dictionary<Point, Boolean> points;

  private String log = "";

  @ManagedProperty(value = "#{storageBean}")
  private StorageBean store;

  public PointBean() {
    this.r = 200.0;
    this.x = 0.0;
    this.y = 0.0;
    this.points = new Hashtable<Point, Boolean>();
  }

  public String getLog() {
    return log;
  }

  public ArrayList<TemporaryPoint> getPoints() {
    ArrayList<TemporaryPoint> res = new ArrayList<TemporaryPoint>();

    Enumeration<Point> keys = points.keys();
    while (keys.hasMoreElements()) {
      Point p = keys.nextElement();
      res.add(new TemporaryPoint(p.X(), p.Y(), points.get(p)));
    }
    return res;
  }

  public StorageBean getStore() {
    return store;
  }
  public void setStore(StorageBean store) {
    this.store = store;
  }

  public void setR(String r) {
    this.r = Double.parseDouble(r);
    this.log = log + " SET R=" + this.r/100;
    recheck();
  }

  public String getR() {
    return String.valueOf(this.r);
  }
  public String getRScaled() {
    return String.valueOf(this.r / 100);
  }

  public void setX(String x) {
    this.x = Double.parseDouble(x);
    this.log = log + " SET X=" + x;
  }
  public String getX() {
    return String.valueOf(this.x);
  }

  public void setY(String y) {
    this.y = Double.parseDouble(y);
    this.log = log + " SET Y=" + y;
  }
  public String getY() {
    return String.valueOf(this.y);
  }

  private void recheck() {
    Enumeration<Point> points = this.points.keys();
    while (points.hasMoreElements()) {
      Point p = points.nextElement();
      this.points.put(p, checkPoint(p.X(), p.Y(), this.r / 100));
    }
  }

  public String check() {
    Boolean result = checkPoint(x, y, r / 100);
    // Save the point and result to
    // session scoped storage
    points.put(new Point(x, y), result);

    // Save information about check to LOG
    // This should be removed at production
    this.log = log + " CHECK-RESULT=";
    this.log = log + result.toString();

    // Save full info about new check.
    // This should later put bean in database
    store.addPoint(x, y, r / 100, result);

    return String.valueOf(result);
  }

  private Boolean checkPoint(Double x, Double y, Double r) {
    if (x < 0 && y <= 0) {
      return y > -r && x > -r;
    } else if (x < 0 && y >= 0) {
      return y < (r + 2*x);
    } else if (x > 0 && y >= 0) {
      return y <= Math.pow(Math.pow(r/2, 2) - Math.pow(x, 2), 0.5);
    } else {
      return false;
    }
  }

  public void onSlideEnd(SlideEndEvent event) {
    setR(String.valueOf(event.getValue()));
  }
}
