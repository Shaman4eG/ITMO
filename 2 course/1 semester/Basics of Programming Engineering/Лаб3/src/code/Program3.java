import java.util.ArrayList;
import java.util.Stack;
import java.util.regex.Pattern;

public class Program3
{
    public static final int NUMBER_OF_DOTS = 9;

    public static void main(String[] args)
    {

        Forma chart = new Forma();
        Double getterOfR;   
        Stack dotsOnChart = new Stack();
        dotsInput(dotsOnChart);
        ArrayList<Punto> outOfZones = new ArrayList<Punto>();
        int numOfCheckedPuntos = 0;

        String arg = args[0];
        boolean valid = checkInput(arg);
        if (!valid) return;
        
        getterOfR = new Double(args[0]);
        chart.R = getterOfR;
        System.out.println("R = " + chart.R);
        

        // Checking dots positions and saving them for output, if dot is in NOT in zone
        do
        {
            if (!chart.IsInZone((Punto)dotsOnChart.peek(), chart.R))
                outOfZones.add((Punto)dotsOnChart.pop());
            else
                dotsOnChart.pop();
            numOfCheckedPuntos++;
        }
        while (numOfCheckedPuntos < NUMBER_OF_DOTS);

        // Outputting result
        System.out.print("Dots that are out of chart zone: ");
        for (Punto notInZonePunto: outOfZones)
            System.out.print("{" + notInZonePunto.X + ", " + notInZonePunto.Y + "}  ");
    }

    public enum inputParCases
    {
        VALID,
        COMMA_INSTEAD_DOT,
        PAR_IS_NEGATIVE,
        TOO_MANY_DIGITS,
        PAR_IS_NaN
    }
    
    public static boolean checkInput(String arg){
        switch (checkParameterInput(arg))
        {
            case VALID:
                return true;

            case COMMA_INSTEAD_DOT:
                System.out.print("Use '.',not ','\n");
                return false;

            case PAR_IS_NEGATIVE:
                System.out.print("R can't be negative.\n");
                return false;

            case TOO_MANY_DIGITS:
                System.out.print("Too many digits.\n");
                return false;

            case PAR_IS_NaN:
                System.out.print("R is not a number.\n");
                return false;
        }
        
        return false;
    }

    private static void dotsInput(Stack dotsOnChart)
    {
        Punto tmpPunto = new Punto();
        tmpPunto.X = -1;
        tmpPunto.Y = -3;
        dotsOnChart.push(tmpPunto);

        tmpPunto = new Punto();
        tmpPunto.X = -4;
        tmpPunto.Y = -4;
        dotsOnChart.push(tmpPunto);

        tmpPunto = new Punto();
        tmpPunto.X = 0;
        tmpPunto.Y = 0;
        dotsOnChart.push(tmpPunto);

        tmpPunto = new Punto();
        tmpPunto.X = -2;
        tmpPunto.Y = 0;
        dotsOnChart.push(tmpPunto);

        tmpPunto = new Punto();
        tmpPunto.X = 0;
        tmpPunto.Y = 1;
        dotsOnChart.push(tmpPunto);

        tmpPunto = new Punto();
        tmpPunto.X = -3;
        tmpPunto.Y = 4;
        dotsOnChart.push(tmpPunto);

        tmpPunto = new Punto();
        tmpPunto.X = 4;
        tmpPunto.Y = 5;
        dotsOnChart.push(tmpPunto);

        tmpPunto = new Punto();
        tmpPunto.X = -1;
        tmpPunto.Y = -3;
        dotsOnChart.push(tmpPunto);

        tmpPunto = new Punto();
        tmpPunto.X = 4;
        tmpPunto.Y = -5;
        dotsOnChart.push(tmpPunto);
    }

    public static inputParCases checkParameterInput(String R)
    {
        if (Pattern.matches("^\\d{1,16}$|^\\d{1,16}\\.\\d{1,16}$", R))
            return inputParCases.VALID;

        if (Pattern.matches("^\\d{1,16},\\d{1,16}$", R))
            return inputParCases.COMMA_INSTEAD_DOT;

        if (Pattern.matches("^-\\d{1,16}$|^-\\d{1,16}\\.\\d{1,16}$|^-\\d{1,16},\\d{1,16}$", R))
            return inputParCases.PAR_IS_NEGATIVE;

        if (Pattern.matches("^-?\\d+$|^-?\\d+\\.\\d+$", R))
            return inputParCases.TOO_MANY_DIGITS;

        return inputParCases.PAR_IS_NaN;
    }
}


// Punto with 2 coordinates
class Punto
{
    float X;
    float Y;
}


// Forma
class Forma
{
    // Parameter given by user
    double R;

    boolean IsInZone(Punto curPunto, double R)
    {
        if (curPunto.X < 0)
        {
            if ((curPunto.X >= -R) && (curPunto.Y >= 0) && (curPunto.Y <= 0.5 * (curPunto.X + R)))
                return true;
        }
        else if ((curPunto.X <= R) && (curPunto.Y >= -0.5 * R) && (curPunto.Y <= Math.sqrt(Math.pow(R, 2) - Math.pow(curPunto.X, 2))))
            return true;

        return  false;
    }
}
