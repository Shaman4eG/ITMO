package Pip8;

import javax.faces.application.FacesMessage;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import javax.faces.component.UIComponent;
import javax.faces.context.FacesContext;
import java.io.Serializable;

@ManagedBean
@SessionScoped
public class MainBean implements Serializable {

    private UIComponent setPoint;

    private int x;
    private int y;
    private int r;

    private int clickedX;
    private int clickedY;

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
            ShowMessage(errorMessage);
            return;
        }

        boolean hit = hitChecker.CheckHit(x, y ,r);

        // save points
        points.AddPoint(new Point(x, y));

        ShowMessage(String.valueOf(hit) + " " + String.valueOf(x) + " " + String.valueOf(y));//String.valueOf(hit));
    }


    public void AddClickedPoint()
    {
        boolean hit = hitChecker.CheckHit(clickedX, clickedY, r);

        // save points locally
        points.AddPoint(new Point(clickedX, clickedY));

        //controllerDb.addNewPoint(new PointEntity(clickedX, clickedY));

        // Remove
        //ShowMessage(String.valueOf(hit));
        ShowMessage(String.valueOf(hit) + " " + String.valueOf(clickedX) + " " + String.valueOf(clickedY));//String.valueOf(hit));

    }

    private void ShowMessage(String errorMessage)
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

    public int getClickedX() {
        return clickedX;
    }

    public void setClickedX(int clickedX) {
        this.clickedX = clickedX;
    }

    public int getClickedY() {
        return clickedY;
    }

    public void setClickedY(int clickedY) {
        this.clickedY = clickedY;
    }

    public void setSetPoint(UIComponent setPoint) {
        this.setPoint = setPoint;
    }

    public UIComponent getSetPoint() {
        return setPoint;
    }
}