import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;
import javax.persistence.PersistenceUnit;

public class EntityManagerUtil {
  private static final EntityManagerFactory entityManagerFactory;

  static {
    try {
      entityManagerFactory = Persistence.createEntityManagerFactory("PointDb");
    } catch (Throwable ex) {
      System.err.println("Initial Fail lol me Hueeee." + ex);
      throw new ExceptionInInitializerError(ex);
    }
  }

  public static EntityManager getEntityManager() {
    return entityManagerFactory.createEntityManager();
  }
}
