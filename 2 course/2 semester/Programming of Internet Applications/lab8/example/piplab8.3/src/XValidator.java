import javax.faces.application.FacesMessage;
import javax.faces.component.UIComponent;
import javax.faces.context.FacesContext;
import javax.faces.validator.FacesValidator;
import javax.faces.validator.Validator;
import javax.faces.validator.ValidatorException;

@FacesValidator("xValidator")
public class XValidator implements Validator{
  private void throwError() {
    FacesMessage msg = new FacesMessage("X didn't passed validation");
    msg.setSeverity(FacesMessage.SEVERITY_ERROR);
    throw new ValidatorException(msg);
  }

  @Override
  public void validate(FacesContext ctx, UIComponent component, Object value) throws ValidatorException {
    double x = 0;
    try {
      x = Double.parseDouble(value.toString());
    } catch (NumberFormatException e) {
      throwError();
    }
    if (x < -3 || x > 5) {
      throwError();
    }
  }
}
