import java.util.ArrayList;
import java.util.Stack;
import java.util.regex.Pattern;

public class Program3
{
    public static final int NUMBER_OF_DOTS = 9;

    public static void main(String[] args)
    {
        Forma chart = new Forma();
        Stack dotsOnChart = new Stack();
        dotsInput(dotsOnChart);
        ArrayList<Punto> notInZoneDots = new ArrayList<Punto>();
        Double getterOfR;
        int numOfCheckedDots = 0;


        // Checking input
        if (args.length == 1)
        {
            switch (checkParameterInput(args[0]))
            {
                case VALID:
                    getterOfR = new Double(args[0]);
                    chart.R = getterOfR;
                    System.out.println("R = " + chart.R);
                    break;

                case COMMA_INSTEAD_DOT:
                    System.out.print("Use '.',not ','.");
                    return;

                case PAR_IS_NEGATIVE:
                    System.out.print("R can't be negative.");
                    return;

                case TOO_MANY_DIGITS:
                    System.out.print("Too many digits.");
                    return;

                case PAR_IS_NaN:
                    System.out.print("R is not a number.");
                    return;
            }
        }
        else if (args.length == 0)
        {
            System.out.print("R not given.");
            return;
        }
        else
        {
            System.out.print("Too many arguments.");
            return;
        }

        // Checking dots positions and saving them for output, if dot is in NOT in zone
        do
        {
            if (!chart.IsDotInZone((Punto)dotsOnChart.peek(), chart.R))
                notInZoneDots.add((Punto)dotsOnChart.pop());
            else
                dotsOnChart.pop();
            numOfCheckedDots++;
        }
        while (numOfCheckedDots < NUMBER_OF_DOTS);

        // Outputting result
        System.out.print("Dots that are out of chart zone: ");
        for (Punto notInZoneDot: notInZoneDots)
            System.out.print("{" + notInZoneDot.X + ", " + notInZoneDot.Y + "}  ");
    }

    private enum inputParCases
    {
        VALID,
        COMMA_INSTEAD_DOT,
        PAR_IS_NEGATIVE,
        TOO_MANY_DIGITS,
        PAR_IS_NaN
    }

    private static void dotsInput(Stack dotsOnChart)
    {
        Punto tmpDot = new Punto();
        tmpDot.X = -1;
        tmpDot.Y = -3;
        dotsOnChart.push(tmpDot);

        tmpDot = new Punto();
        tmpDot.X = -4;
        tmpDot.Y = -4;
        dotsOnChart.push(tmpDot);

        tmpDot = new Punto();
        tmpDot.X = 0;
        tmpDot.Y = 0;
        dotsOnChart.push(tmpDot);

        tmpDot = new Punto();
        tmpDot.X = -2;
        tmpDot.Y = 0;
        dotsOnChart.push(tmpDot);

        tmpDot = new Punto();
        tmpDot.X = 0;
        tmpDot.Y = 1;
        dotsOnChart.push(tmpDot);

        tmpDot = new Punto();
        tmpDot.X = -3;
        tmpDot.Y = 4;
        dotsOnChart.push(tmpDot);

        tmpDot = new Punto();
        tmpDot.X = 4;
        tmpDot.Y = 5;
        dotsOnChart.push(tmpDot);

        tmpDot = new Punto();
        tmpDot.X = -1;
        tmpDot.Y = -3;
        dotsOnChart.push(tmpDot);

        tmpDot = new Punto();
        tmpDot.X = 4;
        tmpDot.Y = -5;
        dotsOnChart.push(tmpDot);
    }

    private static inputParCases checkParameterInput(String R)
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


// Dot with 2 coordinates
class Punto
{
    float X;
    float Y;
}


// Chart
class Forma
{
    // Parameter given by user
    double R;

    boolean IsDotInZone(Punto curDot, double R)
    {
        if (curDot.X < 0)
        {
            if ((curDot.X >= -R) && (curDot.Y >= 0) && (curDot.Y <= 0.5 * (curDot.X + R)))
                return true;
        }
        else if ((curDot.X <= R) && (curDot.Y >= -0.5 * R) && (curDot.Y <= Math.sqrt(Math.pow(R, 2) - Math.pow(curDot.X, 2))))
            return true;

        return  false;
    }
}
