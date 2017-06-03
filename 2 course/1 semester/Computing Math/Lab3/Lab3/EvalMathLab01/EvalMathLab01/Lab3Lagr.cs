using System.Collections.Generic;

namespace EvalMathLab01
{
    public class Spot : System.IComparable
    {
        public double x = 0;
        public double y = 0;

        public Spot(double _x, double _y)
        {
            x = _x;
            y = _y;
        }

        public int CompareTo(object obj)
        {
            Spot other = obj as Spot;
            return this.x.CompareTo(other.x);
        }
    }

    class Lab3Lagr
    {
        public delegate double Function(double x);
        public delegate double FunctionCoef(double x0, double x1);
        static Function Func;
        static FunctionCoef Coef;

        public static List<Spot> Evaluate(double leftBorder, double rightBorder, double[,] inputTable, int size, double dx)
        {
            List<Spot> result = new List<Spot>();
            Function f = LagrangesMethod(inputTable, size);
            for (double x = leftBorder; x < rightBorder; x += dx)
            {
                result.Add(new Spot(x, f(x)));
            }
            return result;
        }


        public static Function LagrangesMethod(double[,] inputTable, int size)
        {
            Coef = (x1, x0) => 1 / (x1 - x0);           
            Func = x =>
            {
                double composition = 1;
                double sum = 0;
                double c = 1;

                for (int i = 0; i < size; i++)
                {
                    composition = 1;
                    c = 1;
                    double y = inputTable[1, i];
                    double xi = inputTable[0, i];
                    for (int j = 0; j < size; j++)
                    {
                        if (i != j)
                        {
                            double xj = inputTable[0, j];
                            composition *= (x - xj);
                            c *= Coef(xi, xj);
                        }
                    }
                    composition *= y * c;
                    sum += composition;
                }

                return sum;
            };
            return Func;
        }
    }
}
