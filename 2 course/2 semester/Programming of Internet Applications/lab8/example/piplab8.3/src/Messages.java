import javax.faces.application.FacesMessage;
import javax.faces.context.FacesContext;

public class Messages {
  public static void sendMessage(String msg, String detail) {
    FacesMessage message = new FacesMessage(msg, detail);
    //FacesContext.getCurrentInstance().addMessage("growl", message);
  }
}
