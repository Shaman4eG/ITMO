package Pip8;

public class ValidateInput {

    public String Validate(int x, int y)
    {
        if (!ValidateX(x)) return "Invalid X value. Should be in range [-2; 2]";
        if (!ValidateY(y)) return "Invalid Y value. Should be in range [-3; 3]";

        return null;
    }

    private boolean ValidateX(int x)
    {
        return   x >=  -2 &&
                 x <=   2;
    }

    private boolean ValidateY(int y)
    {
        return  y >=  -3 &&
                y <=   3;
    }
}
