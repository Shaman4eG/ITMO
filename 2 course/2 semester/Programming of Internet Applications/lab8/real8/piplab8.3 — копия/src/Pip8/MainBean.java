package Pip8;

import javax.faces.application.FacesMessage;
import javax.faces.bean.ApplicationScoped;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import javax.faces.component.UIComponent;
import javax.faces.context.FacesContext;
import java.io.Serializable;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;

@ManagedBean
@SessionScoped
public class MainBean implements Serializable {

    private UIComponent setPoint;

    private int x;
    private int y;
    private int r;

    private ValidateInput validator;
    private HitChecker hitChecker;
    private PointsKeeper points;

    public MainBean()
    {
        x = 0;
        y = 0;
        r = 3;
        validator = new ValidateInput();
        hitChecker = new HitChecker();
        points = new PointsKeeper();
    }

    public void ValidateAndExecute()
    {
        String errorMessage = validator.Validate(x, y);
        if (errorMessage != null)
        {
            ShowError(errorMessage);
            return;
        }

        boolean hit = hitChecker.CheckHit(x, y ,r);

        points.AddPoint(new Point(x, y));
        List<Point> a = points.GetPoints();

        // Remove
        ShowError(String.valueOf(hit));
    }

    private void ShowError(String errorMessage)
    {
        FacesMessage message = new FacesMessage(errorMessage);
        FacesContext context = FacesContext.getCurrentInstance();
        context.addMessage(setPoint.getClientId(context), message);
    }

    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }

    public int getR() {
        return r;
    }

    public void setR(int r) {
        this.r = r;
    }

    public void setSetPoint(UIComponent setPoint) {
        this.setPoint = setPoint;
    }

    public UIComponent getSetPoint() {
        return setPoint;
    }
}