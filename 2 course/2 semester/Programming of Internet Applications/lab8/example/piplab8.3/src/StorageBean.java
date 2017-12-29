import javax.faces.bean.ApplicationScoped;
import javax.faces.bean.ManagedBean;
import javax.persistence.EntityManager;

import java.util.ArrayList;

import java.util.HashSet;
import java.util.List;

@ManagedBean(name = "storageBean", eager = true)
@ApplicationScoped
public class StorageBean {
  private HashSet<PointDbEntity> points;
  private EntityManager entityManager = EntityManagerUtil.getEntityManager();

  public StorageBean() {
    points = new HashSet<PointDbEntity>();
  }

  public void addPoint(Double x, Double y, Double r, Boolean result) {
    PointDbEntity point = new PointDbEntity(x, y, r, result);

    try {
      entityManager.getTransaction().begin();
      entityManager.persist(point);
      entityManager.getTransaction().commit();

    } catch (Exception e) {
      points.add(point);
      Messages.sendMessage("Error - addPoints", e.toString());
      entityManager.getTransaction().rollback();
    }
  }

  public List<PointDbEntity> getPoints() {
    List<PointDbEntity> result = new ArrayList<PointDbEntity>(points);

    try {
      entityManager.getTransaction().begin();
      List<PointDbEntity> points = entityManager.createQuery("select e from PointDbEntity e").getResultList();
      entityManager.getTransaction().commit();
      return points;

    } catch (Exception e) {
      Messages.sendMessage("Error - getPoints", e.toString());
      entityManager.getTransaction().rollback();
    }

    return result;
  }
}